#pragma once
#include <string>

struct GLFWwindow;

namespace HoopoeEngine
{
    class Window
    {
    private:
        unsigned int m_width ;
        unsigned int m_height;
        std::string m_title;
        GLFWwindow *m_pWindow;
        
        int init();
        void shutdown();
    public:
        Window(std::string title, const unsigned int width, const unsigned int height);
        ~Window();

        Window(const Window&) = delete;
        Window(Window&&) = delete;
        Window& operator=(const Window&) = delete;
        Window& operator=(Window&&) = delete;
         
        void on_update();

        unsigned int get_width() const {return m_width;}
        unsigned int get_height() const {return m_height;}
    };
}