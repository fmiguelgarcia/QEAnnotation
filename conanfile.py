from conans import ConanFile, CMake 
from conans.tools import os_info
import multiprocessing

class QEAnnotationConan(ConanFile):
    name = "QEAnnotation"
    version = "0.1.0"
    requires = "QECommon/0.1.0@fmiguelgarcia/stable"
    settings = "os", "compiler", "build_type", "arch"
    license = "https://www.gnu.org/licenses/lgpl-3.0-standalone.html"
    generators = "cmake"
    url = "https://github.com/fmiguelgarcia/QEAnnotation.git"
    description = "Annotation library in Qt Enterprise"
    exports_sources = ["src/*", "test/*", "tools/*", "CMakeLists.txt"]

    def build(self):
        cmake = CMake( self.settings)
        self.run( "cmake %s %s" % (self.conanfile_directory, cmake.command_line))
        self.run( "cmake --build . %s" % cmake.build_config)

    def package(self):
        self.copy( pattern="*.hpp", dst="include/qe/annotation/",
                src="src/qe/annotation")
        self.copy( pattern="LICENSE.LGPLv3", dst="share/qe/annotation")
        self.copy( pattern="libQEAnnotation.so*", dst="lib",
                src="src/qe/annotation", links=True)
        self.copy( pattern="libQEAnnotation.dll", dst="lib", src="src/qe/annotation/bin")
        self.copy( pattern="libQEAnnotation.dll.a", dst="lib", src="src/qe/annotation/lib")

    def package_info(self):
        self.cpp_info.libs.extend(["QEAnnotation"])
