#include "Application.h"
#include "Log.h"

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

Engine::Application::Application() {
  m_Window = std::unique_ptr<Window>(Window::Create());
  m_Window->SetEventCallBack(BIND_EVENT_FN(OnEvent));
}

Engine::Application::~Application() {}

void Engine::Application::OnEvent(Event &e) {
  EventDispatcher dispatcher(e);
  dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClosed));
  ENGINE_CORE_INFO("{0}", e.ToString());
}

void Engine::Application::Run() {
  while (m_Running) {
    m_Window->OnUpdate();
  };
}

bool Engine::Application::OnWindowClosed(WindowCloseEvent &e) {
  m_Running = false;
  return true;
}
