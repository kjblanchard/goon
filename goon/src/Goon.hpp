/**
 * @file Goon.hpp
 * @brief This file should be included in the host application, so that it can be used.  Includes all of the proper include files, as well as generates the entrypoint.
 * @author Kevin Blanchard
 * @version 0.1.0
 * @date 2022-11-14
 */
#pragma once
#include <Goon/Application.hpp>
#include <Goon/Log.hpp>
#include <Goon/Layer.hpp>
#include <Goon/Input.hpp>
#include <Goon/Keycodes.hpp>
//Do we need this?  Probably.
#include <Goon/ImGui/ImGuiLayer.hpp>
//Entrypoint
#include "Goon/Entrypoint.hpp"
