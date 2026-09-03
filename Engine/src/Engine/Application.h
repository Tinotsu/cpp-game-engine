#pragma once

namespace Engine {
  class Application
  {
    public:
      Application();
      virtual ~Application();

      void Run();
  };

  // To be define in CLIENT
  Application* CreateApplication();
}
