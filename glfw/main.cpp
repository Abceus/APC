#include <iostream>
#include <fstream>
#include <sstream>

#include "test_game.h"
#include "apc/context.h"
#include "apc/opengl/gl_renderer.h"
#include "apc/log.h"
#include "apc/file_loader.h"

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <functional>

// const GLuint WIDTH = 1920, HEIGHT = 1080;
// const GLuint WIDTH = 1080, HEIGHT = 1920;
// const GLuint WIDTH = 800, HEIGHT = 600;
// const GLuint WIDTH = 850, HEIGHT = 692;

class PCLog : public apc::ILog
{
public:
    void print( const std::stringstream &stream ) override
    {
        std::cout << stream.str() << std::endl;
    }
};

class PCFileLoader : public apc::IFileLoader
{
public:
    std::vector<unsigned char> load( const std::string &path ) const override
    {
        std::ifstream file( "./resources/" + path, std::ios::binary | std::ios::ate);
        if( file )
        {
            std::streamsize size = file.tellg();
            file.seekg( 0, std::ios::beg );

            std::vector<unsigned char> buffer( size );
            file.read( reinterpret_cast<char *>(buffer.data()), size );
            return buffer;
        }
        return std::vector<unsigned char>();
    }
};

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
        // glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

        auto config = TestGame::getGameConfig();

        // window = glfwCreateWindow(config.width, config.height, config.gameName, nullptr, nullptr);
        window = glfwCreateWindow(524, 568, config.gameName.c_str(), nullptr, nullptr);
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
        glfwSetWindowSizeCallback(window, &PC::window_size_callback);


//    glfwSetKeyCallback(window, key_callback);

        glewExperimental = GL_TRUE;
        if (glewInit() != GLEW_OK)
        {
            std::cout << "Failed to initialize GLEW" << std::endl;
            return;
        }

        glfwGetFramebufferSize(window, &width, &height);

        apc::Context::getInstance().setLogImpl<PCLog>();
        apc::Context::getInstance().setLoaderImpl<PCFileLoader>();
        apc::Context::getInstance().init<apc::GLRenderer, TestGame>();
        apc::Context::getInstance().screenSizeChanged({width, height});
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
            apc::Context::getInstance().update(deltaTime);
            apc::Context::getInstance().draw();
            glfwSwapBuffers(window);
        }
    }

    void deinit()
    {
        apc::Context::getInstance().quit();
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
                    if( !m_dragged )
                    {
                        apc::Context::getInstance().button( { static_cast<int>(xpos), static_cast<int>(ypos) } );
                    }
                    else
                    {
                        m_dragged = false;
                        apc::Context::getInstance().drop( { static_cast<int>(xpos), static_cast<int>(ypos) } );
                    }
                    break;
                case GLFW_MOUSE_BUTTON_RIGHT:
                    apc::Context::getInstance().altButton( { static_cast<int>(xpos), static_cast<int>(ypos) } );
                    break;
            }
        }
    }

    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
    {
        apc::Context::getInstance().zoom( yoffset );
    }

    static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
    {
        int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
        if(state == GLFW_PRESS && m_mouseFocused)
        {
            if( !m_dragged )
            {
                m_dragged = true;
                apc::Context::getInstance().drag({ static_cast<int>(xpos), static_cast<int>(ypos) });
            }
            else
            {
                apc::Context::getInstance().holdedMove( { static_cast<int>(xpos), static_cast<int>(ypos) } );
            }
        }
    }

    static void cursor_enter_callback(GLFWwindow* window, int entered)
    {
        PC::m_mouseFocused = static_cast<bool>(entered);
    }

    static void window_size_callback(GLFWwindow* window, int width, int height)
    {
        apc::Context::getInstance().screenSizeChanged({width, height});
    }
private:
    GLFWwindow* window;
    int width, height;
    static bool m_mouseFocused;
    static bool m_dragged;
};

bool PC::m_mouseFocused = true;
bool PC::m_dragged = true;

int main()
{
    PC pc;
    pc.init();
    pc.run();
    pc.deinit();
    return 0;
}