add_library(Engine STATIC
  src/Engine/Application.cpp
  src/Engine/Log.cpp
  src/Engine/Window.cpp
)

target_precompile_headers(Engine PRIVATE src/enginepch.h)

target_include_directories(Engine
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

add_subdirectory(vendor/spdlog)
target_link_libraries(Engine PUBLIC spdlog::spdlog)

add_subdirectory(vendor/glfw)
target_link_libraries(Engine PUBLIC glfw)
