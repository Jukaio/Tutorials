// main.cpp

#include <iostream>
#include "application.h"


int main(int, char**)
{
    ApplicationInitialisation();
    if(ApplicationShouldRun()) {
        while(ApplicationIsRunning()) {
            ApplicationRun();
        }
    }
    ApplicationTermination();
    
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
