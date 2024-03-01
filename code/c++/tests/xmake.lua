add_requires("raylib")
add_requires("catch2")
add_requires("spdlog")
add_requires("cereal")

target("test_raylib")
    set_kind("binary")
    add_files("test_raylib.cpp")
    add_packages("raylib") 


target("test_catch2")
    set_kind("binary")
    add_files("test_catch2.cpp")
    add_packages("catch2")  


target("test_spdlog")
    set_kind("binary")
    add_files("test_spdlog.cpp")
    add_packages("spdlog")  

target("test_cereal")
    set_kind("binary")
    add_files("test_cereal.cpp")
    add_packages("cereal")  
    set_languages("c++17")