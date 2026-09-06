#include "Input.h"
#include "GLFW/glfw3.h"
#include "Window.h"

namespace Engine {

Input::Input(Window &window) : m_Window(window) {}

Input::~Input() {}

bool Input::IsKeyPressed(int keycode) {
  auto window = m_Window.GetNativeWindow();
  auto state = glfwGetKey(window, keycode);
  return state == GLFW_PRESS || state == GLFW_REPEAT;
}

bool Input::IsMouseButtonPressed(int button) {
  auto window = m_Window.GetNativeWindow();
  auto state = glfwGetMouseButton(window, button);
  return state == GLFW_PRESS;
}

std::pair<float, float> Input::GetMousePosition() {
  auto window = m_Window.GetNativeWindow();
  double xpos, ypos;
  glfwGetCursorPos(window, &xpos, &ypos);
  return {static_cast<float>(xpos), static_cast<float>(ypos)};
}

float Input::GetMouseX() {
  auto [x, y] = GetMousePosition();
  return x;
}
float Input::GetMouseY() {
  auto [x, y] = GetMousePosition();
  return y;
}
} // namespace Engine
