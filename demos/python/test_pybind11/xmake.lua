 

add_rules("mode.debug", "mode.release")
add_requires("pybind11")
set_optimize("fastest")

-- target("CallBack")
--     set_kind("shared")
--     add_files("callback.cpp")
--     set_extension(".pyd")
--     add_packages("pybind11")
--     after_build(
--         function(target)
--             local targetfile = target:targetfile()
--             -- os.cp(targetfile, path.join("./", path.filename(targetfile):sub(4)))
--             os.cp(targetfile, path.join("./", path.filename(targetfile)))
--         end
--     )

target("CallBack")
    add_packages("pybind11")
    set_kind("shared")
    set_extension(".pyd")
    add_files("callback.cpp")
    after_build(
        function(target)
            local targetfile = target:targetfile()
            os.cp(targetfile, path.join("./", path.filename(targetfile)))
        end
    )
