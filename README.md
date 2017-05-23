# QEAnnotation

It is the Annotation library in **QE Framework**. It allows you to *annotate* easily *QObject* classes and access to a model class that represents its custom annotation.

1. [How to use custom annotations]()
  1. [Models and Annotation singleton]()
1. [Installation](#installation)
1. [Versioning](#versioning)
1. [License](#license)

## How to use custom annotations

Let's assume that we are using an ORM that uses annotations to make relations between objects in memory and your database.
Our first step is to annotate the classes. *QEAnnotation* uses **Q_CLASSINFO** Qt macro to add annotations to a property.
In this example, we will use the 'book' concept.

```C++
class Book : public QObject
{
	Q_OBJECT 
	Q_CLASSINFO( "class", "@qe.model.name=book")

	Q_PROPERTY( int id MEMBER id)
	Q_CLASSINFO( "id", "@qe.entity.isAutoIncrementable=true @qe.entity.name=bid")

	Q_PROPERTY( QString title MEMBER title)
	Q_CLASSINFO( "title", "@qe.entity.maxLength=256")

	Q_PROPERTY( QString author MEMBER author)
	Q_CLASSINFO( "author", "@qe.entity.maxLength=512")

	public:
		int id = 0;
		QString title;
		QString author;
};
```

In the above example code, we have the following annotation over properties:
 - On 'id' property: 
   - \@qe.entity.isAutoIncrementable = true
   - \@qe.entity.name = bid

 - On 'title' property:
   - \@qe.entity.maxLength = 256

You can create as much annotations as you want, but they **MUST** start with **\@** character.

In order to access those annotations from your code, you only need to load the model of this class using the singleton {{qe::annotation::Annotation}}.

```C++
	// In your code...
	using qe::annotation;

	// ...
	Model bookAnnModel = Annotation::registerModel<Book>();
	
	bool isIdAuto = bookAnnModel.annotation( "id", "@qe.entity.isAutoIncrementable")
		.value().toBool();
	int maxLength = bookAnnModel.annotation( "title", "@qe.entity.maxLength")
		.value().toInt();Annotation::registerModel<Book>();
```

### Models and Annotation singleton

*Model* class uses [implicit sharing concept](http://doc.qt.io/qt-5/implicit-sharing.html), so you can copy efficiently objects.

Also *Annotation* class caches the models associated to any specific class. In this way, only first load will parse the annotations.

## Installation

The easiest way to use this library in your code is by [Conan Package Manager](https://www.conan.io).
Please use the project setup that you can find in [QEAnnotation/1.0.0 Conan](https://www.conan.io/source/QEAnnotation/1.0.0/fmiguelgarcia/stable).

## Versioning

This library uses [Semantic Versioning](htpp://semver.org) and internal private implementation to provide a long-term, stable, and reusable binaries.

## License 

This license follows the dual-license pattern that Qt is currently using. A [LGPL 3.0 license](https://www.gnu.org/licenses/lgpl-3.0-standalone.html) for projects that do not need commercial support, and another one, **Commercial license** for rest of cases. 

You can find a brief comparison between both licenses in the below table:

 License types                 | LGPLv3 | Commercial 
-------------------------------|--------|------------
 Community Support             | Yes    | Yes
 Official Support Helpdesk     | No     | Yes
 Keep your application private | No     | Yes
 Possible to keep your application private with dynamic linking | Yes | Yes
 No need to provide a relinking mechanism for QE Framework <br> (can always use static linking)  | No | Yes
 No need to provide a copy of license and explicitly<br> acknowledge the use of QE | No | Yes
 No need to make copy of the QE Framework source code <br> available for customers | No | Yes
 Full rights to proprietary QE source code modifications | No | Yes
 Enforce DRM                   | [See LGPLv3 FAQ](https://www.gnu.org/licenses/gpl-faq.html#DRMProhibited) | Yes
 Enforce software patents      | [See LGPLv3 FAQ](https://www.gnu.org/licenses/gpl-faq.html#DRMProhibited) | Yes

