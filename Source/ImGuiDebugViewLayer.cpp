#include "ImGuiDebugViewLayer.h"
#include <Tbx/Application/App/App.h>
#include <Tbx/Systems/Input/Input.h>
#include <Tbx/Systems/Rendering/Rendering.h>
#include <Tbx/Systems/Windowing/WindowManager.h>
#include <Tbx/Systems/Events/EventCoordinator.h>
#include <Tbx/Systems/TBS/World.h>
#include <Tbx/Graphics/Camera.h>
#include <Tbx/Math/Transform.h>
#include <imgui.h>

namespace ImGuiDebugView
{
    void ImGuiDebugViewLayer::OnAttach()
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // optional

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        //ImGui::StyleColorsLight();
        
        // Init size
        const auto mainWindow = Tbx::WindowManager::GetMainWindow();
        _windowResolution = mainWindow->GetSize();

        // Setup Platform/Renderer backends
        //auto* nativeWindow = static_cast<GLFWwindow*>(mainWindow->GetNativeWindow());

        // Sub to frame rendered event so we know when to draw
        _windowResizedEventId = Tbx::EventCoordinator::Subscribe<Tbx::WindowResizedEvent>(TBX_BIND_FN(OnWindowResized));
    }

    void ImGuiDebugViewLayer::OnDetach()
    {
        Tbx::EventCoordinator::Unsubscribe<Tbx::WindowResizedEvent>(_windowResizedEventId);

        ImGui::DestroyContext();
    }

    void ImGuiDebugViewLayer::OnUpdate()
    {
        auto memory = _processInfo.GetMemoryUsage();
        auto maxMemory = _systemInfo.GetTotalMemory();
        auto memUsage = _systemInfo.GetTotalUsageMemory();
        auto cpuUsage = _processInfo.GetCpuUsage();
        auto cpuSysUsage = _systemInfo.GetCpuTotalUsage();

        // Get io from last frame
        const ImGuiIO& io = ImGui::GetIO();

        // Start the Dear ImGui frame
        {
            ImGui::NewFrame();
        }

        // Listen for key press to toggle the debug window
        {
            if (Tbx::Input::IsKeyDown(TBX_KEY_F1))
            {
                _showDebugWindowOnDebugBtnUp = true;
            }
            if (_showDebugWindowOnDebugBtnUp &&
                Tbx::Input::IsKeyUp(TBX_KEY_F1))
            {
                _showDebugWindowOnDebugBtnUp = false;
                _isDebugWindowOpen = !_isDebugWindowOpen;
            }
        }

        // Show debug window
        if (_isDebugWindowOpen)
        {
            ImGui::Begin("Tbx Debugger", &_isDebugWindowOpen);

            if (ImGui::CollapsingHeader("Performance", ImGuiTreeNodeFlags_DefaultOpen))
            {
                ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
                ImGui::Text("CPU Usage: %.1f%%", cpuUsage);
                ImGui::Text("System CPU Usage: %.1f%%", cpuSysUsage);
                ImGui::Text("Memory Usage (Available): %.1f%%", static_cast<float>(memory) / maxMemory * 100.0f);
                ImGui::Text("Memory Usage (In MB): %.1f MB", static_cast<float>(memory) / 1024.0f / 1024.0f);
                ImGui::Text("System Memory Usage: %.1f MB", static_cast<float>(memUsage) / 1024.0f / 1024.0f);
            }

            if (ImGui::CollapsingHeader("Display", ImGuiTreeNodeFlags_DefaultOpen))
            {
                ImGui::Text("Resolution: (%d, %d)", _windowResolution.Width, _windowResolution.Height);
                ImGui::Text("Aspect Ratio: (%.1f)", _windowResolution.GetAspectRatio());
            }

            if (ImGui::CollapsingHeader("Rendering"), ImGuiTreeNodeFlags_DefaultOpen)
            {
                auto api = Tbx::App::GetInstance()->GetGraphicsSettings().Api;
                switch (api)
                {
                    case Tbx::GraphicsApi::DirectX12:
                        ImGui::Text("API: DX12");
                        break;
                    case Tbx::GraphicsApi::Vulkan:
                        ImGui::Text("API: Vulkan");
                        break;
                    case Tbx::GraphicsApi::Metal:
                        ImGui::Text("API: Metal");
                        break;
                }

                int cameraNumber = 0;
                auto playSpaces = Tbx::World::GetPlayspaces();
                for (auto playSpace : playSpaces)
                {
                    for (auto camera : Tbx::PlayspaceView<Tbx::Camera>(playSpace))
                    {
                        auto& camTrans = playSpace->GetBlockOn<Tbx::Transform>(camera);
                        ImGui::Text("Camera %d Position: %s", cameraNumber, camTrans.Position.ToString().c_str());
                        ImGui::Text("Camera %d Rotation: %s", cameraNumber, Tbx::Quaternion::ToEuler(camTrans.Rotation).ToString().c_str());
                        ImGui::Text("Camera %d Scale: %s", cameraNumber, camTrans.Scale.ToString().c_str());
                        cameraNumber++;
                    }
                }
            }

            if (ImGui::CollapsingHeader("Input", ImGuiTreeNodeFlags_DefaultOpen))
            {
                ImGui::Text("Mouse Position: (%.1f, %.1f)", io.MousePos.x, io.MousePos.y);
                ImGui::Text("Mouse Delta: (%.1f, %.1f)", io.MouseDelta.x, io.MouseDelta.y);
            }

            ImGui::End();
        }

        // Finally, render
        {
            ImGui::Render();
        }
    }

    bool ImGuiDebugViewLayer::IsOverlay()
    {
        return true;
    }

    void ImGuiDebugViewLayer::OnWindowResized(const Tbx::WindowResizedEvent& e)
    {
        _windowResolution = e.GetNewSize();
    }
}
