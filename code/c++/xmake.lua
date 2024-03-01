



add_repositories("my-repo myrepo")
add_requires("raylibx")

add_rules("mode.debug", "mode.release")

includes("tests/")

includes("src/")


-- target("test_jsoncpp")
--     set_kind("binary")
--     add_files("tmp.cpp")
--     add_packages("raylibx")  
