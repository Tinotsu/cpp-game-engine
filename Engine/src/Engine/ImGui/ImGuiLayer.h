#pragma once

#include "Engine/Events/Event.h"
#include "Engine/Layer.h"
#include "Engine/Window.h"

namespace Engine {
class ImGuiLayer : public Layer {
public:
  ImGuiLayer(Window &window);
  ~ImGuiLayer();

  virtual void OnAttach() override;
  void OnImGuiRender();
  void Begin();
  void End();

private:
  Window &m_Window;
  float m_Time = 0.0f;
};

} // namespace Engine
