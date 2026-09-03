#pragma once

extern Engine::Application* Engine::CreateApplication();

int main(int argc, char** argv)
{
  Engine::Log::Init();
  ENGINE_CORE_WARN("Initialized Log!");
  int a = 5;
  ENGINE_CORE_INFO("Hello! Var={0}", a);

  printf("Engine Start\n");
  auto app = Engine::CreateApplication(); // auto tells C++ to infer the var type automatically
  app->Run();
  delete app;
}
