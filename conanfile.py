from conans import ConanFile, CMake 
import os

class QEAnnotationConan(ConanFile):
    name = "QEAnnotation"
    version = "1.0.0"
    requires = "QECommon/1.0.0@fmiguelgarcia/stable"
    settings = "os", "compiler", "build_type", "arch"
    license = "https://www.gnu.org/licenses/lgpl-3.0-standalone.html"
    generators = "cmake"
    url = "https://github.com/fmiguelgarcia/QEAnnotation.git"
    description = "Annotation library in Qt Enterprise"
    exports_sources = ["src/*", "test/*", "tools/*", "CMakeLists.txt"]
    options = { "qt_version": "ANY"}

    def configure(self):
        self.options.qt_version = os.popen("qmake -query QT_VERSION").read().strip()
        self.output.info("Configure Qt Version: %s" % self.options.qt_version)


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
        if self.settings.os == "Windows":
            libNames = ["QEAnnotation", "libQEAnnotation"]
            libExts = [".dll", ".lib", ".dll.a", ".pdb"]
            for libName in libNames:
                for libExt in libExts:
                    filePattern = "**/" + libName + libExt
                    self.copy( pattern=filePattern, dst="lib", src="src/qe/annotation", keep_path=False)

    def package_info(self):
        self.cpp_info.libs.extend(["QEAnnotation"])
