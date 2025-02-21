#include "Layer.h"

namespace Cosec {

Layer::Layer(std::string debugName) : m_DebugName(std::move(debugName)) {}

Layer::~Layer() = default;

} // namespace Cosec
