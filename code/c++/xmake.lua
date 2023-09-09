
add_requires("raylib")
add_requires("catch2")
add_requires("spdlog")

add_rules("mode.debug", "mode.release")

target("test_raylib")
    set_kind("binary")
    add_files("tests/test_raylib.cpp")
    add_packages("raylib") 


target("test_catch2")
    set_kind("binary")
    add_files("tests/test_catch2.cpp")
    add_packages("catch2")  


target("test_spdlog")
    set_kind("binary")
    add_files("tests/test_spdlog.cpp")
    add_packages("spdlog")  


includes("src/")
