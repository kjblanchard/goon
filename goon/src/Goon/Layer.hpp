/**
 * @file Layer.hpp
 * @brief Base class for all layers
 * @author Kevin Blanchard
 * @version 0.1.0
 * @date 2022-11-14
 */
#pragma once
#include <Goon/Core.hpp>
#include <Goon/Events/Event.hpp>

namespace Goon {
  /**
   * @brief Abstract class for all layers
   */
class GN_API Layer
{

public:
  /**
   * @brief A layer that will be updated on every tick
   *
   * @param name The layer name, not really required.
   */
  Layer(const std::string &name = "Layer");
  virtual ~Layer();
  virtual void OnAttach() {}
  virtual void OnDetach() {}
  virtual void OnImGuiRender() {}
  /**
   * @brief What should happen on each update of the layer
   */
  virtual void OnUpdate() {}
  /**
   * @brief How should the layer handle events
   *
   * @param event The event to handle
   */
  virtual void OnEvent(Event&) {}
  /**
   * @brief Gets the layers name
   *
   * @return The layer name
   */
  inline const std::string &GetName() const { return m_DebugName; }
protected:

  /**
   * @brief This is called debug name, as we really shouldn't be searching for names in release builds, it is frowned on per performance.
   */
  std::string m_DebugName;
};

} // namespace Goon
