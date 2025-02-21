#include "Layer.h"

namespace Cosec {

Layer::Layer(std::string name) : m_DebugName(std::move(name)) {}

Layer::~Layer() = default;

} // namespace Cosec
