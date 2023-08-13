add_library(
    shunting_yard
    STATIC
    tokens.cpp
    tokenizer.cpp
    validation.cpp
    algo.cpp
)

target_include_directories(
    shunting_yard
    PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)
