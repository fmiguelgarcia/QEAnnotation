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
#include "Model.hpp"
#include "ModelPrivate.hpp"

using namespace qe::annotation;
using namespace std;

/**
 * \class qe::annotation::Model
 * \brief It parses the meta-object information and allows to find class and
 * members annotations.
 * This class use Explicit shared data.
 */

/// @brief It creates an annotation model using meta-information from
/// @p meta Annotation information will be extracted from here.
Model::Model(const QMetaObject *meta)
  : Model(
		QExplicitlySharedDataPointer<ModelPrivate>(
			new ModelPrivate(meta)))
{}

Model::Model(const Model &other) noexcept
  : d_ptr( other.d_ptr)
{}

Model::Model(Model &&other) noexcept
  : d_ptr( std::move(other.d_ptr))
{}

Model::Model( QExplicitlySharedDataPointer<ModelPrivate>&& dd) noexcept
	: d_ptr( std::move(dd))
{}

Model::Model( const QExplicitlySharedDataPointer<ModelPrivate>& dd) noexcept
	: d_ptr( dd)
{}

Model::~Model()
{}

Model &Model::operator=(const Model &other) noexcept
{
	d_ptr = other.d_ptr;
	return *this;
}

Model &Model::operator=( Model &&other) noexcept
{
	d_ptr = std::move( other.d_ptr);
	return *this;
}

/// @brief It gets all annotations for this model.
ItemByClassInfoId Model::annotations() const
{
	const Q_D(Model);
	return d->annotations;
}

/// @brief It gets all annotations for a specific classInfoId.
ItemList Model::annotations(const QString &classInfoId) const
{
	const Q_D(Model);
	return d->findAnnotations( classInfoId);
}

/// @brief It gets the annotation for the specific @p classInfoId and @p
/// key.
/// @param classInfoId Q_CLASSINFO name use to store annotation.
/// @param key
Item Model::annotation(const QString &classInfoId, const QString &key) const
{
	const Q_D(Model);
	return d->findAnnotation( classInfoId, key);
}

/// @return The meta-object related with this model.
const QMetaObject* Model::metaObject() const noexcept
{
	const Q_D(Model);
	return d->metaObject;
}

void Model::detach()
{
	d_ptr.detach();
}

