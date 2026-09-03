add_library(Engine STATIC
  src/Engine/Application.cpp
)

target_include_directories(Engine
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)
