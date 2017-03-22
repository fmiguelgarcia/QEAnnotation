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
#include <qe/annotation/Item.hpp>
#include <QString>
#include <QSharedDataPointer>
#include <QMetaObject>
#include <map>
#include <vector>

namespace qe { namespace annotation {
	
	class ModelPrivate;

	using ItemList = std::vector<Item>;
	using ItemByClassInfoId = std::map<QString, ItemList>;

	/// @brief Shared data of Model. 
	class ModelPrivate : public QSharedData
	{
		public:
			/// @brief Annotation map by Class Info identifier.
			ItemByClassInfoId m_annotationsByClassInfoId;
	};

	/// @brief It parses the meta-object information and allows to find class and 
	///	members annotations. 
	///
	/// This class uses a implicitly shared (see http://doc.qt.io/qt-5/implicit-sharing.html).
	/// Annotations are extracted from Q_CLASSINFO detected by moc. Let's see the
	/// following example:
	/// @code{.cpp}
	///	class Person : public QObject
	///	{
	///		Q_OBJECT
	///		Q_PROPERTY( QString name MEMBER name)
	///
	///		Q_CLASSINFO( "class", "@QEOrm.table=person")
	///		Q_CLASSINFO( "name", "@QEOrm.maxLength=128 @QEOrm.isNullable=false")
	///
	///		public:
	///			Person( QObject* parent = nullptr);
	///		
	///			QString name;
	///	};
	/// @endcode
	///
	/// In above code, we have used Q_CLASSINFO macro to add several annotations:
	///	- Q_CLASSINFO( "class", "@QEOrm.table=person"): It associates the
	/// annotation "@QEOrm.table" to the class info id "class".
	///	- 	Q_CLASSINFO( "name", "@QEOrm.maxLength=128 @QEOrm.isNullable=false"):
	/// In this case, we've associated two annotations to property "name".
	/// When class info id is a name of a property, we consider that annotations are
	/// linked to this property.
	/// The class info id "class" is an special case because some annotation models
	/// considers it as a class scope annotation.
	/// You can add any number of annotations into a Q_CLASSINFO using the space as
	/// a separator character. Every annotation *HAVE TO* start with '@'.
	class Model
	{
		public:
			/// @brief It creates an annotation model using meta-information from
			/// @p meta.
			explicit Model( const QMetaObject* meta);

			/// @brief Copy constructor.
			Model( const Model& ) noexcept;

			/// @brief Copy operator.
			Model& operator = ( const Model& ) noexcept;

			/// @brief It gets the annotation for the specific @p classInfoId and @p
			/// key. 
			/// @param classInfoId Q_CLASSINFO name use to store annotation.
			/// @param key
			Item annotation( const QString classInfoId, const QString key) const;

			/// @brief It gets all annotations for a specific classInfoId.
			ItemList annotations( const QString classInfoId) const;

			/// @brief It gets all annotations for this model.
			ItemByClassInfoId annotations() const;

		private:
			/// @brief It parses all annotations for class info tags.
			void parseMetaObject( const QMetaObject* meta);

			/// @brief It parses annotations found in @p annotations string.
			ItemList parseAnnotationsInClassInfo(const QString annotations) const;

		private:
			QSharedDataPointer<ModelPrivate> d_ptr;
	};
}}
	
Q_DECLARE_TYPEINFO( qe::annotation::Model, Q_MOVABLE_TYPE);
