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

# Where Xpdf tools are
set(XPDF_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/bin_external/xpdf")

# Where they should go in your build folder (next to your .exe)
set(XPDF_BUILD_DIR "$<TARGET_FILE_DIR:${PROJECT_NAME}>/xpdf_tools")

# Create a custom target to copy the directory every build
add_custom_target(copy_xpdf_tools ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${XPDF_SOURCE_DIR}"
    "${XPDF_BUILD_DIR}"
    COMMENT "Copying Xpdf binaries to build directory for standalone use"
)

