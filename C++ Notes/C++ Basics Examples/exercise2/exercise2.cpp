// exercise2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <time.h>
using namespace std;

int main()
{
    __time32_t rawtime;
    struct tm timeinfo;
    char buffer[32];
    _time32(&rawtime);
    _localtime32_s(&timeinfo, &rawtime);
    asctime_s(buffer, 32, &timeinfo);

    cout << "The current time is " << buffer << endl;
    cout << "current time is " << timeinfo.tm_hour << ":" << timeinfo.tm_min << ":" << timeinfo.tm_sec << endl;
    cout << "The seconds passed since Jan. 1st 1970 is " << rawtime << endl;
    
}

