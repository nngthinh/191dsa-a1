/* Created by Nguyen Duc Dung on 2019-09-03.
 * =========================================================================================
 * Name        : processData.cpp
 * Author      : Duc Dung Nguyen
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - HCMUT
 * Description : Implementation of main features in the assignment
 * Course      : Data Structure and Algorithms - Fall 2019
 * =========================================================================================
 */

#include "processData.h"
#include "dbLib.h"

/* TODO: You can implement methods, functions that support your data structures here.
 * */
using namespace std;

void Initialization() {
    // If you use global variables, please initialize them explicitly in this function.
}

void Finalization() {
    // Release your data before exiting
}

void ProcessRequest(const char* pRequest, void* pData, void* &pOutput, int &N) {
    // TODO: Implement this function for processing a request
    // NOTE: You can add other functions to support this main process.
    //       pData is a pointer to a data structure that manages the dataset
    //       pOutput is a pointer reference. It is set to nullptr and student must allocate data for it in order to save the required output
    //       N is the size of output, must be a non-negative number
	TDataset* Dataset;
	Dataset = (TDataset*)pData;

	stringstream ss;
	string request, cell1, cell2, cell3;
	ss.str(pRequest);
	getline(ss, request, ' ');

	if (request == "CL") {
		getline(ss, cell1);
		//CL
		if (cell1 == "\0") {
			pOutput = new int* ();
			*(int*)pOutput = Dataset->getsize_Line();
			N = 1;
		}
		//CL <city_name>
		else {
			int* city_id = Dataset->find_CityID_City_CityName(cell1);
			pOutput = Dataset->count_numLine_Line_CityID(*city_id);
			if (city_id) delete city_id; // Remove unnecessary pointer 
			N = 1;
		}
	}
	
	else if (request == "LSC") {
		//LSC <city_name>
		getline(ss, cell1);
		int* city_id = Dataset->find_CityID_City_CityName(cell1);
		pOutput = Dataset->list_StationID_Station_CityID(*city_id, N); 
		if (city_id) delete city_id; // Remove unnecessary pointer 
	}
	else if (request == "LLC") {
		//LLC <city_name>
		getline(ss, cell1);
		int *city_id = Dataset->find_CityID_City_CityName(cell1);
		pOutput = Dataset->list_LineID_Line_CityID(*city_id, N);
		if (city_id) delete city_id; // Remove unnecessary pointer 
	}
	else if (request == "LSL") {
		//LSL <line_id>
		ss >> cell1;
		int line_id = atoi(cell1.c_str());
		pOutput = Dataset->list_StationID_StationLine_LineID(line_id, N);
	}
	else if (request == "FC") {
		//FC <city_name>
		getline(ss, cell1);
		pOutput = (void*)Dataset->find_CityID_City_CityName(cell1);
		N = 1;
	}
	else if (request == "FS") {
		//FS <station_name>
		getline(ss, cell1);
		pOutput = new int* ();
		*(int*)pOutput = Dataset->find_StationID_Station_StationName(cell1);
		N = 1;
	}
	else if (request == "SLP") {
		//SLP <station_id> <track_id>
		ss >> cell1 >> cell2;
		pOutput = new int* ();
		int station_id = atoi(cell1.c_str());
		int track_id = atoi(cell2.c_str());
		string point = Dataset->find_StationGeometry_Station_StationID(station_id);
		*(int*)pOutput = Dataset->find_StationIDX_Track_StationGeometry_TrackID(point, track_id);
		N = 1;
	}
	else if (request == "IS") {
		//IS <csv_description>
		getline(ss, cell1);
		pOutput = new int* ();
		*(int*)pOutput = Dataset->insert_Station_Station(cell1);
		N = 1;
	}
	else if (request == "RS") {
		//RS <station_id>
		ss >> cell1;
		int station_id = atoi(cell1.c_str());
		pOutput = new int* ();
		*(int*)pOutput = Dataset->remove_Station_Dataset_StationID(station_id);
		N = 1;
	}
	else if (request == "US") {
		//US <station_id> <csv_description>
		getline(ss, cell1, ' ');
		getline(ss, cell2);
		int station_id = atoi(cell1.c_str());
		pOutput = new int* ();
		*(int*)pOutput = Dataset->update_StationID_Station(station_id, cell2);
		N = 1;
	}
	else if (request == "ISL") {
		//ISL <station_id> <line_id> <p_i>
		ss >> cell1 >> cell2 >> cell3;
		pOutput = new int* ();
		int station_id = atoi(cell1.c_str());
		int line_id = atoi(cell2.c_str());
		int p_i = atoi(cell3.c_str());
		*(int*)pOutput = Dataset->insert_Station_StationLine(station_id, line_id, p_i);
		N = 1;
	}
	else if (request == "RSL") {
		//RSL <station_id> <line_id>
		ss >> cell1 >> cell2;
		pOutput = new int* ();
		int station_id = atoi(cell1.c_str());
		int line_id = atoi(cell2.c_str());
		*(int*)pOutput = Dataset->remove_Station_StationLine_StationID_LineID(station_id, line_id);
		N = 1;
	}
	
	//Added
	else if (request == "ASLP") { 
		//ASLP
		pOutput = new int* ();
		*(int*)pOutput = Dataset->ALSP();
		N = 1;
	}
}