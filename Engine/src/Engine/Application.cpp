#include "Application.h"
#include "Engine/Layer.h"
#include "Log.h"

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

Engine::Application::Application() {
  m_Window = std::unique_ptr<Window>(Window::Create());
  m_Window->SetEventCallBack(BIND_EVENT_FN(OnEvent));
}

Engine::Application::~Application() {}

void Engine::Application::PushLayer(Layer *layer) {
  m_LayerStack.PushLayer(layer);
}

void Engine::Application::PushOverlay(Layer *layer) {
  m_LayerStack.PushOverlay(layer);
}

void Engine::Application::OnEvent(Event &e) {
  EventDispatcher dispatcher(e);
  dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClosed));
  ENGINE_CORE_INFO("{0}", e.ToString());

  for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
    (*--it)->OnEvent(e);
    if (e.IsHandled())
      break;
  }
}

void Engine::Application::Run() {
  while (m_Running) {
    m_Window->OnUpdate();

    for (Layer *layer : m_LayerStack)
      layer->OnUpdate();
  };
}

bool Engine::Application::OnWindowClosed(WindowCloseEvent &e) {
  m_Running = false;
  return true;
}
