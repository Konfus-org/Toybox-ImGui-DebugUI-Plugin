#include "ImGuiDebugViewLayer.h"
#include <Tbx/App/App.h>
#include <Tbx/Input/Input.h>
#include <Tbx/Events/EventCoordinator.h>
#include <Tbx/TBS/World.h>
#include <Tbx/Graphics/Camera.h>
#include <Tbx/Math/Transform.h>
#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_opengl3.h>
#include <SDL3/SDL.h>

namespace ImGuiDebugView
{
    static bool OnSDLEvent(void*, SDL_Event* event)
    {
        ImGui_ImplSDL3_ProcessEvent(event); // forwards to ImGui, does NOT consume
        return false;
    }

    void ImGuiDebugViewLayer::OnLoad()
    {
        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
    }

    void ImGuiDebugViewLayer::OnUnload()
    {
        ImGui::DestroyContext();
    }

    void ImGuiDebugViewLayer::OnAttach()
    {
        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        //ImGui::StyleColorsLight();

        // Init size
        const auto mainWindow = Tbx::App::GetInstance()->GetMainWindow();
        if (mainWindow.expired() || !mainWindow.lock())
        {
            TBX_ASSERT(false, "Cannot initialize debug view! Main window weak ptr isn't valid...");
            return;
        }
        _windowResolution = mainWindow.lock()->GetSize();
        const auto glContext = SDL_GL_GetCurrentContext();
        if (glContext == nullptr)
        {
            TBX_ASSERT(false, "Cannot initialize debug view! OpenGL hasn't been initialized yet...");
            return;
        }

        auto* nativeWindow = (SDL_Window*)mainWindow.lock()->GetNativeWindow();
        if (nativeWindow == nullptr)
        {
            TBX_ASSERT(false, "Cannot initialize debug view! Native window hasn't been initialized yet...");
            return;
        }

        ImGui_ImplSDL3_InitForOpenGL(nativeWindow, glContext);
        ImGui_ImplOpenGL3_Init();

        // Sub to events
        Tbx::EventCoordinator::Subscribe(this, &ImGuiDebugViewLayer::OnFrameRendered);
        Tbx::EventCoordinator::Subscribe(this, &ImGuiDebugViewLayer::OnWindowResized);
        SDL_AddEventWatch(OnSDLEvent, nullptr);
    }

    void ImGuiDebugViewLayer::OnDetach()
    {
        Tbx::EventCoordinator::Unsubscribe(this, &ImGuiDebugViewLayer::OnFrameRendered);
        Tbx::EventCoordinator::Unsubscribe(this, &ImGuiDebugViewLayer::OnWindowResized);
        
        ImGui_ImplSDL3_Shutdown();
        ImGui_ImplOpenGL3_Shutdown();
    }

    void ImGuiDebugViewLayer::OnUpdate()
    {
        /*auto memory = _processInfo.GetMemoryUsage();
        auto maxMemory = _systemInfo.GetTotalMemory();
        auto memUsage = _systemInfo.GetTotalUsageMemory();
        auto cpuUsage = _processInfo.GetCpuUsage();
        auto cpuSysUsage = _systemInfo.GetCpuTotalUsage();*/

        // Get io from last frame
        const ImGuiIO& io = ImGui::GetIO();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();

        // Listen for key press to toggle the debug window
        if (Tbx::Input::IsKeyUp(TBX_KEY_F1))
        {
            _isDebugWindowOpen = !_isDebugWindowOpen;
        }

        // Show debug window
        if (_isDebugWindowOpen)
        {
            ImGui::Begin("Tbx Debugger", &_isDebugWindowOpen);

            if (ImGui::CollapsingHeader("Performance"))
            {
                ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
                /*ImGui::Text("CPU Usage: %.1f%%", cpuUsage);
                ImGui::Text("System CPU Usage: %.1f%%", cpuSysUsage);
                ImGui::Text("Memory Usage (Available): %.1f%%", static_cast<float>(memory) / maxMemory * 100.0f);
                ImGui::Text("Memory Usage (In MB): %.1f MB", static_cast<float>(memory) / 1024.0f / 1024.0f);
                ImGui::Text("System Memory Usage: %.1f MB", static_cast<float>(memUsage) / 1024.0f / 1024.0f);*/
            }

            if (ImGui::CollapsingHeader("Rendering"))
            {
                auto api = Tbx::App::GetInstance()->GetGraphicsSettings().Api;
                switch (api)
                {
                    using enum Tbx::GraphicsApi;
                    case None:
                        ImGui::Text("API: None");
                        break;
                    case OpenGL:
                        ImGui::Text("API: OpenGL");
                        break;
                    default:
                        ImGui::Text("API: Uknown");
                        break;
                }

                if (ImGui::TreeNodeEx("Display"))
                {
                    ImGui::Text("Resolution: (%d, %d)", _windowResolution.Width, _windowResolution.Height);
                    ImGui::Text("Aspect Ratio: (%.1f)", _windowResolution.GetAspectRatio());
                    ImGui::TreePop();
                }
            }

            if (ImGui::CollapsingHeader("Input"))
            {
                ImGui::Text("Mouse Position: (%.1f, %.1f)", io.MousePos.x, io.MousePos.y);
                ImGui::Text("Mouse Delta: (%.1f, %.1f)", io.MouseDelta.x, io.MouseDelta.y);
                ImGui::Text("Mouse Down: %d", io.MouseDown[0]);
                ImGui::Text("Mouse Wheel: %.1f", io.MouseWheel);
            }

            /*if (ImGui::CollapsingHeader("World"))
            {
                ImGui::Text(" Boxes (%d):", Tbx::World::GetBoxCount());

                for (const auto& box : Tbx::World::GetBoxes())
                {
                    auto boxName = "Box" + std::to_string(box->GetId());

                    if (ImGui::TreeNode(boxName.c_str()))
                    {
                        ImGui::Text(" Toys (%d):", box->GetToyCount());

                        for (const auto& toy : Tbx::BoxView(box))
                        {
                            if (ImGui::TreeNode(toy.GetName().c_str()))
                            {
                                ImGui::Text("# Blocks On Toy: ??? (TODO)");
                                ImGui::TreePop();
                            }
                        }

                        ImGui::TreePop();
                    }
                }
            }*/

            ImGui::End();
        }

        // Finally, render
        ImGui::Render();
    }

    bool ImGuiDebugViewLayer::IsOverlay()
    {
        return true;
    }

    void ImGuiDebugViewLayer::OnFrameRendered(const Tbx::RenderedFrameEvent&)
    {
        if (ImGui::GetDrawData() == nullptr) return;
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void ImGuiDebugViewLayer::OnWindowResized(const Tbx::WindowResizedEvent& e)
    {
        _windowResolution = e.GetNewSize();
    }
}
