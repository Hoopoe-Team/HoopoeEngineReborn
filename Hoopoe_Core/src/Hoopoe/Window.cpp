#include "Hoopoe/Window.hpp"
#include "Hoopoe/Log.hpp"
#include "Hoopoe/OpenGLShader.hpp"
#include "Hoopoe/FileManager.hpp"

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_opengl3.h>

#define PI 3.14159265358979323846

namespace HoopoeEngine
{
    Shader triangle_shader;
    GLuint vbo, vao, ebo;

    void create_triangle(GLuint &vbo, GLuint &vao, GLuint &ebo)
    {

        // create the triangle
        float triangle_vertices[] = {
            0.0f, 0.25f, 0.0f,    // position vertex 1
            1.0f, 0.0f, 0.0f,     // color vertex 1
            0.25f, -0.25f, 0.0f,  // position vertex 1
            0.0f, 1.0f, 0.0f,     // color vertex 1
            -0.25f, -0.25f, 0.0f, // position vertex 1
            0.0f, 0.0f, 1.0f,     // color vertex 1
        };
        unsigned int triangle_indices[] = {
            0, 1, 2};
        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);
        glGenBuffers(1, &ebo);
        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_vertices), triangle_vertices, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(triangle_indices), triangle_indices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    static bool s_GLFW_initilized = false;

    Window::Window(std::string title, const unsigned int width, const unsigned int height)
        : m_data({std::move(title), width, height})
    {
        int resultCode = init();

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGui_ImplOpenGL3_Init();
        ImGui_ImplGlfw_InitForOpenGL(m_pWindow, true);
    }

    Window::~Window()
    {
        shutdown();
    }

    int Window::init()
    {
        LOG_INFO("Create window '{0}' width size {1}x{2}", m_data.title, m_data.width, m_data.height);

        if (!s_GLFW_initilized)
        {
            if (!glfwInit())
            {
                LOG_CRITICAL("Can't initilize GLFW!");
                return -1;
            }
            s_GLFW_initilized = true;
        }
        glfwSwapInterval(1);

        m_pWindow = glfwCreateWindow(m_data.width, m_data.height, m_data.title.c_str(), nullptr, nullptr);
        if (!m_pWindow)
        {
            LOG_CRITICAL("Can't create GLFW! '{0}' width size {1}x{2}", m_data.title, m_data.width, m_data.height);
            glfwTerminate();
            return -2;
        }

        glfwMakeContextCurrent(m_pWindow);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            LOG_CRITICAL("Failed to initalize GLAD");
            return -3;
        }

        glfwSetWindowUserPointer(m_pWindow, &m_data);

        glfwSetWindowSizeCallback(m_pWindow, // window size
                                  [](GLFWwindow *pWindow, int width, int height)
                                  {
                                      WindowData &data = *static_cast<WindowData *>(glfwGetWindowUserPointer(pWindow));
                                      data.width = width;
                                      data.height = height;

                                      EventWindowResize event(width, height);
                                      data.eventCallbackFn(event);
                                  });
        glfwSetCursorPosCallback(m_pWindow, // mouse pos
                                 [](GLFWwindow *pWindow, double x, double y)
                                 {
                                     WindowData &data = *static_cast<WindowData *>(glfwGetWindowUserPointer(pWindow));

                                     EventMouseMoved event(x, y);
                                     data.eventCallbackFn(event);
                                 });

        glfwSetWindowCloseCallback(m_pWindow, // Close button
                                   [](GLFWwindow *pWindow)
                                   {
                                       WindowData &data = *static_cast<WindowData *>(glfwGetWindowUserPointer(pWindow));

                                       EventWindowClose event;
                                       data.eventCallbackFn(event);
                                   });

        glfwSetFramebufferSizeCallback(m_pWindow, // size of triangle reletive to the window
                                       [](GLFWwindow *pWindow, int width, int height)
                                       {
                                           glViewport(0, 0, width, height);
                                       });

        create_triangle(vbo, vao, ebo);

        triangle_shader.init(FileManager::read("HoopoeShader.vs"), FileManager::read("HoopoeShader.fs"));

        return 0;
    }
              
    void Window::shutdown()
    {
	    ImGui::DestroyContext();

        glfwDestroyWindow(m_pWindow);
        glfwTerminate();
    }
    void Window::on_update()
    {
        glClearColor(m_background_color[0], m_background_color[1], m_background_color[2], m_background_color[3]);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGuiIO &io = ImGui::GetIO();
        io.DisplaySize.x = static_cast<float>(get_width());
        io.DisplaySize.y = static_cast<float>(get_height());

        ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
              
        triangle_shader.use();
        
        glBindVertexArray(vao);

        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        

        // Background color
        ImGui::Begin("Background Color Window");
        ImGui::ColorEdit4("Background Color", m_background_color);
        ImGui::End();


        ImGui::Begin("Triangle Position/Color");
		static float rotation = 0.0;
		ImGui::SliderFloat("rotation", &rotation, 0, 2 * PI);
		static float translation[] = {0.0, 0.0};
		ImGui::SliderFloat2("position", translation, -1.0, 1.0);
        static float color[4] = { 1.0f,1.0f,1.0f,1.0f };

        triangle_shader.setUniform("rotation", rotation);
        triangle_shader.setUniform("translation", translation[0], translation[1]);

        ImGui::ColorEdit3("color", color);

        triangle_shader.setUniform("color", color[0], color[1], color[2]);

        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(m_pWindow);
        glfwPollEvents();
    }
}
