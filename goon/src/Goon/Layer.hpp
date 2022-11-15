#pragma once

#include <Goon/Core.h>
#include <Goon/Events/Event.hpp>

namespace Goon {
class GN_API Layer
{
public:
  Layer(const std::string &name = "Layer");
  virtual ~Layer();
  virtual void OnAttach() {}
  virtual void OnDetach() {}
  virtual void OnUpdate() {}
  virtual void OnEvent(Event &event) {}
  inline const std::string &GetName() const { return m_DebugName; }
protected:

  /**
   * @brief This is called debug name, as we really shouldn't be searching for names in release builds, it is frowned on per performance.
   */
  std::string m_DebugName;
};

} // namespace Goon
