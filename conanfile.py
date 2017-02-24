from conans import ConanFile, CMake 
import os
import inspect

class QEAnnotationConan(ConanFile):
    name = "QEAnnotation"
    version = "0.1.0"
    requires = "QECommon/0.1.0@fmiguelgarcia/stable"
    settings = "os", "compiler", "build_type", "arch"
    license = "https://www.gnu.org/licenses/lgpl-3.0-standalone.html"
    generators = "cmake"
    url = "ssh://miguel@migroslinx.no-ip.org/home/miguel/git/QE/QEAnnotation"
    description = "Annotation library in Qt Enterprise"

    def source(self):
        self.run("git clone %s" % self.url) 

    def build(self):
        cmake = CMake( self.settings)
        self.run( "cmake %s/QEAnnotation %s" % (self.conanfile_directory, cmake.command_line))
        self.run( "cmake --build . %s" % cmake.build_config )

    def package(self):
        self.copy( pattern="*.hpp", dst="include/QEAnnotation/", src="QEAnnotation/src")
        self.copy( pattern="LICENSE.LGPLv3", dst="share/QEAnnotation")
        self.copy( pattern="libQEAnnotation.so*", dst="lib", src="src")

    def package_info(self):
        self.cpp_info.libs.extend(["QEAnnotation"])
        self.cpp_info.includedirs.extend(["include/QEAnnotation"])
