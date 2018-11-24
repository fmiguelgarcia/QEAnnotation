from conans import  tools, CMake, python_requires 

base = python_requires( 'QEConanFile/1.0.0@dmious/stable')

class QEAnnotationConan(base.QEConanFile):
    name = "QEAnnotation"
    version = base.QEConanFile.version_from_file( 
        'src/qe/annotation/CMakeLists.txt',
        r"set\( QEAnnotation_VERSION (.*)\)")
    requires = "QECore/0.1.0@dmious/stable"
    settings = "os", "compiler", "build_type", "arch"
    license = "https://www.gnu.org/licenses/lgpl-3.0-standalone.html"
    generators = "cmake"
    url = "https://github.com/fmiguelgarcia/QEAnnotation.git"
    description = "Annotation library in Qt Enterprise"
    exports_sources = ["src/*", "test/*", "tools/*", "CMakeLists.txt", "!.*.swq"]

    def build(self):
        cmake = CMake( self)
        cmake.configure()
        cmake.build()

    def package(self):
        self.copy( pattern="*.hpp", dst="include/qe/annotation/",
                src="src/qe/annotation")
        self.copy( pattern="LICENSE.LGPLv3", dst="share/qe/annotation")
        self.copy( pattern="libQEAnnotation.so*", dst="lib",
                src="src/qe/annotation", links=True)
        if tools.os_info.is_windows: 
            libNames = ["QEAnnotation", "libQEAnnotation"]
            libExts = [".dll", ".lib", ".dll.a", ".pdb"]
            for libName in libNames:
                for libExt in libExts:
                    filePattern = "**/" + libName + libExt
                    self.copy( pattern=filePattern, dst="lib", src="src/qe/annotation", keep_path=False)

    def package_info(self):
        self.cpp_info.libs.extend(["QEAnnotation"])
