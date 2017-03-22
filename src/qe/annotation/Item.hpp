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
#include <QString>
#include <QVariant>

namespace qe { namespace annotation {

	/// @brief It stores the key and value of an annotation.
	class Item
	{
		public:
			/// @brief Constructor.
			explicit Item(
					QString key = QString(),
					QVariant value = QVariant()) noexcept;

			/// @brief Move constructor.
			Item( Item &&other) noexcept;

			/// @brief Copy constructor.
			Item( const Item &other) noexcept;

			/// @brief Copy operator.
			Item &operator =( const Item &other);
		
			/// @brief Move operator	
			Item &operator =( Item &&other);

			/// @brief It indicates if both annotations have the same key. 
			bool operator == (const Item& other) const noexcept;

			/// @brief It compares the keys of both annotations.
			bool operator < (const Item& other) const noexcept;

			/// @brief Annotation item is valid when its key is NOT empty.
			bool isValid() const noexcept;

			/// @brief It gets the key of this annotation.
			QString key() const noexcept;

			/// @brief It returns the value of this annotation. 
			/// If value is null, it will return @p defaultValue instead.
			/// @param defaultValue Value that will be returned if internal value is
			/// null
			QVariant value( const QVariant defaultValue = QVariant()) const noexcept;

		private:
			QString m_key;			///< Key
			QVariant m_value;		///< Value
	};
}}
