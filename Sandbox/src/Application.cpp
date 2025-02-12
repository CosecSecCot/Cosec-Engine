#include <TopDownEngine.h>

class Sandbox : public TopDown::Application {
public:
    Sandbox() = default;
    ~Sandbox() override = default;
};

TopDown::Application *TopDown::CreateApplication() { return new Sandbox(); }
