/* Created by Nguyen Duc Dung on 2019-09-03.
 * =========================================================================================
 * Name        : dbLib.h
 * Author      : Duc Dung Nguyen
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - HCMUT
 * Description : The data structure library for Assignment 1
 * Course      : Data Structure and Algorithms - Fall 2019
 * =========================================================================================
 */

#ifndef DSA191_A1_DBLIB_H
#define DSA191_A1_DBLIB_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstring>
#include <sstream>
#include <math.h>

#include "dsaLib.h"

/* TODO: Please design your data structure carefully so that you can work with the given dataset
 *       in this assignment. The below structures are just some suggestions.
 */



struct date {
	string date;
};

struct TCity {
	int id;
	string name;
	string coords;
	int start_year;
	string url_name;
	string country;
	string country_state;
};

struct TLine {
	int id;
	int city_id;
	string name;
	string url_name;
	string color;
	int system_id;
	int transport_mode_id;
};

struct TStationLine {
	int id;
	int station_id;
	int line_id;
	int city_id;
	string created_at;
	string updated_at;
};

struct TStation {
	int id;
	string name;
	string geometry;
	int buildstart;
	int opening;
	int closure;
	int city_id;
};

struct TSystem {
	int id;
	int city_id;
	string name;

	TSystem* next;
};

struct TTrack {
	int id;
	string geometry;
	int buildstart;
	int opening;
	int closure;
	int length;
	int city_id;
};

struct TTrackLine {
	int id;
	int section_id;
	int line_id;
	string created_at;
	string updated_at;
	int city_id;
};

class TDataset {
	// This class can be a container that help you manage your tables
	L1List<TCity>* City = new L1List<TCity>;
	L1List<TLine>* Line = new L1List<TLine>;
	L1List<TStationLine>* StationLine = new L1List<TStationLine>;
	L1List<TStation>* Station = new L1List<TStation>;
	L1List<TSystem>* System = new L1List<TSystem>;
	L1List<TTrack>* Track = new L1List<TTrack>;
	L1List<TTrackLine>* TrackLine = new L1List<TTrackLine>;
public:
	TDataset() {}
	~TDataset() {
		City->clean();
		Line->clean();
		StationLine->clean();
		Station->clean();
		System->clean();
		Track->clean();
		TrackLine->clean();
	}

	size_t getsize_City() {
		return City->getSize();
	}
	size_t getsize_Line() {
		return Line->getSize();
	}
	size_t getsize_StationLine() {
		return StationLine->getSize();
	}
	size_t getsize_Station() {
		return Station->getSize();
	}
	size_t getsize_System() {
		return System->getSize();
	}
	size_t getsize_Track() {
		return Track->getSize();
	}
	size_t getsize_TrackLine() {
		return TrackLine->getSize();
	}

	void setData_City(TCity& City) {
		this->City->push_back(City);
	}
	void setData_Line(TLine& Line) {
		this->Line->push_back(Line);
	}
	void setData_StationLine(TStationLine& StationLine) {
		this->StationLine->push_back(StationLine);
	}
	void setData_Station(TStation Station) {
		this->Station->push_back(Station);
	}
	void setData_System(TSystem& System) {
		this->System->push_back(System);
	}
	void setData_Track(TTrack& Track) {
		this->Track->push_back(Track);
	}
	void setData_TrackLine(TTrackLine& TrackLine) {
		this->TrackLine->push_back(TrackLine);
	}

	/* Requested functions */

	int find_CityID_City_CityName(string& city_name) {
		size_t getSize = City->getSize();
		for (size_t i = 0; i < getSize; i++) {
			if (City->at(i).name == city_name) {
				return City->at(i).id;
			}
		}
		return -1;
	}

	int count_numLine_Line_CityID(int& city_id) {
		int count = 0;
		size_t getSize = Line->getSize();
		for (size_t i = 0; i < getSize; i++) {
			if (Line->at(i).city_id == city_id) count++;
		}
		if (count == 0) return -1;
		return count;
	}

	int* list_StationID_Station_CityID(int& city_id, int& N) {
		int count = 0;
		L1List<int>* arr_list = new L1List<int>;
		int temp;
		size_t getSize = Station->getSize();
		for (size_t i = 0; i < getSize; i++) {
			if (Station->at(i).city_id == city_id) {
				temp = Station->at(i).id;
				arr_list->push_back(temp);
				count++;
			}
		}
		int* arr = new int[count];
		for (int i = 0; i < count; i++) {
			arr[i] = arr_list->at(i);
		}
		arr_list->clean();
		arr_list = NULL;
		N = count;
		return arr;
	}

	int* list_LineID_Line_CityID(int& city_id, int& N) {
		int count = 0;
		L1List<int>* arr_list = new L1List<int>;
		int temp;
		size_t getSize = Line->getSize();
		for (size_t i = 0; i < getSize; i++) {
			if (Line->at(i).city_id == city_id) {
				temp = Line->at(i).id;
				arr_list->push_back(temp);
				count++;
			}
		}
		int* arr = new int[count];
		for (int i = 0; i < count; i++) {
			arr[i] = arr_list->at(i);
		}
		arr_list->clean();
		arr_list = NULL;
		N = count;
		return arr;
	}

	int* list_StationID_StationLine_LineID(int& line_id, int& N) {
		int count = 0;
		L1List<int>* arr_list = new L1List<int>;
		int temp;
		size_t getSize = StationLine->getSize();
		for (size_t i = 0; i < getSize; i++) {
			if (StationLine->at(i).line_id == line_id) {
				temp = StationLine->at(i).station_id;
				arr_list->push_back(temp);
				count++;
			}
		}
		int* arr = new int[count];
		for (int i = 0; i < count; i++) {
			arr[i] = arr_list->at(i);
		}
		arr_list->clean();
		arr_list = NULL;
		N = count;
		return arr;
	}

	int find_StationID_Station_StationName(string& station_name) {
		size_t getSize = Station->getSize();
		for (size_t i = 0; i < getSize; i++) {
			if (Station->at(i).name == station_name) {
				return Station->at(i).id;
			}
		}
		return -1;
	}

	string find_StationGeometry_Station_StationID(int& station_id) {
		if (station_id == NULL) return "\0";
		size_t getSize = Station->getSize();
		for (size_t i = 0; i < getSize; i++) {
			if (Station->at(i).id == station_id)
				return Station->at(i).geometry;
		}
		return "\0";
	}

	int find_StationIDX_Track_StationGeometry_TrackID(string& point, int track_id) {
		if (track_id == NULL || point == "\0") return -1;
		size_t getSize = Track->getSize();
		for (size_t i = 0; i < getSize; i++) {
			if (Track->at(i).id == track_id) {
				int count = 0;
				string cell_temp;
				stringstream ss_temp;
				ss_temp.str(Track->at(i).geometry);
				while (getline(ss_temp, cell_temp, ',')) {
					if (cell_temp == point) {
						return count;
					}
					count++;
				}
			}
		}
		return -1;
	}

	int insert_Station_Station(string& csv_description);

	int remove_Station_Dataset_StationID(int& staion_id);

	int update_StationID_Station(int& station_id, string& csv_description);

	int insert_Station_StationLine(int &station_id, int& line_id, int& p_i) {
		size_t getSize = Station->getSize();
		int count = 0; bool notExisted = true; int pos = -1;
		for (size_t i = 0; i < getSize; i++) {
			if (Station->at(i).id == station_id) {
				notExisted = false;
				break;
			}
		}
		if (!notExisted) {
			notExisted = true;
			getSize = StationLine->getSize();
			for (size_t i = 0; i < getSize; i++) {
				TStationLine* pCur = &StationLine->at(i);
				if (pCur->station_id == station_id) {
					notExisted = false;
					break;
				}
				if (pCur->line_id == line_id) {
					if (p_i == count) {
						pos = i;
						break;
					}
					count++;
				}
			}
			if (notExisted) {
				TStationLine temp;
				temp.line_id = line_id;
				temp.station_id = station_id;
				if (StationLine->insert(pos, temp) == 0) return 0;
			}
		}
		return -1;
	}

	int remove_Station_StationLine_StationID_LineID(int& station_id, int& line_id) {
		size_t getSize = StationLine->getSize();
		for (size_t i = 0; i < getSize; i++) {
			TStationLine* pCur = &StationLine->at(i);
			if (pCur->station_id == station_id && pCur->line_id == line_id) {
				if (StationLine->remove(i) == 0) return 0;
			}
		}
		return -1;
	}

	/* Extended functions */

	int remove_Station_StationLine_StationID(int& station_id) {
		size_t getSize = StationLine->getSize();
		for (size_t i = 0; i < getSize; i++) {
			TStationLine* pCur = &StationLine->at(i);
			if (pCur->station_id == station_id) {
				if (StationLine->remove(i) == 0) return 0;
			}
		}
		return -1;
	}

	int remove_StationLS_Track_StationGeometry_CityID(string& point, int& city_id);
	
	int get_IDmax_Station() {
		return Station->get_IDmax();
	}

	void set_IDmax_Station(int& id_max) {
		Station->set_IDmax(id_max);
	}
};

void LoadData(void*&);
void ReleaseData(void*&);

void LoadData_City(stringstream&, TCity*&);
void LoadData_Line(stringstream&, TLine*&);
void LoadData_StationLine(stringstream&, TStationLine*&);
void LoadData_Station(stringstream&, TStation*&);
void LoadData_System(stringstream&, TSystem*&);
void LoadData_Track(stringstream&, TTrack*&);
void LoadData_TrackLine(stringstream&, TTrackLine*&);

#endif //DSA191_A1_DBLIB_H