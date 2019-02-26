#include <iostream>
#include "test_game.h"
#include "base/context.h"
#include "base/gl_renderer.h"

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <functional>

const GLuint WIDTH = 800, HEIGHT = 600;

class PC
{
public:
    void init()
    {
        std::cout << "Starting GLFW context, OpenGL 3.3" << std::endl;
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

        window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);
        if (window == nullptr)
        {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return;
        }
        glfwMakeContextCurrent(window);
        glfwSetMouseButtonCallback(window, &PC::mouse_button_callback);
        glfwSetScrollCallback(window, &PC::scroll_callback);
        glfwSetCursorPosCallback(window, &PC::cursor_position_callback);
        glfwSetCursorEnterCallback(window, &PC::cursor_enter_callback);


//    glfwSetKeyCallback(window, key_callback);

        glewExperimental = GL_TRUE;
        if (glewInit() != GLEW_OK)
        {
            std::cout << "Failed to initialize GLEW" << std::endl;
            return;
        }

        glfwGetFramebufferSize(window, &width, &height);

        APC::Context::getInstance().init<APC::GLRenderer, TestGame>(width, height);
        APC::Context::getInstance().setLogFunction( [&](std::stringstream& ss){ std::cout << ss.str(); });
    }
    void run()
    {
        auto lastFrame = glfwGetTime();
        while (!glfwWindowShouldClose(window))
        {
            glfwPollEvents();
            auto currentFrame = glfwGetTime();
            auto deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;
            APC::Context::getInstance().update(deltaTime);
            APC::Context::getInstance().draw();
            glfwSwapBuffers(window);
        }
    }
    void deinit()
    {
        glfwTerminate();
    }

    static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
    {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        if(action == GLFW_RELEASE)
        {
            switch( button )
            {
                case GLFW_MOUSE_BUTTON_LEFT:
                    APC::Context::getInstance().button( { static_cast<int>(xpos), static_cast<int>(ypos) } );
                    break;
                case GLFW_MOUSE_BUTTON_RIGHT:
                    APC::Context::getInstance().altButton( { static_cast<int>(xpos), static_cast<int>(ypos) } );
                    break;
            }
        }
    }

    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
    {
        APC::Context::getInstance().zoom( yoffset );
    }

    static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
    {
        int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
        if(state == GLFW_PRESS && m_mouseFocused)
        {
            APC::Context::getInstance().holdedMove({ static_cast<int>(xpos), static_cast<int>(ypos) });
        }
    }

    static void cursor_enter_callback(GLFWwindow* window, int entered)
    {
        PC::m_mouseFocused = static_cast<bool>(entered);
    }
private:
    GLFWwindow* window;
    int width, height;
    static bool m_mouseFocused;
};

bool PC::m_mouseFocused = true;

int main()
{
    PC pc;
    pc.init();
    pc.run();
    pc.deinit();
    return 0;
}