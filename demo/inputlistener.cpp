#include <iostream>
#include "../include/inputlistener.h"

int main()
{
  tomato::input_listener listener;

  while (true)
  {
    auto mouse_data = listener.get_mouse_input();

    if (!mouse_data.events.empty())
    {
      std::cout << "mouse pos: (" << mouse_data.x_pos << ", " << mouse_data.y_pos << ") - events: ";

      for (auto event : mouse_data.events)
      {
        switch (event)
        {
        case 1:
          std::cout << "LMB Click ";
          break;
        case 2:
          std::cout << "RMB Click ";
          break;
        case 3:
          std::cout << "Wheel Click ";
          break;
        case 4:
          std::cout << "LMB Long Press ";
          break;
        case 5:
          std::cout << "RMB Long Press ";
          break;
        case 6:
          std::cout << "Wheel Long Press ";
          break;
        case 7:
          std::cout << "LMB loose ";
          break;
        case 8:
          std::cout << "RMB loose ";
          break;
        case 9:
          std::cout << "Wheel loose ";
          break;
        }
      }
      std::cout << std::endl;
    }

    Sleep(10);
  }

  return 0;
}