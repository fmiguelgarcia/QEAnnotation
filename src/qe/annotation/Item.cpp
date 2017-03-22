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
#include "Item.hpp"

using namespace qe::annotation;
using namespace std;

Item::Item( const QString &key, const QVariant &value) noexcept
  : m_key(key), m_value(value)
{}

Item::Item( Item &&other) noexcept
  : m_key( move(other.m_key)), m_value( move(other.m_value))
{}

Item::Item(const Item &other) noexcept
  : m_key(other.m_key), m_value(other.m_value)
{}

Item &Item::operator=(const Item &other) = default;

Item &Item::operator=(Item &&other)
{
	m_key = std::move( other.m_key);
	m_value = std::move( other.m_value);
	return *this;
}

bool Item::operator==(const Item &other) const noexcept
{ return m_key == other.m_key; }

bool Item::operator<(const Item &other) const noexcept
{ return m_key < other.m_key; }

bool Item::isValid() const noexcept
{ return ! m_key.isEmpty(); }

const QString & Item::key() const noexcept
{ return m_key; }

QVariant Item::value( const QVariant & defaultValue ) const noexcept
{
	if (m_value.isNull())
		return defaultValue;
	return m_value;
}
