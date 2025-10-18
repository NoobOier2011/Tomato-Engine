#include <iostream>
#include "../include/window.h"

void game();

int main()
{
    tomato::window Window;
    Window.run(800, 600, "Potato Engine", game);
}

void game()
{
    std::cerr << "Potato Engine is running!" << std::endl;
}