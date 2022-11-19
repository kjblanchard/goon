//This is temporary?
#include "Platform/MacWindow.hpp"
#include <gnpch.hpp>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <Goon/Layer.hpp>
#include <Goon/Log.hpp>
#include <Goon/ImGui/ImGuiLayer.hpp>
#include <Goon/Application.hpp>
#include <Platform/OpenGL/imgui_impl_opengl3.h>
#include <Platform/OpenGL/imgui_impl_opengl3_loader.h>


namespace Goon {

  static const char* ImGui_ImplGlfw_GetClipboardText(void* user_data)
  {
    return glfwGetClipboardString((GLFWwindow*)user_data);
  }

  static void ImGui_ImplGlfw_SetClipboardText(void* user_data, const char* text)
  {
    glfwSetClipboardString((GLFWwindow*)user_data, text);
  }
  static int ImGui_ImplGlfw_KeyToModifier(int key)
  {
    if (key == GLFW_KEY_LEFT_CONTROL || key == GLFW_KEY_RIGHT_CONTROL)
      return GLFW_MOD_CONTROL;
    if (key == GLFW_KEY_LEFT_SHIFT || key == GLFW_KEY_RIGHT_SHIFT)
      return GLFW_MOD_SHIFT;
    if (key == GLFW_KEY_LEFT_ALT || key == GLFW_KEY_RIGHT_ALT)
      return GLFW_MOD_ALT;
    if (key == GLFW_KEY_LEFT_SUPER || key == GLFW_KEY_RIGHT_SUPER)
      return GLFW_MOD_SUPER;
    return 0;
  }


  static ImGuiKey ImGui_ImplGlfw_KeyToImGuiKey(int key)
  {
    switch (key)
    {
      case GLFW_KEY_TAB: return ImGuiKey_Tab;
      case GLFW_KEY_LEFT: return ImGuiKey_LeftArrow;
      case GLFW_KEY_RIGHT: return ImGuiKey_RightArrow;
      case GLFW_KEY_UP: return ImGuiKey_UpArrow;
      case GLFW_KEY_DOWN: return ImGuiKey_DownArrow;
      case GLFW_KEY_PAGE_UP: return ImGuiKey_PageUp;
      case GLFW_KEY_PAGE_DOWN: return ImGuiKey_PageDown;
      case GLFW_KEY_HOME: return ImGuiKey_Home;
      case GLFW_KEY_END: return ImGuiKey_End;
      case GLFW_KEY_INSERT: return ImGuiKey_Insert;
      case GLFW_KEY_DELETE: return ImGuiKey_Delete;
      case GLFW_KEY_BACKSPACE: return ImGuiKey_Backspace;
      case GLFW_KEY_SPACE: return ImGuiKey_Space;
      case GLFW_KEY_ENTER: return ImGuiKey_Enter;
      case GLFW_KEY_ESCAPE: return ImGuiKey_Escape;
      case GLFW_KEY_APOSTROPHE: return ImGuiKey_Apostrophe;
      case GLFW_KEY_COMMA: return ImGuiKey_Comma;
      case GLFW_KEY_MINUS: return ImGuiKey_Minus;
      case GLFW_KEY_PERIOD: return ImGuiKey_Period;
      case GLFW_KEY_SLASH: return ImGuiKey_Slash;
      case GLFW_KEY_SEMICOLON: return ImGuiKey_Semicolon;
      case GLFW_KEY_EQUAL: return ImGuiKey_Equal;
      case GLFW_KEY_LEFT_BRACKET: return ImGuiKey_LeftBracket;
      case GLFW_KEY_BACKSLASH: return ImGuiKey_Backslash;
      case GLFW_KEY_RIGHT_BRACKET: return ImGuiKey_RightBracket;
      case GLFW_KEY_GRAVE_ACCENT: return ImGuiKey_GraveAccent;
      case GLFW_KEY_CAPS_LOCK: return ImGuiKey_CapsLock;
      case GLFW_KEY_SCROLL_LOCK: return ImGuiKey_ScrollLock;
      case GLFW_KEY_NUM_LOCK: return ImGuiKey_NumLock;
      case GLFW_KEY_PRINT_SCREEN: return ImGuiKey_PrintScreen;
      case GLFW_KEY_PAUSE: return ImGuiKey_Pause;
      case GLFW_KEY_KP_0: return ImGuiKey_Keypad0;
      case GLFW_KEY_KP_1: return ImGuiKey_Keypad1;
      case GLFW_KEY_KP_2: return ImGuiKey_Keypad2;
      case GLFW_KEY_KP_3: return ImGuiKey_Keypad3;
      case GLFW_KEY_KP_4: return ImGuiKey_Keypad4;
      case GLFW_KEY_KP_5: return ImGuiKey_Keypad5;
      case GLFW_KEY_KP_6: return ImGuiKey_Keypad6;
      case GLFW_KEY_KP_7: return ImGuiKey_Keypad7;
      case GLFW_KEY_KP_8: return ImGuiKey_Keypad8;
      case GLFW_KEY_KP_9: return ImGuiKey_Keypad9;
      case GLFW_KEY_KP_DECIMAL: return ImGuiKey_KeypadDecimal;
      case GLFW_KEY_KP_DIVIDE: return ImGuiKey_KeypadDivide;
      case GLFW_KEY_KP_MULTIPLY: return ImGuiKey_KeypadMultiply;
      case GLFW_KEY_KP_SUBTRACT: return ImGuiKey_KeypadSubtract;
      case GLFW_KEY_KP_ADD: return ImGuiKey_KeypadAdd;
      case GLFW_KEY_KP_ENTER: return ImGuiKey_KeypadEnter;
      case GLFW_KEY_KP_EQUAL: return ImGuiKey_KeypadEqual;
      case GLFW_KEY_LEFT_SHIFT: return ImGuiKey_LeftShift;
      case GLFW_KEY_LEFT_CONTROL: return ImGuiKey_LeftCtrl;
      case GLFW_KEY_LEFT_ALT: return ImGuiKey_LeftAlt;
      case GLFW_KEY_LEFT_SUPER: return ImGuiKey_LeftSuper;
      case GLFW_KEY_RIGHT_SHIFT: return ImGuiKey_RightShift;
      case GLFW_KEY_RIGHT_CONTROL: return ImGuiKey_RightCtrl;
      case GLFW_KEY_RIGHT_ALT: return ImGuiKey_RightAlt;
      case GLFW_KEY_RIGHT_SUPER: return ImGuiKey_RightSuper;
      case GLFW_KEY_MENU: return ImGuiKey_Menu;
      case GLFW_KEY_0: return ImGuiKey_0;
      case GLFW_KEY_1: return ImGuiKey_1;
      case GLFW_KEY_2: return ImGuiKey_2;
      case GLFW_KEY_3: return ImGuiKey_3;
      case GLFW_KEY_4: return ImGuiKey_4;
      case GLFW_KEY_5: return ImGuiKey_5;
      case GLFW_KEY_6: return ImGuiKey_6;
      case GLFW_KEY_7: return ImGuiKey_7;
      case GLFW_KEY_8: return ImGuiKey_8;
      case GLFW_KEY_9: return ImGuiKey_9;
      case GLFW_KEY_A: return ImGuiKey_A;
      case GLFW_KEY_B: return ImGuiKey_B;
      case GLFW_KEY_C: return ImGuiKey_C;
      case GLFW_KEY_D: return ImGuiKey_D;
      case GLFW_KEY_E: return ImGuiKey_E;
      case GLFW_KEY_F: return ImGuiKey_F;
      case GLFW_KEY_G: return ImGuiKey_G;
      case GLFW_KEY_H: return ImGuiKey_H;
      case GLFW_KEY_I: return ImGuiKey_I;
      case GLFW_KEY_J: return ImGuiKey_J;
      case GLFW_KEY_K: return ImGuiKey_K;
      case GLFW_KEY_L: return ImGuiKey_L;
      case GLFW_KEY_M: return ImGuiKey_M;
      case GLFW_KEY_N: return ImGuiKey_N;
      case GLFW_KEY_O: return ImGuiKey_O;
      case GLFW_KEY_P: return ImGuiKey_P;
      case GLFW_KEY_Q: return ImGuiKey_Q;
      case GLFW_KEY_R: return ImGuiKey_R;
      case GLFW_KEY_S: return ImGuiKey_S;
      case GLFW_KEY_T: return ImGuiKey_T;
      case GLFW_KEY_U: return ImGuiKey_U;
      case GLFW_KEY_V: return ImGuiKey_V;
      case GLFW_KEY_W: return ImGuiKey_W;
      case GLFW_KEY_X: return ImGuiKey_X;
      case GLFW_KEY_Y: return ImGuiKey_Y;
      case GLFW_KEY_Z: return ImGuiKey_Z;
      case GLFW_KEY_F1: return ImGuiKey_F1;
      case GLFW_KEY_F2: return ImGuiKey_F2;
      case GLFW_KEY_F3: return ImGuiKey_F3;
      case GLFW_KEY_F4: return ImGuiKey_F4;
      case GLFW_KEY_F5: return ImGuiKey_F5;
      case GLFW_KEY_F6: return ImGuiKey_F6;
      case GLFW_KEY_F7: return ImGuiKey_F7;
      case GLFW_KEY_F8: return ImGuiKey_F8;
      case GLFW_KEY_F9: return ImGuiKey_F9;
      case GLFW_KEY_F10: return ImGuiKey_F10;
      case GLFW_KEY_F11: return ImGuiKey_F11;
      case GLFW_KEY_F12: return ImGuiKey_F12;
      default: return ImGuiKey_None;
    }
  }

  static void ImGui_ImplGlfw_UpdateKeyModifiers(int mods, bool pressed)
  {
    ImGuiIO& io = ImGui::GetIO();
    switch(mods) 
    {
      case GLFW_MOD_CONTROL:
        io.AddKeyEvent(ImGuiKey_ModCtrl,pressed);
        break;
      case GLFW_MOD_SHIFT:
        io.AddKeyEvent(ImGuiKey_ModShift,pressed);
        break;
      case GLFW_MOD_ALT:
        io.AddKeyEvent(ImGuiKey_ModAlt,pressed);
        break;
      case GLFW_MOD_SUPER:
        io.AddKeyEvent(ImGuiKey_ModSuper,pressed);
        break;
    }

  }

  ImGuiLayer::ImGuiLayer()
    :Layer("ImGuiLayer")
  {

  }
  ImGuiLayer::~ImGuiLayer()
  {

  }
  void ImGuiLayer::OnAttach()
  {

    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGuiIO& io = ImGui::GetIO();
    io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
    io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
    ImGui_ImplOpenGL3_Init("#version 150");
    io.SetClipboardTextFn = ImGui_ImplGlfw_SetClipboardText;
    io.GetClipboardTextFn = ImGui_ImplGlfw_GetClipboardText;
  }
  void ImGuiLayer::OnDetach()
  {

  }
  void ImGuiLayer::OnUpdate()
  {

    ImGuiIO& io = ImGui::GetIO();
    auto& app = Application::Get();
    auto& gwindow = app.GetWindow();
    auto& mwindow = gwindow.GetNativeWindow<MacWindow>();
    auto glfwwindow = mwindow.GetGlfwWindow();
    float scalex, scaley;
    int display_w, display_h;
    glfwGetWindowContentScale(glfwwindow, &scalex, &scaley);
    glfwGetFramebufferSize(glfwwindow, &display_w, &display_h);
    io.DisplaySize = ImVec2(display_w/scalex, display_h/scaley);
    io.DisplayFramebufferScale = ImVec2(scalex, scaley);

    float time = (float)glfwGetTime();
    io.DeltaTime = m_time > 0 ? (time - m_time) : (1.0f / 60.0f);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();
    m_time = time;
    static bool show = true;
    ImGui::ShowDemoWindow(&show);
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

  }
  bool ImGuiLayer::OnMouseMove(MouseMovedEvent &e)
  {
    ImGuiIO& io = ImGui::GetIO();
    io.AddMousePosEvent(e.GetX(), e.GetY());
    return false;

  }

  bool ImGuiLayer::OnMouseButtonPressed(MouseButtonPressedEvent &e)
  {
    ImGuiIO& io = ImGui::GetIO();
    io.AddMouseButtonEvent(e.GetMouseButton(), true);
    return true;

  }

  bool ImGuiLayer::OnMouseButtonReleased(MouseButtonReleasedEvent &e)
  {
    ImGuiIO& io = ImGui::GetIO();
    io.AddMouseButtonEvent(e.GetMouseButton(), false);
    return false;

  }

  bool ImGuiLayer::OnMouseScrolled(MouseScrolledEvent &e)
  {
    ImGuiIO& io = ImGui::GetIO();
    io.MouseWheel += e.GetYOffset();
    io.MouseWheelH += e.GetXOffset();
    return false;

  }

  bool ImGuiLayer::OnKeyPressed(KeyPressedEvent &e)
  {
    ImGuiIO& io = ImGui::GetIO();
    int keycode = e.GetKeyCode();
    int mods = ImGui_ImplGlfw_KeyToModifier(keycode);
    if(mods)
    {
      ImGui_ImplGlfw_UpdateKeyModifiers(mods, true);
      return false;
    }
    auto imGuiKey = ImGui_ImplGlfw_KeyToImGuiKey(keycode);
    io.AddKeyEvent(imGuiKey, true);
    return false;

  }
  bool ImGuiLayer::OnKeyReleased(KeyReleasedEvent &e)
  {
    ImGuiIO& io = ImGui::GetIO();
    int keycode = e.GetKeyCode();
    int mods =ImGui_ImplGlfw_KeyToModifier(keycode);
    if(mods)
    {
      ImGui_ImplGlfw_UpdateKeyModifiers(mods, false);
      return false;
    }
    auto imGuiKey = ImGui_ImplGlfw_KeyToImGuiKey(keycode);
    io.AddKeyEvent(imGuiKey, false);
    return false;

  }

  bool ImGuiLayer::OnKeyTyped(KeyTypedEvent &e)
  {
    ImGuiIO& io = ImGui::GetIO();
    io.AddInputCharacter(e.GetKeyCode());
    return false;
  }


  void ImGuiLayer::OnEvent(Event& e) 
  {
    auto dispatcher = EventDispatcher(e);
    dispatcher.Dispatch<MouseMovedEvent>(GN_BIND_EVENT_FN(&ImGuiLayer::OnMouseMove));
    dispatcher.Dispatch<MouseButtonPressedEvent>(GN_BIND_EVENT_FN(&ImGuiLayer::OnMouseButtonPressed));
    dispatcher.Dispatch<MouseScrolledEvent>(GN_BIND_EVENT_FN(&ImGuiLayer::OnMouseScrolled));
    dispatcher.Dispatch<MouseButtonReleasedEvent>(GN_BIND_EVENT_FN(&ImGuiLayer::OnMouseButtonReleased));
    dispatcher.Dispatch<KeyPressedEvent>(GN_BIND_EVENT_FN(&ImGuiLayer::OnKeyPressed));
    dispatcher.Dispatch<KeyReleasedEvent>(GN_BIND_EVENT_FN(&ImGuiLayer::OnKeyReleased));
    dispatcher.Dispatch<KeyTypedEvent>(GN_BIND_EVENT_FN(&ImGuiLayer::OnKeyTyped));
  }

}
