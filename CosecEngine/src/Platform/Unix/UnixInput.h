#pragma once

#include "CosecEngine/Core.h"
#include "CosecEngine/EngineInput.h"

namespace Cosec {

class COSEC_API UnixInput : public EngineInput {
protected:
    bool IsKeyPressedImpl(int keycode) override;
    bool IsMouseButtonPressedImpl(int button) override;
    float GetMouseXImpl() override;
    float GetMouseYImpl() override;
    std::pair<float, float> GetMousePosImpl() override;
};

} // namespace Cosec
