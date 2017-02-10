#include "QEAnnotationItem.hpp"

QE_USE_NAMESPACE
using namespace std;

QEAnnotationItem::QEAnnotationItem( QString key, QVariant value) noexcept
  : m_key(move(key)), m_value(move(value))
{}

QEAnnotationItem::QEAnnotationItem( QEAnnotationItem &&other) noexcept
  : m_key( move(other.m_key)), m_value( move(other.m_value))
{}

QEAnnotationItem::QEAnnotationItem(const QEAnnotationItem &other) noexcept
  : m_key(other.m_key), m_value(other.m_value)
{}

QEAnnotationItem &QEAnnotationItem::operator=(const QEAnnotationItem &other) = default;

bool QEAnnotationItem::operator==(const QEAnnotationItem &other) const noexcept
{ return m_key == other.m_key; }

bool QEAnnotationItem::operator<(const QEAnnotationItem &other) const noexcept
{ return m_key < other.m_key; }

bool QEAnnotationItem::isValid() const noexcept
{ return ! m_key.isEmpty(); }

QString QEAnnotationItem::key() const noexcept
{ return m_key; }

QVariant QEAnnotationItem::value( const QVariant defaultValue ) const noexcept
{
	if (m_value.isNull())
		return defaultValue;
	return m_value;
}
