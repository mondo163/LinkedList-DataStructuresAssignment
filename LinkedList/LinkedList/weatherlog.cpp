// Created my professor as the starting for the point for the project that would be unmodified 
// and all the remaining code will be added to this file. 

#include <iostream>
#include <fstream>
#include "datalogger.h"

using namespace std;

void createReport(datalogger& dl,const char* label)
{
    dl.printReport(label);
}

int main(int argc, char** argv) {

    datalogger rawDatalog;
    datalogger cleanDatalog;

    if (argc != 2) {
	cout << "Usage: " << argv[0] << " <datafile>" << endl;
	exit(0);
    }

    // Read the data

    char* datafile = argv[1];
    ifstream inDatafile(datafile);
    int timestamp;
    int temperature;
    int windspeed;
    
    while (!inDatafile.eof()) {
	inDatafile >> timestamp;
	inDatafile >> temperature;
	inDatafile >> windspeed;

	if (!inDatafile.eof()) {
	    if (rawDatalog.containsTimestamp(timestamp)) {
		cleanDatalog.removeData(timestamp);
	    } else {
		cleanDatalog.addData(timestamp,temperature,windspeed);
	    }

	    rawDatalog.addData(timestamp, temperature, windspeed);
	}
    }

    createReport(rawDatalog,"raw data");
    cout << endl;
    createReport(cleanDatalog,"clean data");
    
    return(0);
}
