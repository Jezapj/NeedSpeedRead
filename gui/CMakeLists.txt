find_package(Qt6 REQUIRED COMPONENTS Quick Widgets)

qt_standard_project_setup()

qt_add_executable(NeedSpeedRead
    main.cpp
)

# Only embed QML as a module in non-Debug builds
if (NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
    qt_add_qml_module(NeedSpeedRead
        URI NeedSpeedRead
        VERSION 1.0
        QML_FILES
            qml/Main.qml
    )
endif()

target_link_libraries(NeedSpeedRead
    PRIVATE
        Qt6::Quick
        Qt6::Widgets
        backend
)

# In Debug, copy QML files next to the executable for hot iteration
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_custom_target(copy_qml ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_SOURCE_DIR}/gui/qml
                $<TARGET_FILE_DIR:NeedSpeedRead>/qml
    )
endif()
