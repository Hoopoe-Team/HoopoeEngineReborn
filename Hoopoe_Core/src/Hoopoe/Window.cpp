#include "Hoopoe/Window.hpp"
#include "Hoopoe/Log.hpp"

#include <glad/glad.h>
#include <glfw/glfw3.h>

namespace HoopoeEngine
{
    static bool s_GLFW_initilized = false;

    Window::Window(std::string title, const unsigned int width, const unsigned int height)
        : m_title(std::move(title)),
          m_width(width),
          m_height(height)
    {
        int resultCode = init();
    }

    Window::~Window()
    {
        shutdown();
    }

    int Window::init()
    {
        LOG_INFO("Create window '{0}' width size {1}x{2}", m_title, m_width, m_height);

        if (!s_GLFW_initilized)
        {
            if (!glfwInit())
            {
                LOG_CRITICAL("Can't initilize GLFW!");
                return -1;
            }
            s_GLFW_initilized = true;
        }

        m_pWindow = glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr);
        if (!m_pWindow)
        {
            LOG_CRITICAL("Can't create GLFW! '{0}' width size {1}x{2}", m_title, m_width, m_height);
            glfwTerminate();
            return -2;
        }

        /* Make the window's context current */
        glfwMakeContextCurrent(m_pWindow);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            LOG_CRITICAL("Failed to initalize GLAD");
            return -3;
        }

        return 0;
    }

    void Window::shutdown()
    {
        glfwDestroyWindow(m_pWindow);
        glfwTerminate();
    }
    void Window::on_update()
    {
        glClearColor(1, 0.5, 0.5, 0);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(m_pWindow);
        glfwPollEvents();
        }
}
