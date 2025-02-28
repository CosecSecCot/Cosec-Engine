#include <CosecEngine.h>
#include <imgui.h>

class ExampleLayer : public Cosec::Layer {
public:
    ExampleLayer() : Cosec::Layer("Example"){};

    void OnUpdate() override {
        // if (Cosec::EngineInput::IsKeyPressed(COSEC_KEY_J)) {
        //     LOG_TRACE("J key pressed!");
        // }
        // if (Cosec::EngineInput::IsMouseButtonPressed(COSEC_MOUSE_BUTTON_LEFT)) {
        //     LOG_TRACE("LEFT MOUSE pressed!");
        // }
    }

    void OnImGuiRender() override {
        ImGui::Begin("Bonga");
        ImGui::Checkbox("Are you Bonga ?", &m_IsBonga);
        if (m_IsBonga) {
            ImGui::Text("Hello Bonga!!");
        }
        ImGui::End();
    }

    void OnEvent(Cosec::Event &event) override {}

private:
    bool m_IsBonga = false;
};

class Sandbox : public Cosec::Application {
public:
    Sandbox() { PushLayer(new ExampleLayer()); }
    ~Sandbox() override = default;
};

Cosec::Application *Cosec::CreateApplication() { return new Sandbox(); }
