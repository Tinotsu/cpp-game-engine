add_library(Engine STATIC
  src/Engine/Application.cpp
  src/Engine/Log.cpp
  src/Engine/Window.cpp
  src/Engine/Layer.cpp
  src/Engine/LayerStack.cpp
  src/Engine/ImGui/ImGuiLayer.cpp
  vendor/imgui/backends/imgui_impl_glfw.cpp
  vendor/imgui/backends/imgui_impl_opengl3.cpp
  vendor/imgui/imgui.cpp
  vendor/imgui/imgui_draw.cpp
  vendor/imgui/imgui_tables.cpp
  vendor/imgui/imgui_widgets.cpp
  vendor/imgui/imgui_demo.cpp
  vendor/glad/src/glad.c
)

target_precompile_headers(Engine PRIVATE src/enginepch.h)

target_include_directories(Engine
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glad/include
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui
)

add_subdirectory(vendor/glfw)
add_subdirectory(vendor/spdlog)
find_package(OpenGL REQUIRED)
target_link_libraries(Engine PUBLIC 
  spdlog::spdlog
  glfw
  OpenGL::GL
)

set_source_files_properties(
  vendor/glad/src/glad.c
  PROPERTIES SKIP_PRECOMPILE_HEADERS ON
)
