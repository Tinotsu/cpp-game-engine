#include "Engine.h"
#include "Engine/Application.h"
#include "Engine/Events/Event.h"
#include "Engine/ImGui/ImGuiLayer.h"

class ExampleLayer : public Engine::Layer {
public:
  ExampleLayer() : Layer("Example") {}

  void OnUpdate() override { ENGINE_INFO("ExampleLayer::Update"); }

  void OnEvent(Engine::Event &event) override {
    ENGINE_TRACE("{0}", event.ToString());
  }
};

class Sandbox : public Engine::Application {
public:
  Sandbox() {
    PushLayer(new ExampleLayer());
    PushOverlay(new Engine::ImGuiLayer(GetWindow()));
  }

  ~Sandbox() {}
};

Engine::Application *Engine::CreateApplication() { return new Sandbox(); }
