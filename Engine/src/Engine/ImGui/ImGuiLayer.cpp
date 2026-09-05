#include "ImGuiLayer.h"
#include "GLFW/glfw3.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "imgui.h"

namespace Engine {
ImGuiLayer::ImGuiLayer(Window &window)
    : Layer("ImGuiLayer"), m_Window(window) {}

ImGuiLayer::~ImGuiLayer() {}

void ImGuiLayer::OnAttach() {
  ImGui::CreateContext();
  ImGui::StyleColorsDark();

  ImGuiIO &io = ImGui::GetIO();
  io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
  io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

  GLFWwindow *window = m_Window.GetNativeWindow();

  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init("#version 410");
}

void ImGuiLayer::OnDettach() {}

void ImGuiLayer::OnEvent(Event &event) {}

void ImGuiLayer::OnUpdate() {
  ImGuiIO &io = ImGui::GetIO();
  GLFWwindow *window = m_Window.GetNativeWindow();
  io.DisplaySize =
      ImVec2((float)m_Window.GetWidth(), (float)m_Window.GetHeight());

  float time = (float)glfwGetTime();
  io.DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.0f / 60.0f);

  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();

  static bool show = true;
  ImGui::ShowDemoWindow(&show);

  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

} // namespace Engine
