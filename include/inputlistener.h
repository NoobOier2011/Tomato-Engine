#ifndef TOMATO_INPUTLISTENER_H
#define TOMATO_INPUTLISTENER_H

#include <conio.h>
#include <windows.h>
#include <vector>
#include <map>
#include <chrono>

#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1 : 0)

namespace tomato
{
  class input_listener
  {
  private:
    struct MouseState
    {
      bool lmb_pressed = false;
      bool rmb_pressed = false;
      bool wheel_pressed = false;
      std::chrono::steady_clock::time_point lmb_press_time;
      std::chrono::steady_clock::time_point rmb_press_time;
      std::chrono::steady_clock::time_point wheel_press_time;
      bool lmb_long_press_triggered = false;
      bool rmb_long_press_triggered = false;
      bool wheel_long_press_triggered = false;
    };

    MouseState mouse_state;
    const long LONG_PRESS_DURATION_MS = 500; // default 500 ms

  public:
    input_listener() = default;

    char get_keyboard_input()
    {
      if (_kbhit())
      {
        return _getch();
      }
      return 0;
    }

    struct mouse_type
    {
      POINT position;
      int x_pos, y_pos;
      std::vector<short> events;
      /*
      vector (events):  1 is LMB, 2 is RMB, 3 is Wheel. (click)
                        4 is LMB, 5 is RMB, 6 is Wheel. (Long press)
                        7 is LMB, 8 is RMB, 9 is Wheel. (loose)
      use bool to show the type
      */
    };

    mouse_type get_mouse_input()
    {
      mouse_type return_mouse;
      GetCursorPos(&return_mouse.position);
      return_mouse.x_pos = return_mouse.position.x;
      return_mouse.y_pos = return_mouse.position.y;

      auto current_time = std::chrono::steady_clock::now();

      if (KEY_DOWN(VK_LBUTTON))
      {
        if (!mouse_state.lmb_pressed)
        {
          mouse_state.lmb_pressed = true;
          mouse_state.lmb_press_time = current_time;
          mouse_state.lmb_long_press_triggered = false;
          return_mouse.events.push_back(1);
        }
        else
        {
          auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
              current_time - mouse_state.lmb_press_time);
          if (duration.count() >= LONG_PRESS_DURATION_MS && !mouse_state.lmb_long_press_triggered)
          {
            return_mouse.events.push_back(4);
            mouse_state.lmb_long_press_triggered = true;
          }
        }
      }
      else if (mouse_state.lmb_pressed)
      {
        mouse_state.lmb_pressed = false;
        return_mouse.events.push_back(7);

        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
            current_time - mouse_state.lmb_press_time);
        if (duration.count() < LONG_PRESS_DURATION_MS)
        {
          return_mouse.events.push_back(1);
        }
      }

      if (KEY_DOWN(VK_RBUTTON))
      {
        if (!mouse_state.rmb_pressed)
        {
          mouse_state.rmb_pressed = true;
          mouse_state.rmb_press_time = current_time;
          mouse_state.rmb_long_press_triggered = false;
          return_mouse.events.push_back(2);
        }
        else
        {
          auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
              current_time - mouse_state.rmb_press_time);
          if (duration.count() >= LONG_PRESS_DURATION_MS && !mouse_state.rmb_long_press_triggered)
          {
            return_mouse.events.push_back(5);
            mouse_state.rmb_long_press_triggered = true;
          }
        }
      }
      else if (mouse_state.rmb_pressed)
      {
        mouse_state.rmb_pressed = false;
        return_mouse.events.push_back(8);

        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
            current_time - mouse_state.rmb_press_time);
        if (duration.count() < LONG_PRESS_DURATION_MS)
        {
          return_mouse.events.push_back(2);
        }
      }

      if (KEY_DOWN(VK_MBUTTON))
      {
        if (!mouse_state.wheel_pressed)
        {
          mouse_state.wheel_pressed = true;
          mouse_state.wheel_press_time = current_time;
          mouse_state.wheel_long_press_triggered = false;
          return_mouse.events.push_back(3);
        }
        else
        {
          auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
              current_time - mouse_state.wheel_press_time);
          if (duration.count() >= LONG_PRESS_DURATION_MS && !mouse_state.wheel_long_press_triggered)
          {
            return_mouse.events.push_back(6);
            mouse_state.wheel_long_press_triggered = true;
          }
        }
      }
      else if (mouse_state.wheel_pressed)
      {
        mouse_state.wheel_pressed = false;
        return_mouse.events.push_back(9);

        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
            current_time - mouse_state.wheel_press_time);
        if (duration.count() < LONG_PRESS_DURATION_MS)
        {
          return_mouse.events.push_back(3);
        }
      }

      return return_mouse;
    }

    // Tool : get long press time
    long get_long_press_threshold() const
    {
      return LONG_PRESS_DURATION_MS;
    }

    // Tool : set long press time
    void set_long_press_threshold(long threshold_ms)
    {
      const_cast<long &>(LONG_PRESS_DURATION_MS) = threshold_ms;
    }
  };
}

#endif // TOMATO_LIBRARY_H
