#include "QEAnnotation.hpp"
#include "QEAnnotationModel.hpp"
#include <QObject>

int main(int argc, char** argv)
{
	QEAnnotationModel annModel = QEAnnotation::registerModel<QObject>();

	return 0;
}
