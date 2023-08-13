add_subdirectory(shunting_yard)
add_subdirectory(ui)

add_executable(
    ${PROJECT_NAME}
    main.cpp
    config.cpp
    analysis.cpp
)

target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
        shunting_yard
        ui
        curses
)
