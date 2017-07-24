/*
 * Copyright (C) 2017 francisco miguel garcia rodriguez
 * Contact: http://www.dmious.com/qe/licensing/
 *
 * This file is part of the QE Common module of the QE Toolkit.
 *
 * $QE_BEGIN_LICENSE:LGPL21$
 * Commercial License Usage
 * Licensees holding valid commercial QE licenses may use this file in
 * accordance with the commercial license agreement provided with the
 * Software or, alternatively, in accordance with the terms contained in
 * a written agreement between you and The Dmious Company. For licensing terms
 * and conditions see http://www.dmious.com/qe/terms-conditions. For further
 * information use the contact form at http://www.dmious.com/contact-us.
 *
 * GNU Lesser General Public License Usage
 * Alternatively, this file may be used under the terms of the GNU Lesser
 * General Public License version 3 as published by the Free
 * Software Foundation and appearing in the file LICENSE.LGPLv3
 * included in the packaging of this file. Please review the
 * following information to ensure the GNU Lesser General Public License
 * requirements will be met: https://www.gnu.org/licenses/lgpl.html and
 * http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
 * $QE_END_LICENSE$
 *
 */

#include "ModelPrivate.hpp"
#include <qe/common/serialization/QVariant.hpp>
#include <qe/common/serialization/QMetaObject.hpp>
#include <qe/common/serialization/QMap.hpp>
#include <qe/common/serialization/QVector.hpp>

#include <QMetaObject>
#include <QMetaClassInfo>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QRegularExpressionMatchIterator>
#include <QStringBuilder>

#include <boost/archive/polymorphic_iarchive.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>
#include <boost/serialization/nvp.hpp>

using namespace qe::annotation;
using namespace boost::serialization;
using namespace boost;
using namespace std;

namespace {

	/// @brief It creates the annotate assign expression using to parse
	/// Q_CLASSINFO
	QString annotateAssignExpression()
	{
		static const QString keyExp = QStringLiteral("(?<key>\\@(\\w(\\w|\\.)+))");
		static const QString valueOneWordExp = QStringLiteral("(?<valueOneWord>((\\w|/|:)+))");
		static const QString valueMuliWordsExp = QStringLiteral( "(\\'(?<valueMultiWords>((\\w|\\s|/|:)+))\\')");

		static const QString assignExp =
			keyExp
			% QStringLiteral("\\s*=\\s*(")
			% valueOneWordExp % QStringLiteral("|")
			% valueMuliWordsExp % QStringLiteral( ")");

		return assignExp;
	}

	ItemList parseAnnotationsInClassInfo(const QString &annotations)
	{
		ItemList annotationItems;

		QRegularExpression assignExp( annotateAssignExpression());
		QRegularExpressionMatchIterator matchItr = assignExp.globalMatch( annotations);
		while ( matchItr.hasNext())
		{
			QRegularExpressionMatch match = matchItr.next();
			QString key = match.captured( QStringLiteral("key"));
			QString value = match.captured( QStringLiteral("valueOneWord"));
			if ( value.isEmpty())
				value = match.captured( QStringLiteral("valueMultiWords"));

			annotationItems.push_back( Item(key, value));
		}

		return annotationItems;
	}

	ItemByClassInfoId parseMetaObject( const QMetaObject* meta)
	{
		ItemByClassInfoId annotationsByClassInfoId;
		for ( int ciIdx = 0; ciIdx < meta->classInfoCount(); ++ciIdx)
		{
			const QMetaClassInfo metaClassInfo = meta->classInfo( ciIdx);
			const QString mcName = metaClassInfo.name();
			const QString mcValue = metaClassInfo.value();

			auto parsedAnnotations = parseAnnotationsInClassInfo( mcValue);

			// Add new annotations
			auto & curAnnotations = annotationsByClassInfoId[ mcName];
			copy( begin(parsedAnnotations), end(parsedAnnotations),
				  back_inserter<>(curAnnotations));

			// Remove duplicates.
			sort( begin(curAnnotations), end(curAnnotations));
			curAnnotations.erase( unique(begin(curAnnotations), end(curAnnotations)), end(curAnnotations));
		}
		return annotationsByClassInfoId;
	}

}

ModelPrivate::ModelPrivate( const QMetaObject* meta)
	: metaObject( meta)
{
	if( meta)
		annotations = parseMetaObject( meta);
}

const Item ModelPrivate::findAnnotation(
	const QString &classInfoId,
	const QString &key) const
{
	Item item;
	const ItemList itemList = findAnnotations( classInfoId);

	auto itemFoundRange = equal_range( begin(itemList), end(itemList), Item(key));
	if ( itemFoundRange.first !=  itemFoundRange.second)
		item = *itemFoundRange.first;

	return item;
}

const ItemList ModelPrivate::findAnnotations(
	const QString &classInfoId) const
{
	ItemList itemList;

	auto annListItr = annotations.find( classInfoId);
	if ( annListItr != end(annotations))
		itemList = annListItr.value();

	return itemList;
}

void ModelPrivate::setName(const QString& name)
{ m_name = name;}

const QString & ModelPrivate::name() const noexcept
{ return m_name; }

#if 1
void ModelPrivate::save( archive::polymorphic_oarchive& oa, const unsigned int) const
{
	const string className { metaObject->className()};

	oa & make_nvp( "name", m_name);
	oa & make_nvp( "annotations", annotations);
	oa & make_nvp( "metaObject", className);
}

void ModelPrivate::load( archive::polymorphic_iarchive& ia, const unsigned int)
{
	string className;

	ia & make_nvp( "name", m_name);
	ia & make_nvp( "annotations", annotations);
	ia & make_nvp( "metaObject", className);

	const int typeId = QMetaType::type( className.c_str());
	metaObject = QMetaType::metaObjectForType( typeId);
}

#else
// Explicity instantiate templates for polymorphics archivs
template
void ModelPrivate::serialize<archive::polymorphic_oarchive>(
	archive::polymorphic_oarchive& oa,
	const unsigned int);

template
void ModelPrivate::serialize<archive::polymorphic_iarchive>(
	archive::polymorphic_iarchive& ia,
	const unsigned int);
#endif
