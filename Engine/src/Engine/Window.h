#pragma once

#include "enginepch.h"

#include "Engine/Events/Event.h"

#include <GLFW/glfw3.h>

namespace Engine {
  
  struct WindowProps
  {
    std::string Title;
    unsigned int Width;
    unsigned int Height;

    WindowProps(const std::string& title = "Engine",
        unsigned int width = 1280,
        unsigned int height = 720)
      : Title(title), Width(width), Height(height)
    {}
  };

  class Window
  {
    public:
      Window(const WindowProps& props);
      using EventCallBackFn = std::function<void(Event&)>;

      ~Window();

      void OnUpdate();

      unsigned int GetWidth() const { return m_Data.Width; };
      unsigned int GetHeight() const { return m_Data.Height; };

      //Window Attributes
      inline void SetEventCallBack(const EventCallBackFn& callback) { m_Data.EventCallBack = callback; };
      void SetVSync(bool enabled);
      bool IsVSync() const;

      static Window* Create(const WindowProps& props = WindowProps());

    private:
      void Init(const WindowProps& props);
      void Shutdown();
    private:
      GLFWwindow* m_Window;

      struct WindowData
      {
        std::string Title;
        unsigned int Width, Height;
        bool VSync;

        EventCallBackFn EventCallBack;
      };

      WindowData m_Data;
  };
}
