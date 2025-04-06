#include "Window.h"
#include "ConfigReader.cpp"
#include <fstream>
#include <string>


using namespace std;

int main()
{
    setlocale(LC_ALL, "");

    ConfigReader configReader("../config.txt");
    const int wWidth = configReader.GetWindowWidth();
    const int wHeight = configReader.GetWindowHeight();

    Window window(wWidth, wHeight, configReader);
    window.Run();

    return 0;
}