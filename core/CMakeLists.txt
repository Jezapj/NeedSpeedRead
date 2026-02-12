add_library(core)

target_sources(core
    PRIVATE
        src/document.cpp
        src/parser.cpp
    PUBLIC
        include/core/document.hpp
        include/core/parser.hpp
)

target_include_directories(core
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
