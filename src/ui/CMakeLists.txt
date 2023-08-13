add_library(
    ui
    STATIC
    menu.cpp
    actions.cpp
)

target_include_directories(
    ui
    PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)
