#include "QAnnotationTest.hpp"
#include "AnnotateClassOne.hpp"
#include <qe/annotation/Annotation.hpp>
#include <QTest>
using namespace qe::annotation;

void TestQAnnotation::QAnnotationModel_annotation()
{
	Model annModel = Annotation::registerModel<AnnotateClassOne>();

	// Check member annotation
	QVERIFY( annModel.annotation( "id", "@qorm.primary_key").value().toBool());
	QVERIFY( annModel.annotation( "id", "@qorm.autoincrement").value().toBool());
	QVERIFY( annModel.annotation( "id", "@json.property.name").value().toString() == "oid");

	QVERIFY( annModel.annotation( "description", "@qorm.notnull").value().toBool() == false);
	QVERIFY( annModel.annotation( "description", "@qorm.maxchar").value().toInt() == 255);

	QVERIFY( annModel.annotation( "description", "@_unvalid_annotation").value().isNull());
	QVERIFY( annModel.annotation( "invalid_description", "@annotation").value().isNull());
	
	QVERIFY( annModel.annotation( "add", 
		"@webmvc.requestMapping").value().toString() == "x/xx/value");

	QVERIFY( annModel.annotation( "testColon", "@w.class")
			.value().toString() == "std::mutex");
}


QTEST_MAIN(TestQAnnotation)
