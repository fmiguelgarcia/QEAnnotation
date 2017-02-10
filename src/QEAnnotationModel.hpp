#pragma once
#include "QEAnnotationItem.hpp"
#include <QString>
#include <QSharedDataPointer>
#include <QMetaObject>
#include <map>

QE_BEGIN_NAMESPACE
class QEAnnotationModelPrivate;

using QEAnnotationItemList = std::vector<QEAnnotationItem>;
using QEAnnotationItemByClassInfoId = std::map<QString, QEAnnotationItemList>;

// Private class QEAnnotationModelPrivate
// =============================================================================
class QEAnnotationModelPrivate : public QSharedData
{
	public:
		QEAnnotationItemByClassInfoId m_annotationsByClassInfoId;
};

class QEAnnotationModel
{
	public:
		explicit QEAnnotationModel( const QMetaObject* meta);
		QEAnnotationModel( const QEAnnotationModel& ) noexcept;
		QEAnnotationModel& operator = ( const QEAnnotationModel& ) noexcept;

		QEAnnotationItem annotation( const QString classInfoId, const QString key) const;
		QEAnnotationItemList annotations( const QString classInfoId) const;
		QEAnnotationItemByClassInfoId annotations() const;

	private:
		/// @brief It parses all annotations for class info tags.
		void parseMetaObject( const QMetaObject* meta);

		/// @brief It parses annotations found in @p annotations string.
		QEAnnotationItemList parseAnnotationsInClassInfo(const QString annotations) const;

	private:
		QSharedDataPointer<QEAnnotationModelPrivate> d_ptr;
};
Q_DECLARE_TYPEINFO( QEAnnotationModel, Q_MOVABLE_TYPE);

QE_END_NAMESPACE
