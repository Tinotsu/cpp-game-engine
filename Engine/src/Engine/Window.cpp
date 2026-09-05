#include <glad/glad.h>
#include "Window.h"
#include "Engine/Core.h"
#include "Engine/Events/ApplicationEvent.h"
#include "Engine/Events/KeyEvent.h"
#include "Engine/Events/MouseEvent.h"
#include "Engine/Log.h"

namespace Engine {

static bool s_GLFWInitialized = false;

static void GLFWErrorCallback(int error, const char *description) {
  ENGINE_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
}

Window *Window::Create(const WindowProps &props) { return new Window(props); }

GLFWwindow *Window::GetNativeWindow() const { return m_Window; }

Window::Window(const WindowProps &props) { Init(props); }

Window::~Window() { Shutdown(); }

void Window::Init(const WindowProps &props) {
  m_Data.Title = props.Title;
  m_Data.Width = props.Width;
  m_Data.Height = props.Height;

  ENGINE_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width,
                   props.Height);

  if (!s_GLFWInitialized) {
    int success = glfwInit();
    ENGINE_CORE_ASSERT(success, "Could not initialize GLFW!");

    glfwSetErrorCallback(GLFWErrorCallback);
    s_GLFWInitialized = true;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  m_Window = glfwCreateWindow((int)props.Width, (int)props.Height,
                              m_Data.Title.c_str(), nullptr, nullptr);
  glfwMakeContextCurrent(m_Window);
  int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
  ENGINE_CORE_ASSERT(status, "Failed to initialize Glad !")
  glfwSetWindowUserPointer(m_Window, &m_Data);
  SetVSync(true);

  // Set GLFW callbacks
  glfwSetWindowSizeCallback(
      m_Window, [](GLFWwindow *window, int width, int height) {
        WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
        data.Height = height;
        data.Width = width;

        WindowResizeEvent event(width, height);
        data.EventCallBack(event);
      });

  glfwSetWindowCloseCallback(m_Window, [](GLFWwindow *window) {
    WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
    WindowCloseEvent event;
    data.EventCallBack(event);
  });

  glfwSetKeyCallback(m_Window, [](GLFWwindow *window, int key, int scancode,
                                  int action, int mods) {
    WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);

    switch (action) {
    case GLFW_PRESS: {
      KeyPressedEvent event(key, 0);
      data.EventCallBack(event);
      break;
    }
    case GLFW_RELEASE: {
      KeyReleasedEvent event(key);
      data.EventCallBack(event);
      break;
    }
    case GLFW_REPEAT: {
      KeyPressedEvent event(key, 1);
      data.EventCallBack(event);
      break;
    }
    }
  });

  glfwSetMouseButtonCallback(
      m_Window, [](GLFWwindow *window, int button, int action, int mods) {
        WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
        switch (action) {
        case GLFW_PRESS: {
          MouseButtonPressedEvent event(button);
          data.EventCallBack(event);
          break;
        }
        case GLFW_RELEASE: {
          MouseButtonReleasedEvent event(button);
          data.EventCallBack(event);
          break;
        }
        }
      });

  glfwSetScrollCallback(
      m_Window, [](GLFWwindow *window, double xOffset, double yOffset) {
        WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);

        MouseScrolledEvent event((float)xOffset, (float)yOffset);
        data.EventCallBack(event);
      });

  glfwSetCursorPosCallback(
      m_Window, [](GLFWwindow *window, double xPos, double yPos) {
        WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);

        MouseMovedEvent event((float)xPos, (float)yPos);
        data.EventCallBack(event);
      });
};

void Window::Shutdown() { glfwDestroyWindow(m_Window); }

void Window::OnUpdate() {
  glfwPollEvents();
  glfwSwapBuffers(m_Window);
}

void Window::SetVSync(bool enabled) {
  if (enabled)
    glfwSwapInterval(1);
  else
    glfwSwapInterval(0);

  m_Data.VSync = enabled;
}

bool Window::IsVSync() const { return m_Data.VSync; }
} // namespace Engine
