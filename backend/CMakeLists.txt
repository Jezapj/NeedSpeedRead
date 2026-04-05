find_package(Qt6 REQUIRED COMPONENTS Core)

add_library(backend)

target_sources(backend
    PRIVATE
        src/document_controller.cpp
    PUBLIC
        include/backend/document_controller.hpp
)

target_include_directories(backend
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(backend
    PUBLIC
        Qt6::Core
        Qt6::Widgets
        core
)
