// implementation for the datalogger object and how the data is logged to 
// the console. 

#include "datalogger.h"

datalogger::datalogger()
{
    //Nothing to construct  
}

datalogger::~datalogger()
{   
    //Nothing to destruct
}

//returns boolean value if timestamp is found
bool datalogger::containsTimestamp(int& timestamp)
{
    return list.retrieve(timestamp);
}

//returns boolean value if data has been removed
bool datalogger::removeData(int& timestamp)
{
    return list.remove(timestamp);
}

//returns boolean value if data was added
void datalogger::addData(int timestamp, int temperature, int windspeed)
{
    WeatherData tempData(timestamp, temperature, windspeed);
    list.insert(tempData);
    
}

//prints report
void datalogger::printReport(const char* label)
{
    cout << "\t\t\t\t -- Data Report (" << label << ") --" << endl;
    
    cout << "Time range:\t\t\t" << list.getTimeHead() << " - " << list.getTimeTail() << endl;
 
    cout << setw(50) << left << "Number of Entries:" << setw(6) << right << list.getSize() << endl;
    
    cout << setw(50) << left << "Number of entries with < -50C temperature:";
    cout << setw(6) << right << list.entriesLessThanFifty() << endl;

    cout << setw(50) << left << "Number of entries with > 0C temperature:";
    cout << setw(6) << right << list.entriesMoreThanZero() << endl;
 
    cout << setw(50) << left << "Most common temperature:";
    cout << setw(6) << right << fixed << setprecision(1);
    cout << static_cast<float>(list.mostCommonTemp())/10 << endl << endl;

    cout << setw(50) << left << "Number of entries with 0 windspeed:";
    cout << setw(6) << right << list.entriesZeroWindspeed() << endl;

    cout << setw(50) << left << "Number of entries with > 25 m/s windspeed:";
    cout << setw(6) << right << list.entriesMoreThanTwentyFive() << endl;
 
    cout << setw(50) << left << "Most common windspeed:";
    cout << setw(6) << right << list.mostCommonWind() << endl << endl;

    //Print the ranges based off of a scale and individually through a for loop
    cout << "Average temperature over ranges:" << endl;
    int rangeScale = list.getSize()/RANGE;
    for (int i = 0; i < RANGE; i++)
    {
        cout << left << i * rangeScale << " through " << (i+1)*rangeScale-1 << "\t\t\t" << setw(3) << right;
        cout << fixed << setprecision(1) << list.averageRangeTemp(i*rangeScale,(i+1)*rangeScale-1)/rangeScale << endl;
    }

    cout << "Average windspeed over ranges:" << endl;
    for (int i = 0; i < RANGE; i++)
    {
        cout << left << i * rangeScale << " through " << (i+1)*rangeScale-1 << "\t\t\t" << setw(3) << right;
        cout << fixed << setprecision(1) << list.averageRangeWind(i*rangeScale,(i+1)*rangeScale-1)/rangeScale << endl;
    }
 
    cout << endl; 
}
