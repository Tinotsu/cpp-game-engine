#pragma once

#include "Engine/Events/ApplicationEvent.h"
#include "Engine/Layer.h"
#include "Engine/LayerStack.h"
#include "Events/Event.h"
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

private:
  bool OnWindowClosed(WindowCloseEvent &e);
  std::unique_ptr<Window> m_Window;
  bool m_Running = true;
  LayerStack m_LayerStack;
};

// To be define in CLIENT
Application *CreateApplication();
} // namespace Engine
