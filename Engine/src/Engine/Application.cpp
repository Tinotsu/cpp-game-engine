#include "Application.h"

Engine::Application::Application()
{
  m_Window = std::unique_ptr<Window>(Window::Create());

}

Engine::Application::~Application()
{

}

void Engine::Application::Run()
{
  while (m_Running)
  {
    m_Window->OnUpdate();
  };
}
