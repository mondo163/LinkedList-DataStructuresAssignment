// Contains the weather data object methods, constructors, and destructors. 

#ifndef WEATHERDATA_H
#define WEATHERDATA_H

#include<iostream>
using namespace std;

class WeatherData
{	
    private:
	    int    timestamp;
        int    temperature;
        int    windspeed;
    public:
        //constructors and destructor
        WeatherData();
        WeatherData(int tempTimeStamp, int tempTemperature, int tempWindSpeed);
        WeatherData(const WeatherData& tempData);
        ~WeatherData();
        //accessor functions
        int getTimeStamp();
        int getTemperature();
        int getWindSpeed();
        //Mutator FUnctions
        void setTimeStamp(int tempTimeStamp);
        void setTemperature(int tempTemperature);
        void setWindSpeed(int tempWindSpeed);
        //operator overloading
        const WeatherData& operator= (const WeatherData& tempData);

};
    //comparison operator overload
    bool operator== (WeatherData& aItem, WeatherData& bItem);
#endif
