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

#pragma once
#include "QEAnnotationModel.hpp"
#include <QByteArray>
#include <map>

QT_BEGIN_NAMESPACE

/// @brief It is an utility class to register annotation models.
class QEAnnotation
{
	public:
		using AnnotationCacheByName = std::map<QByteArray, QEAnnotationModel>;

		/// @brief It registers the Annotation model for class T
		template <class T>
		static QEAnnotationModel registerModel();

		/// @brief It register the annotation model for metaobject @p meta.
		static QEAnnotationModel registerModel( const QMetaObject *meta);

	private:
		/// @brief Registered annotation models.
		static AnnotationCacheByName m_registeredModels;
};

template <class T>
QEAnnotationModel QEAnnotation::registerModel()
{
	return registerModel( &T::staticMetaObject);
}

QT_END_NAMESPACE
