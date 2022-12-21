#include <iostream>

#include "Core.h"

int main()
{
    srand(time(0));
    try {
        Core::getInstance().run();
    }
    catch (std::exception& e)
    {
        std::cerr << "[ERROR]: " << e.what() << "\n";
    }
    Core::getInstance().dispose();

    return 0;
}