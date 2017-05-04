#include <qe/annotation/Annotation.hpp>
#include <QObject>

using namespace qe::annotation;

int main(int argc, char** argv)
{
	auto annModel = Annotation::registerModel<QObject>();

	return 0;
}
