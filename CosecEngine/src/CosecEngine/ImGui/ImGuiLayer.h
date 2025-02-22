#pragma once

#include "CosecEngine/Layer.h"

namespace Cosec {

class COSEC_API ImGuiLayer : public Layer {
public:
    ImGuiLayer();
    ~ImGuiLayer() override;

    void OnAttach() override;
    void OnDetach() override;
    void OnImGuiRender() override;

    void Begin();
    void End();
};

} // namespace Cosec
