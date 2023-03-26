// Implemented methods for the weatherdata object

#include "weatherdata.h"

WeatherData::WeatherData()
{
    timestamp =0;
    temperature = 0;
    windspeed = 0;
}

WeatherData::WeatherData(int tempTimeStamp, int tempTemperature, int tempWindSpeed)
{
    timestamp = tempTimeStamp;
    temperature = tempTemperature;
    windspeed = tempWindSpeed;
}
    
WeatherData::WeatherData(const WeatherData& tempData)
{
    timestamp = tempData.timestamp;
    temperature = tempData.temperature;
    windspeed = tempData.windspeed;
}    	

WeatherData::~WeatherData()
{
    //Nothing to destruct
}

//accessor functions
int WeatherData::getTimeStamp()
{
    return timestamp;
}

int WeatherData::getTemperature()
{
   
    return temperature;
     
}

int WeatherData::getWindSpeed()
{
    return windspeed;
}

//mutator functions
void WeatherData::setTimeStamp(int tempTimeStamp)
{
    timestamp = tempTimeStamp;
}

void WeatherData::setTemperature(int tempTemperature)
{
    temperature = tempTemperature;
}

void WeatherData::setWindSpeed(int tempWindSpeed)
{
    windspeed = tempWindSpeed;
}

//copy operator overloaded    
const WeatherData& WeatherData::operator= (const WeatherData& tempData)
{
    if (this == &tempData)
        return *this;  
    else
    {
        timestamp = tempData.timestamp;
        temperature = tempData.temperature;
        windspeed = tempData.windspeed;
        return *this;
    }
}

//comparison operator to check if two items are the same
bool operator == (WeatherData& aItem, WeatherData& bItem)
{
    bool    same = false;
    int     timeOne = aItem.getTimeStamp();
    int     timeTwo = bItem.getTimeStamp();
    int     tempOne = aItem.getTemperature();
    int     tempTwo = bItem.getTemperature();
    int     windOne = aItem.getWindSpeed();
    int     windTwo = bItem.getWindSpeed();

    if ((timeOne == timeTwo) && (tempOne == tempTwo) && (windOne == windTwo))
        same = true;

    return same;
}
