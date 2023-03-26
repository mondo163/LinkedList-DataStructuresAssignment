// class definitions for the multi chain linked list

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include<iostream>
#include<iomanip>
#include "weatherdata.h"
 
class LinkList
{
    private:
        struct Node 
        {
            WeatherData data;
            Node    *nextTime;
            Node    *nextTemp;
            Node    *nextWind;
            Node    *prevTime;
            Node    *prevTemp;
            Node    *prevWind;

            Node();
            Node(const WeatherData& adata); 
        };
        Node    *headTime;
        Node    *headTemp;
        Node    *headWind; 
        int     size;
    public:
    //constructor and destructor
    LinkList();
    LinkList(const LinkList &aData);
    ~LinkList();

    //Link List class functions
    void insert(WeatherData& adata);
    bool retrieve(const int& tempStamp);
    bool remove(const int& timeStamp);
    int entriesLessThanFifty();
    int entriesMoreThanZero();
    int mostCommonTemp();
    int entriesZeroWindspeed();
    int entriesMoreThanTwentyFive();
    int mostCommonWind();
    int averageRangeTemp(int first, int second);
    int averageRangeWind(int first, int second);
    
    //Class Accessor Functions
    const int getSize();
    int getTimeHead();
    int getTimeTail();
    int getHeadTemp();
    int getHeadWind();

};
    
#endif 
