#include "Platform/MacWindow.hpp"
#include <gnpch.hpp>
//TODO I should be able to remove glfw after moving to the imgui docking.
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <Goon/Layer.hpp>
#include <Goon/Log.hpp>
#include <Goon/ImGui/ImGuiLayer.hpp>
#include <Goon/Application.hpp>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>


namespace Goon {

  ImGuiLayer::ImGuiLayer()
    :Layer("ImGuiLayer")
  {

  }
  ImGuiLayer::~ImGuiLayer()
  {

  }
  void ImGuiLayer::OnAttach()
  {

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
//    io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
//    io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
//    io.BackendFlags |= ImGuiBackendFlags_PlatformHasViewports;
    ImGui_ImplOpenGL3_Init("#version 150");
//    io.SetClipboardTextFn = ImGui_ImplGlfw_SetClipboardText;
//    io.GetClipboardTextFn = ImGui_ImplGlfw_GetClipboardText;
        // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
      style.WindowRounding = 0.0f;
      style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    Application& app = Application::Get();
    GLFWwindow* window = app.GetWindow().GetNativeWindow<MacWindow>().GetGlfwWindow();

    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    //ImGui_ImplOpenGL3_Init("#version 410");
  }
  void ImGuiLayer::OnDetach()
  {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

  }

  void ImGuiLayer::OnImGuiRender()
  {
    static bool show = true;
    ImGui::ShowDemoWindow(&show);

  }

  void ImGuiLayer::OnUpdate()
  {

//    ImGuiIO& io = ImGui::GetIO();
//    auto& app = Application::Get();
//    auto& window = app.GetWindow();
//    auto [scalex, scaley] = window.GetWindowContentScaling();
//    auto [displayw, displayh] = window.GetWindowFrameBufferSize();
//
//    io.DisplaySize = ImVec2(displayw/scalex, displayh/scaley);
//    io.DisplayFramebufferScale = ImVec2(scalex, scaley);
//
//    float time = (float)glfwGetTime();
//    io.DeltaTime = m_time > 0 ? (time - m_time) : (1.0f / 60.0f);
//
//    ImGui_ImplOpenGL3_NewFrame();
//    ImGui::NewFrame();
//    m_time = time;
//    static bool show = true;
//    ImGui::ShowDemoWindow(&show);
//    ImGui::Render();
//    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

  }
  void ImGuiLayer::Begin()
  {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

  }

  void ImGuiLayer::End()
  {
    ImGuiIO& io = ImGui::GetIO();
    Application& app = Application::Get();
    io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

    // Rendering
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
      GLFWwindow* backup_current_context = glfwGetCurrentContext();
      ImGui::UpdatePlatformWindows();
      ImGui::RenderPlatformWindowsDefault();
      glfwMakeContextCurrent(backup_current_context);
    }

  }

}

