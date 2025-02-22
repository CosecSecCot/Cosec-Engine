#pragma once

#include "CosecEngine/Layer.h"

namespace Cosec {

class COSEC_API ImGuiLayer : public Layer {
public:
    ImGuiLayer();
    ~ImGuiLayer() override;

    void OnAttach() override;
    void OnDetach() override;
    void OnUpdate() override;

private:
    float m_Time = 0.0f;
};

} // namespace Cosec
