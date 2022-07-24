add_rules("mode.debug","mode.releasedbg", "mode.release")

if is_mode("release") then
    add_defines("NDEBUG")
    set_optimize("fastest")
end

set_arch("x64")
set_languages("cxx17")
add_requires("hopscotch-map", "catch2", "mariadb-connector-c")

target("async-db-cpp")
    set_kind("static")
    add_files("src/**.cpp")
    add_includedirs("src/", {public = true})
    add_headerfiles("src/**.hpp")
    add_packages("hopscotch-map", "mariadb-connector-c")

target("async-db-cpp-tests")
    set_kind("binary")
    add_files("tests/**.cpp")
    add_deps("async-db-cpp")
    add_packages("catch2", "hopscotch-map", "mariadb-connector-c")