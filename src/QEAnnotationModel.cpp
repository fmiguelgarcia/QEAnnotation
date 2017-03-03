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
#include "QEAnnotationModel.hpp"

#include <QSharedData>
#include <QMetaObject>
#include <QMetaClassInfo>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QRegularExpressionMatchIterator>
#include <map>

QE_USE_NAMESPACE
using namespace std;

namespace {

	/// @brief It creates the annotate assign expression using to parse
	/// Q_CLASSINFO
	QString annotateAssignExpression()
	{
		const QLatin1Literal keyExp("(?<key>\\@(\\w(\\w|\\.)+))");
		const QLatin1Literal valueOneWordExp("(?<valueOneWord>((\\w|/|:)+))");
		const QLatin1Literal valueMuliWordsExp( "(\\'(?<valueMultiWords>((\\w|\\s|/|:)+))\\')");

		const QString assignExp = QString("%1\\s*=\\s*(%2|%3)")
			.arg( keyExp)
			.arg( valueOneWordExp)
			.arg( valueMuliWordsExp);

		return assignExp;
	}
}

QEAnnotationModel::QEAnnotationModel(const QMetaObject *meta)
  : d_ptr( new QEAnnotationModelPrivate)
{
	if (meta)
		parseMetaObject( meta);
}

QEAnnotationModel::QEAnnotationModel(const QEAnnotationModel &other) noexcept
  : d_ptr( other.d_ptr)
{}

QEAnnotationModel &QEAnnotationModel::operator=(const QEAnnotationModel &other) noexcept
{
	d_ptr = other.d_ptr;
	return *this;
}

void QEAnnotationModel::parseMetaObject( const QMetaObject* meta)
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

QEAnnotationItemList QEAnnotationModel::parseAnnotationsInClassInfo(const QString annotations) const
{
	QEAnnotationItemList annotationItems;

	QRegularExpression assignExp( annotateAssignExpression());
	QRegularExpressionMatchIterator matchItr = assignExp.globalMatch( annotations);
	while ( matchItr.hasNext())
	{
		QRegularExpressionMatch match = matchItr.next();
		QString key = match.captured( QLatin1Literal("key"));
		QString value = match.captured( QLatin1Literal("valueOneWord"));
		if ( value.isEmpty())
			value = match.captured( QLatin1Literal("valueMultiWords"));

		annotationItems.emplace_back( key, value);
	}

	return annotationItems;
}

QEAnnotationItemByClassInfoId QEAnnotationModel::annotations() const
{ return d_ptr->m_annotationsByClassInfoId; }

QEAnnotationItemList QEAnnotationModel::annotations(const QString classInfoId) const
{
	QEAnnotationItemList itemList;

	auto annListItr = d_ptr->m_annotationsByClassInfoId.find( classInfoId);
	if ( annListItr != end(d_ptr->m_annotationsByClassInfoId))
		itemList = annListItr->second;

	return itemList;
}

QEAnnotationItem QEAnnotationModel::annotation(const QString classInfoId, const QString key) const
{
	QEAnnotationItem item;
	QEAnnotationItemList itemList = annotations( classInfoId);
	auto itemFoundRange = equal_range( begin(itemList), end(itemList), QEAnnotationItem(key));
	if ( itemFoundRange.first !=  itemFoundRange.second)
		item = *itemFoundRange.first;

	return item;
}
