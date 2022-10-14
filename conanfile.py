from conan import ConanFile
from conan.tools.gnu import Autotools, AutotoolsToolchain, AutotoolsDeps
from conan.errors import ConanInvalidConfiguration

class MLXWrapperConan(ConanFile):
    name = "yaxi"
    version = "1.0"
    license = "MIT"
    author = "agagniere sid.xxdzs@gmail.com"
    url = "https://github.com/agagniere/yaxi"
    description = "Yet Another X11 Interface"
    topics = ("x11", "wayland")
    settings = ("os", "compiler", "arch")
    options = {
        "backend": ["minilibx", "xlib", "xcb", "wayland", "quartz"],
        "shared": [True, False],
        "fPIC" : [True, False],
        "optimisation": ['0', '1', '2', '3', 's', 'fast'],
        "debug": [True, False]
    }
    default_options = {
        "backend": "minilibx",
        "shared": False,
        "fPIC": False,
        "optimisation": '2',
        "debug": True
    }
    requires = ["libft/2.6"]
    exports_sources = 'include*', 'src*', 'Makefile'

    def requirements(self):
        dependency = {
            "wayland":  "wayland/1.21.0",
            "xlib":     "xorg/system",
            "xcb":      "xorg/system",
            "minilibx": "minilibx/1.3"
        }
        if str(self.options.backend) in dependency:
            self.requires(dependency[str(self.options.backend)])

    def configure(self):
        if self.options.shared:
            self.options.fPIC = True
            #self.options.rm_safe("fPIC")
        self.settings.rm_safe("compiler.libcxx")
        self.settings.rm_safe("compiler.cppstd")

    def generate(self):
        toolchain = AutotoolsToolchain(self)
        toolchain.extra_cflags += [f"-O{self.options.optimisation}", "-Wall", "-Wextra"]
        if self.options.debug:
            toolchain.extra_cflags += ["-g"]
        toolchain.generate()
        AutotoolsDeps(self).generate()

    def build(self):
        autotools = Autotools(self)
        autotools.make("shared" if self.options.shared else "static")

    def package(self):
        self.copy("*.h", dst="include", src="include")
        self.copy("libyaxi.*", dst="lib")

    def package_info(self):
        self.cpp_info.libs = ["yaxi"]
