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

#pragma once
#include <qe/annotation/Global.hpp>
#include <qe/annotation/Item.hpp>
#include <QMetaObject>
#include <QSharedData>
#include <QString>
#include <boost/serialization/split_member.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/level.hpp>
#include <vector>
#include <map>

namespace qe::annotation 
{
	class QEANNOTATION_EXPORT ModelPrivate : public QSharedData
	{
		public:
			explicit ModelPrivate( const QMetaObject* meta = nullptr);

			const QString& name() const noexcept;

			const Item findAnnotation(
				const QString &classInfoId,
				const QString &key) const;

			const ItemList findAnnotations(
				const QString &classInfoId) const;

			// Serialization
			BOOST_SERIALIZATION_SPLIT_MEMBER()
			template< class Archive>
			void save( Archive& ar, const unsigned int) const;
			template< class Archive>
			void load( Archive& ia, const unsigned int);

		public:
			const QMetaObject*  metaObject;
			/// @brief Annotation map by Class Info identifier.
			ItemByClassInfoId annotations;

		protected:
			void setName( const QString& name);

		private:
			QString m_name;						///< Model name.
	};
}

BOOST_CLASS_IMPLEMENTATION( qe::annotation::ModelPrivate, boost::serialization::object_serializable)
BOOST_CLASS_EXPORT_KEY( qe::annotation::ModelPrivate)
