#include "Application.h"

#include <glad/glad.h>

#include <ranges>

namespace Cosec {

Application *Application::s_Instance = nullptr;

Application::Application() {
    COSEC_CORE_ASSERT(!s_Instance, "Application already exists!");
    s_Instance = this;

    m_Window = std::unique_ptr<EngineWindow>(EngineWindow::Create());
    m_Window->SetEventCallback([this](auto &&e) { Application::OnEvent(std::forward<decltype(e)>(e)); });

    m_LayerStack = std::make_unique<LayerStack>();

    m_ImGuiLayer = new ImGuiLayer();
    PushOverlay(m_ImGuiLayer);

    m_VertexArray.reset(VertexArray::Create());

    // clang-format off
    float vertices[] = {
        // a_position        // a_color
        -0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f, 1.0f,
         0.0f,  0.5f, 0.0f,  0.0f, 1.0f, 0.0f, 1.0f,
         0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f, 1.0f
    };
    // clang-format on

    std::shared_ptr<VertexBuffer> m_VertexBuffer;
    m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

    BufferLayout layout = {
        {ShaderDataType::Float3, "a_position"},
        {ShaderDataType::Float4, "a_color"},
    };
    m_VertexBuffer->SetLayout(layout);

    m_VertexArray->AddVertexBuffer(m_VertexBuffer);

    // clang-format off
    uint32_t indices[] = {
        0, 1, 2
    };
    // clang-format on

    std::shared_ptr<IndexBuffer> m_IndexBuffer;
    m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

    m_VertexArray->SetIndexBuffer(m_IndexBuffer);

    std::string vertexSrc = R"(
#version 410 core
layout (location=0)in vec3 a_position;
layout (location=1)in vec4 a_color;
out vec3 v_pos;
out vec4 v_color;
void main()
{
    v_pos = a_position * 0.5 + 0.5;
    v_color = a_color;
    gl_Position = vec4(a_position, 1.0);
})";

    std::string fragmentSrc = R"(
#version 410 core
layout (location=0)out vec4 color;
in vec3 v_pos;
in vec4 v_color;
void main()
{
    color = vec4(v_pos * 0.5 + 0.5, 1.0);
    color = v_color;
})";

    m_Shader.reset(Shader::Create(vertexSrc, fragmentSrc));
}

Application::~Application() = default;

void Application::OnEvent(Event &e) {
    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<WindowCloseEvent>(DISPATCH_EVENT_FN(Application::OnWindowClose));

    for (auto &it : std::ranges::reverse_view(*m_LayerStack)) {
        it->OnEvent(e);
        if (e.Handled) {
            break;
        }
    }
}

void Application::PushLayer(Layer *layer) { m_LayerStack->PushLayer(layer); }

void Application::PushOverlay(Layer *overlay) { m_LayerStack->PushOverlay(overlay); }

void Application::Run() {
    while (m_Running) {
        glClearColor(0.07, 0.07, 0.08, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        m_Shader->Bind();
        m_VertexArray->Bind();
        glDrawElements(GL_TRIANGLES, m_VertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

        for (const auto layer : *m_LayerStack) {
            layer->OnUpdate();
        }

        m_ImGuiLayer->Begin();
        for (const auto layer : *m_LayerStack) {
            layer->OnImGuiRender();
        }
        m_ImGuiLayer->End();

        m_Window->OnUpdate();
    }
}

bool Application::OnWindowClose(WindowCloseEvent &) {
    LOG_CORE_TRACE("Window Closed!");
    m_Running = false;
    return true;
}

} // namespace Cosec
