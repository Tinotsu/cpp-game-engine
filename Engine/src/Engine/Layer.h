#pragma once

#include "Engine/Events/Event.h"

namespace Engine {
class Layer {
public:
  Layer(const std::string &name = "Layer");
  virtual ~Layer();

  virtual void OnAttach() {}
  virtual void OnDettach() {}
  virtual void OnUpdate() {}
  virtual void OnEvent(Event &event) {}

  inline const std::string &GetName() const { return m_DebugName; }

protected:
  std::string m_DebugName;
};

} // namespace Engine
