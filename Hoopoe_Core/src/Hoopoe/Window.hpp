#pragma once

#include "Hoopoe/Event.hpp"

#include <string>
#include <functional>

struct GLFWwindow;

namespace HoopoeEngine
{
    class Window
    {
    public:

        using EventCallbackFn = std::function<void(BaseEvent&)>;

        void set_event_callback(const EventCallbackFn& callback)
        {
            m_data.eventCallbackFn = callback;
        }
        Window(std::string title, const unsigned int width, const unsigned int height);
        ~Window();

        Window(const Window&) = delete;
        Window(Window&&) = delete;
        Window& operator=(const Window&) = delete;
        Window& operator=(Window&&) = delete;
         
        void on_update();

        unsigned int get_width() const {return m_data.width;}
        unsigned int get_height() const {return m_data.height;}

    private:

        struct WindowData
        {
            std::string title;
            unsigned int width;
            unsigned int height;
            
            EventCallbackFn eventCallbackFn;
        };

        GLFWwindow* m_pWindow = nullptr;

        int init();
        void shutdown();

        WindowData m_data;
        float m_background_color[4] = { 1.f, 0.f, 0.f, 0.f };
       
    };
}