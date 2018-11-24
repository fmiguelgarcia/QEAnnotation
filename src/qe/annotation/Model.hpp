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
#include <qe/annotation/Global.hpp>
#include <qe/annotation/Item.hpp>
#include <QExplicitlySharedDataPointer>
#include <QMetaObject>

namespace qe::annotation 
{
	class ModelPrivate;

	class QEANNOTATION_EXPORT Model
	{
		public:
			explicit Model( const QMetaObject* meta);
			Model( const Model& ) noexcept;
			Model( Model&& ) noexcept;
			~Model();

			Model& operator = ( const Model& ) noexcept;
			Model& operator = ( Model&& ) noexcept;

			const QString& name() const noexcept;

			Item annotation( const QString &classInfoId, const QString &key) const;
			ItemList annotations( const QString &classInfoId) const;
			ItemByClassInfoId annotations() const;
			const QMetaObject* metaObject() const noexcept;

			void detach();

		protected:
			QExplicitlySharedDataPointer<ModelPrivate> d_ptr;

			explicit Model( QExplicitlySharedDataPointer<ModelPrivate>&& dd) noexcept;
			explicit Model( const QExplicitlySharedDataPointer<ModelPrivate>& dd) noexcept;

		private:
			/// @brief It parses all annotations for class info tags.
			void parseMetaObject( const QMetaObject* meta);

			/// @brief It parses annotations found in @p annotations string.
			ItemList parseAnnotationsInClassInfo(const QString &annotations) const;

			Q_DECLARE_PRIVATE( Model);
	};
}

Q_DECLARE_TYPEINFO( qe::annotation::Model, Q_MOVABLE_TYPE);
