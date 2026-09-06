#include "Application.h"
#include "Engine/Layer.h"
#include "Input.h"
#include "Log.h"

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

Engine::Application::Application() {
  m_Window = std::unique_ptr<Window>(Window::Create());
  m_Window->SetEventCallBack(BIND_EVENT_FN(OnEvent));

  m_Input = std::unique_ptr<Input>(new Input(*m_Window));
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
  // ENGINE_CORE_INFO("{0}", e.ToString());

  for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
    (*--it)->OnEvent(e);
    if (e.IsHandled())
      break;
  }
}

void Engine::Application::Run() {
  while (m_Running) {

    glClear(GL_COLOR_BUFFER_BIT);

    for (Layer *layer : m_LayerStack)
      layer->OnUpdate();

    auto [x, y] = m_Input->GetMousePosition();
    // ENGINE_CORE_TRACE("{0}, {1}", x, y);

    m_Window->OnUpdate();
  };
}

bool Engine::Application::OnWindowClosed(WindowCloseEvent &e) {
  m_Running = false;
  return true;
}
