#include <QObject>

class AnnotateClassOne : public QObject
{
	Q_OBJECT
	Q_PROPERTY( int id MEMBER m_id)
	Q_PROPERTY( QString description MEMBER m_description)
	Q_PROPERTY( double realValue MEMBER m_realValue)

	// Example of @qorm annotations
	Q_CLASSINFO( "class", "@qorm.table=xa1 @qorm.description='Description with spaces'")

	Q_CLASSINFO( "id", "@qorm.primary_key=true @qorm.autoincrement=true")
	Q_CLASSINFO( "description", "@qorm.notnull=false @qorm.maxchar=255")
	Q_CLASSINFO( "realValue", "@qorm.default = 1.0")

	Q_CLASSINFO( "id", "@json.property.name=oid")
	Q_CLASSINFO( "description", "@json.property.name=desc")
	Q_CLASSINFO( "realValue",  "@json.property.enable=false")

	Q_CLASSINFO( "add", "@webmvc.requestMapping=x/xx/value")
	
	public:
		Q_INVOKABLE double add( double a, double b) const;
		
	private:
		int m_id;
		QString m_description;
		double m_realValue;
};
