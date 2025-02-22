#include "imgui.h"
#include <CosecEngine.h>

class ExampleLayer : public Cosec::Layer {
public:
    ExampleLayer() : Cosec::Layer("Example") {};

    void OnUpdate() override {
        if (Cosec::EngineInput::IsKeyPressed(COSEC_KEY_J)) {
            LOG_TRACE("J key pressed!");
        }
        if (Cosec::EngineInput::IsMouseButtonPressed(COSEC_MOUSE_BUTTON_LEFT)) {
            LOG_TRACE("LEFT MOUSE pressed!");
        }
        if (Cosec::EngineInput::IsMouseButtonPressed(COSEC_MOUSE_BUTTON_RIGHT)) {
            LOG_TRACE("RIGHT MOUSE pressed!");
        }
    }

    void OnImGuiRender() override {
        ImGui::Begin("Test");
        ImGui::Text("Hello World!");
        ImGui::End();
    }

    void OnEvent(Cosec::Event &event) override {}
};

class Sandbox : public Cosec::Application {
public:
    Sandbox() { PushLayer(new ExampleLayer()); }
    ~Sandbox() override = default;
};

Cosec::Application *Cosec::CreateApplication() { return new Sandbox(); }
