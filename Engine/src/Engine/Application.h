#pragma once

#include "Engine/Events/ApplicationEvent.h"
#include "Engine/ImGui/ImGuiLayer.h"
#include "Engine/Layer.h"
#include "Engine/LayerStack.h"
#include "Events/Event.h"
#include "Input.h"
#include "Window.h"

namespace Engine {
class Application {
public:
  Application();
  virtual ~Application();

  void Run();

  void OnEvent(Event &e);

  void PushLayer(Layer *layer);
  void PushOverlay(Layer *layer);

  inline Window &GetWindow() { return *m_Window; }

private:
  bool OnWindowClosed(WindowCloseEvent &e);
  std::unique_ptr<Window> m_Window;
  ImGuiLayer *m_ImGuiLayer;
  std::unique_ptr<Input> m_Input;
  bool m_Running = true;
  LayerStack m_LayerStack;
};

// To be define in CLIENT
Application *CreateApplication();
} // namespace Engine
