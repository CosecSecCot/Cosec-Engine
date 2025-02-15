#include <CosecEngine.h>

class Sandbox : public Cosec::Application {
public:
    Sandbox() = default;
    ~Sandbox() override = default;
};

Cosec::Application *Cosec::CreateApplication() { return new Sandbox(); }
