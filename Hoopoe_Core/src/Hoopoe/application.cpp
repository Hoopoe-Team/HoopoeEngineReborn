#pragma once
#include <iostream>

#include "Hoopoe/Application.hpp"

#include <spdlog/spdlog.h>
#include <GLFW/glfw3.h>

namespace HoopoeEngine
{
    Application::Application()
    {
        spdlog::info("Welcome to spdlog!");
        spdlog::error("Some error message with arg: {}", 1);

        spdlog::warn("Easy padding in numbers like {:08d}", 12);
        spdlog::critical("Support for int: {0:d};  hex: {0:x};  oct: {0:o}; bin: {0:b}", 42);
        spdlog::info("Support for floats {:03.2f}", 1.23456);
        spdlog::info("Positional args are {1} {0}..", "too", "supported");
        spdlog::info("{:<30}", "left aligned");

        spdlog::set_level(spdlog::level::debug); // Set global log level to debug
        spdlog::debug("This message should be displayed..");

        // change log pattern
        spdlog::set_pattern("[%H:%M:%S %z] [%n] [%^---%L---%$] [thread %t] %v");

        // Compile time log levels
        // define SPDLOG_ACTIVE_LEVEL to desired level
        SPDLOG_TRACE("Some trace message with param {}", 42);
        SPDLOG_DEBUG("Some debug message");
    }

    Application::~Application()
    {
    }

    int Application::start(unsigned int window_width, unsigned int window_height, const char *title)
    {
        GLFWwindow *window;

        /* Initialize the library */
        if (!glfwInit())
            return -1;

        /* Create a windowed mode window and its OpenGL context */
        window = glfwCreateWindow(window_width, window_height, title, NULL, NULL);
        if (!window)
        {
            glfwTerminate();
            return -1;
        }

        /* Make the window's context current */
        glfwMakeContextCurrent(window);

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            //glClear(GL_COLOR_BUFFER_BIT);

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();

            on_update();
        }

        glfwTerminate();
        return 0;
    }
}