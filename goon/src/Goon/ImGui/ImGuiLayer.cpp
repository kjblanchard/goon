#include "Goon/Layer.hpp"
#include "Goon/Log.hpp"
#include "imgui.h"
#include <GLFW/glfw3.h>
#include <gnpch.hpp>
#include <Goon/ImGui/ImGuiLayer.hpp>
#include <Goon/Application.hpp>
#include <Platform/OpenGL/imgui_impl_opengl3.h>
#include <Platform/OpenGL/imgui_impl_opengl3_loader.h>


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

    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGuiIO& io = ImGui::GetIO();
    io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
    io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
    auto initialized = ImGui_ImplOpenGL3_Init("#version 150");
    GN_CORE_INFO("{0} is the init status",initialized);

    //Test for proper sizing
    int scale = 2;
    ImFontConfig cfg;
    cfg.SizePixels = 13.0f * scale;
    io.Fonts->AddFontDefault(&cfg);
    io.FontGlobalScale = 1.0f / scale;

  }
  void ImGuiLayer::OnDetach()
  {

  }
  void ImGuiLayer::OnUpdate()
  {

    ImGuiIO& io = ImGui::GetIO();
    auto& app = Application::Get();
    auto thing =  ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());
    GN_CORE_INFO("{0} is the x and {1} is the y", thing.x, thing.y);
    io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

    float time = (float)glfwGetTime();
    io.DeltaTime = m_time > 0 ? (time - m_time) : (1.0f / 60.0f);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();
    //GN_CORE_ASSERT(0, "Dead");
    
    m_time = time;
    static bool show = true;
    ImGui::ShowDemoWindow(&show);
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

  }
  void ImGuiLayer::OnEvent(Event&) 
  {

  }

}

