#pragma once

#include <QObject>

class TestQAnnotation: public QObject
{
	Q_OBJECT
private slots:
	void QAnnotationModel_annotation();
};

