#pragma once

#include "Engine/Events/Event.h"
#include "Engine/Layer.h"
#include "Engine/Window.h"

namespace Engine {
class ImGuiLayer : public Layer {
public:
  ImGuiLayer(Window &window);
  ~ImGuiLayer();

  void OnAttach();
  void OnDettach();
  void OnUpdate();
  void OnEvent(Event &event);

private:
  Window &m_Window;
  float m_Time = 0.0f;
};

} // namespace Engine
