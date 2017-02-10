#include "QAnnotationTest.hpp"
#include "AnnotateClassOne.hpp"
#include "../src/QEAnnotationModel.hpp"
#include "../src/QEAnnotation.hpp"
#include <QTest>

void TestQAnnotation::QAnnotationModel_annotation()
{
	QEAnnotationModel annModel = QEAnnotation::registerModel<AnnotateClassOne>();

	// Check member annotation
	QVERIFY( annModel.annotation( "id", "@qorm.primary_key").value().toBool());
	QVERIFY( annModel.annotation( "id", "@qorm.autoincrement").value().toBool());
	QVERIFY( annModel.annotation( "id", "@json.property.name").value().toString() == "oid");

	QVERIFY( annModel.annotation( "description", "@qorm.notnull").value().toBool() == false);
	QVERIFY( annModel.annotation( "description", "@qorm.maxchar").value().toInt() == 255);

	QVERIFY( annModel.annotation( "description", "@_unvalid_annotation").value().isNull());
	QVERIFY( annModel.annotation( "invalid_description", "@annotation").value().isNull());
}


QTEST_MAIN(TestQAnnotation)
