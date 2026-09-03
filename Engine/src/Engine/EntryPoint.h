#pragma once

extern Engine::Application* Engine::CreateApplication();

int main(int argc, char** argv)
{
  printf("Engine Start\n");
  auto app = Engine::CreateApplication(); // auto tells C++ to infer the var type automatically
  app->Run();
  delete app;
}
