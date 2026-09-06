#pragma once

#include "Engine/Window.h"
namespace Engine {
class Input {
public:
  Input(Window &window);
  ~Input();
  bool IsKeyPressed(int keycode);
  bool IsMouseButtonPressed(int button);
  std::pair<float, float> GetMousePosition();
  float GetMouseX();
  float GetMouseY();

private:
  Window &m_Window;
};
} // namespace Engine
