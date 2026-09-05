#pragma once

#include "Engine/Events/ApplicationEvent.h"
#include "Events/Event.h"
#include "Window.h"

namespace Engine {
class Application {
public:
  Application();
  virtual ~Application();

  void Run();

  void OnEvent(Event &e);

private:
  bool OnWindowClosed(WindowCloseEvent &e);
  std::unique_ptr<Window> m_Window;
  bool m_Running = true;
};

// To be define in CLIENT
Application *CreateApplication();
} // namespace Engine
