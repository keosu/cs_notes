
package("raylibx")

    set_homepage("http://www.raylib.com")
    set_description("A simple and easy-to-use library to enjoy videogames programming.")

    if is_plat("macosx") and is_arch("x86_64") then
        add_urls("https://github.com/raysan5/raylib/releases/download/$(version).tar.gz", {version = function (version)
            if version:ge("3.5.0") then
                return version .. "/raylib-" .. version .. "_macos"
            else
                return version .. "/raylib-" .. version .. "-macOS"
            end
        end}) 
        add_versions("4.5.0", "63deb87ffc32e5eb2023ba763aaea2cb5f41bd37bbc07760651efe251bd76f3d")
    else
        add_urls("https://github.com/raysan5/raylib/archive/$(version).tar.gz",
                 "https://github.com/raysan5/raylib.git") 
        add_versions("4.5.0", "163378604f2293ea5ebf3238f50c8926addde72d1a6bc8998ac2e96074ba8af8")
    end

    if not (is_plat("macosx") and is_arch("x86_64")) then
        add_deps("cmake >=3.11")
    end

    if is_plat("macosx") then
        add_frameworks("CoreVideo", "CoreGraphics", "AppKit", "IOKit", "CoreFoundation", "Foundation")
    elseif is_plat("windows", "mingw") then
        add_syslinks("gdi32", "user32", "winmm", "shell32")
    elseif is_plat("linux") then
        add_syslinks("pthread", "dl", "m")
        add_deps("libx11", "libxrandr", "libxrender", "libxinerama", "libxcursor", "libxi", "libxfixes", "libxext")
    end
    add_deps("opengl", {optional = true})

    on_install("macosx|x86_64", function (package)
        os.cp("include/*.h", package:installdir("include"))
        os.cp("lib/libraylib.a", package:installdir("lib"))
    end)

    on_install("windows", "linux", "macosx|arm64", "mingw", function (package)
        local configs = {"-DBUILD_EXAMPLES=OFF"}
        table.insert(configs, "-DCMAKE_BUILD_TYPE=" .. (package:debug() and "Debug" or "Release"))
        table.insert(configs, "-DBUILD_SHARED_LIBS=" .. (package:config("shared") and "ON" or "OFF"))
        import("package.tools.cmake").install(package, configs, {packagedeps = {"libx11", "libxrender", "libxrandr", "libxinerama", "libxcursor", "libxi", "libxfixes", "libxext"}})
    end)

    on_test(function (package)
        assert(package:check_cxxsnippets({test = [[
            void test() {
                InitWindow(100, 100, "hello world!");
            }
        ]]}, {includes = {"raylib.h"}}))
    end)
