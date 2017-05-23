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
 *
 * $QE_END_LICENSE$
 */
#include "Model.hpp"

#include <QSharedData>
#include <QMetaObject>
#include <QMetaClassInfo>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QRegularExpressionMatchIterator>
#include <QStringBuilder>

using namespace qe::annotation;
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
}

// Class ModelPrivate
// ============================================================================

namespace qe { namespace annotation {
	class ModelPrivate : public QSharedData
	{
		public:
			const QMetaObject*  m_metaObject;
			/// @brief Annotation map by Class Info identifier.
			ItemByClassInfoId m_annotationsByClassInfoId;
	};
}}

// Class Model
// ============================================================================

Model::Model(const QMetaObject *meta)
  : Model( QSharedDataPointer<ModelPrivate>( new ModelPrivate), meta)
{}

Model::Model(const Model &other) noexcept
  : d_ptr( other.d_ptr)
{}
		
/// @brief 
Model::Model( QSharedDataPointer<ModelPrivate>&& dd, const QMetaObject* meta)
	: d_ptr(dd)
{
	if (meta)
	{
		d_ptr->m_metaObject = meta;
		parseMetaObject( meta);
	}
}

Model &Model::operator=(const Model &other) noexcept
{
	d_ptr = other.d_ptr;
	return *this;
}

Model::~Model()
{}

void Model::parseMetaObject( const QMetaObject* meta)
{
	for ( int ciIdx = 0; ciIdx < meta->classInfoCount(); ++ciIdx)
	{
		const QMetaClassInfo metaClassInfo = meta->classInfo( ciIdx);
		auto parsedAnnotations = parseAnnotationsInClassInfo( metaClassInfo.value());

		// Add new annotations
		auto & curAnnotations = d_ptr->m_annotationsByClassInfoId[metaClassInfo.name()];
		copy( begin(parsedAnnotations), end(parsedAnnotations),
			back_inserter<>(curAnnotations));

		// Remove duplicates.
		sort( begin(curAnnotations), end(curAnnotations));
		curAnnotations.erase( unique(begin(curAnnotations), end(curAnnotations)), end(curAnnotations));
	}
}

ItemList Model::parseAnnotationsInClassInfo(const QString &annotations) const
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

		annotationItems.emplace_back( key, value);
	}

	return annotationItems;
}

ItemByClassInfoId Model::annotations() const
{ return d_ptr->m_annotationsByClassInfoId; }

ItemList Model::annotations(const QString &classInfoId) const
{
	ItemList itemList;

	auto annListItr = d_ptr->m_annotationsByClassInfoId.find( classInfoId);
	if ( annListItr != end(d_ptr->m_annotationsByClassInfoId))
		itemList = annListItr->second;

	return itemList;
}

Item Model::annotation(const QString &classInfoId, const QString &key) const
{
	Item item;
	ItemList itemList = annotations( classInfoId);
	auto itemFoundRange = equal_range( begin(itemList), end(itemList), Item(key));
	if ( itemFoundRange.first !=  itemFoundRange.second)
		item = *itemFoundRange.first;

	return item;
}

const QMetaObject* Model::metaObject() const noexcept
{ return d_ptr->m_metaObject;}

