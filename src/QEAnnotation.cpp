#include "QEAnnotation.hpp"

QE_USE_NAMESPACE
using namespace std;

QEAnnotation::AnnotationCacheByName QEAnnotation::m_registeredModels;

QEAnnotationModel QEAnnotation::registerModel(const QMetaObject *meta)
{
	QEAnnotationModel annModel(nullptr);
	if (meta)
	{
		const QByteArray name = meta->className();
		auto itr = m_registeredModels.find( name);
		if (itr == end(m_registeredModels))
			itr = m_registeredModels.insert(
				make_pair (name, QEAnnotationModel(meta))).first;
		annModel = itr->second;
	}

	return annModel;
}
