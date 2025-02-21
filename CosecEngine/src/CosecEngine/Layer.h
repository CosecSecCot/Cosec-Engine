#pragma once

#include "Core.h"
#include "Events/Event.h"

namespace Cosec {

class COSEC_API Layer {
public:
    Layer(std::string debugName = "Layer");
    virtual ~Layer();

    virtual void OnAttach() {}
    virtual void OnDetach() {}
    virtual void OnUpdate() {}
    virtual void OnEvent(const Event &event) {}

    [[nodiscard]] const std::string &GetName() const { return m_DebugName; }

protected:
    std::string m_DebugName;
};

} // namespace Cosec
