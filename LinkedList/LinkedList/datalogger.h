// class that contains the list, adds the data, and prints the proper report 

#ifndef DATALOGGER_H
#define DATALOGGER_H

#include<iostream>
#include<iomanip>
#include "linkedlist.h"
using namespace std;

//global constants
const int RANGE = 10;

class datalogger
{
    private:
        LinkList list;       
    public:
        //constructor and destructor
        datalogger();
        ~datalogger(); 
        //class functions
        bool containsTimestamp(int& timestamp);
        bool removeData(int& timestamp);
        bool addData(int timestamp, int temperature, int windspeed);
        void printReport(const char* label);

};





#endif
