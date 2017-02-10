#pragma once
#include "QEAnnotationModel.hpp"
#include <QByteArray>
#include <map>

QT_BEGIN_NAMESPACE

class QEAnnotation
{
	public:
		using AnnotationCacheByName = std::map<QByteArray, QEAnnotationModel>;

		/// @brief It registers the Annotation model for class T
		template <class T>
		static QEAnnotationModel registerModel();

		static QEAnnotationModel registerModel( const QMetaObject *meta);

	private:
		/// @brief Registered annotation modeles.
		static AnnotationCacheByName m_registeredModels;
};

template <class T>
QEAnnotationModel QEAnnotation::registerModel()
{
	return registerModel( &T::staticMetaObject);
}

QT_END_NAMESPACE
