#ifndef TOMATO_LIBRARY_H
#define TOMATO_LIBRARY_H

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

namespace tomato
{
  class window
  {
  public:
    void run(uint32_t width, uint32_t height, const char *title)
    {
      init_window(width, height, title);
      // init_vulkan();
      main_loop();
      close_window();
    }

  private:
    GLFWwindow *Window;

    void init_window(int width, int height, const char *title)
    {
      glfwInit();

      glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
      glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

      Window = glfwCreateWindow(width, height, title, nullptr,
                                nullptr);
    }
    void main_loop()
    {
      while (!glfwWindowShouldClose(Window))
      {
        glfwPollEvents();
      }
    }
    void close_window()
    {
      glfwDestroyWindow(Window);

      glfwTerminate();
    }
  };

}

#endif // TOMATO_LIBRARY_H