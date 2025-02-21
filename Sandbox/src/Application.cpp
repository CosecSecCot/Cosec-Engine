#include <CosecEngine.h>

class ExampleLayer : public Cosec::Layer {
public:
    ExampleLayer() : Cosec::Layer("Example"){};

    void OnUpdate() override { LOG_INFO("Example Layer Update!"); }

    void OnEvent(const Cosec::Event &event) override { LOG_TRACE("{0}", event.ToString()); }
};

class Sandbox : public Cosec::Application {
public:
    Sandbox() { PushLayer(new ExampleLayer()); }
    ~Sandbox() override = default;
};

Cosec::Application *Cosec::CreateApplication() { return new Sandbox(); }
