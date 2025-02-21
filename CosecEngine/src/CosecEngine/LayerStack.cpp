#include "LayerStack.h"

namespace Cosec {

LayerStack::LayerStack() { m_LayerInsert = m_Layers.begin(); }

LayerStack::~LayerStack() {
    for (auto layer : m_Layers) {
        delete layer;
    }
}

void LayerStack::PushLayer(Layer *layer) { m_LayerInsert = m_Layers.emplace(m_LayerInsert, layer); }

/*
 * Overlays are always rendered at last. Therefore, they are inserted at the back of the layer stack.
 * */
void LayerStack::PushOverlay(Layer *overlay) { m_Layers.emplace_back(overlay); }

/*
 * For now, when you pop a layer from the layer stack, it doesn't get deallocated.
 * It only gets deallocated when the destructor is called, i.e., it will exist until the application shuts down.
 * */
void LayerStack::PopLayer(Layer *layer) {
    auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
    if (it != m_Layers.end()) {
        m_Layers.erase(it);
        m_LayerInsert--;
    }
}

void LayerStack::PopOverlay(Layer *overlay) {
    auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
    if (it != m_Layers.end()) {
        m_Layers.erase(it);
    }
}

} // namespace Cosec
