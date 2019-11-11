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
	
	int* find_CityID_City_CityName(string& city_name) {
		
		// Create pointer 
		int* p_city_id = new int(-1);
		string* p_city_name = &city_name;

		// Traverse
		City->traverse(
			[](TCity& City, void*& city_name, void*& city_id) -> bool {
				if (City.name == *(string*)city_name) {
					*(int*)city_id = City.id;
					return true;
				}
				return false;
			}, (void*&)p_city_name, (void*&)p_city_id);

		return p_city_id; // -1 or p_city_id
	}

	int* count_numLine_Line_CityID(int& city_id) {

		// Create pointer 
		int* p_count = new int (0);
		int* p_city_id = &city_id; 

		// Traverse
		if (city_id != -1) {
			Line->traverse(
				[](TLine& Line, void*& city_id, void*& count) -> bool {
					if (Line.city_id == *(int*)city_id)
						(*(int*)count)++;
					return false;
				}, (void*&)p_city_id, (void*&)p_count);
		}
		if (*p_count == 0) *p_count = -1;
		return p_count; // -1 or p_count 
	}

	int* list_StationID_Station_CityID(int& city_id, int& N) {
		
		N = 0;

		// Create pointer 
		int* p_count = &N;
		int* p_city_id = &city_id;
		L1List<int>* arr_list = new L1List<int>;

		if (city_id != -1) {
			Station->traverse(
				[](TStation& Station, void*& city_id, void*& arr_list) -> bool {
					if (Station.city_id == *(int*)city_id) {
						((L1List<int>*)arr_list)->push_back(Station.id);
					}
					return false;
				}, (void*&)p_city_id, (void*&)arr_list);
		}

		// Create an array of int
		N = arr_list->getSize(); 

		int* arr_int = new int[N];
		if (N > 0) {
			N = 0;
			arr_list->traverse(
				[](int& list, void*& count, void*& arr_int) -> bool {
					((int*)arr_int)[(*(int*)count)++] = list;
					return false;
				}, (void*&)p_count, (void*&)arr_int);
		}

		arr_list->clean(); // Clean up the temp list

		return arr_int;
	}

	int* list_LineID_Line_CityID(int& city_id, int& N) {
		
		N = 0;

		// Create pointer 
		int* p_count = &N;
		int* p_city_id = &city_id;
		L1List<int>* arr_list = new L1List<int>;

		if (city_id != -1) {
			Line->traverse(
				[](TLine& Line, void*& city_id, void*& arr_list) -> bool {
					if (Line.city_id == *(int*)city_id) {
						((L1List<int>*)arr_list)->push_back(Line.id);
					}
					return false;
				}, (void*&)p_city_id, (void*&)arr_list);
		}

		// Create an array of int
		N = arr_list->getSize();

		int* arr_int = new int[N];
		if (N > 0) {
			N = 0;
			arr_list->traverse(
				[](int& list, void*& count, void*& arr_int) -> bool {
					((int*)arr_int)[(*(int*)count)++] = list;
					return false;
				}, (void*&)p_count, (void*&)arr_int);
		}

		arr_list->clean(); // Clean up the temp list

		return arr_int;
	}

	int* list_StationID_StationLine_LineID(int& line_id, int& N) {
		
		N = 0;

		// Create pointer 
		int* p_count = &N;
		int* p_line_id = &line_id;
		L1List<int>* arr_list = new L1List<int>;

		if (line_id != -1) {
			StationLine->traverse(
				[](TStationLine& StationLine, void*& line_id, void*& arr_list) -> bool {
					if (StationLine.line_id == *(int*)line_id) {
						((L1List<int>*)arr_list)->push_back(StationLine.station_id);
					}
					return false;
				}, (void*&)p_line_id, (void*&)arr_list);
		}

		// Create an array of int
		N = arr_list->getSize();

		int* arr_int = new int[N];
		if (N > 0) {
			N = 0;
			arr_list->traverse(
				[](int& list, void*& count, void*& arr_int) -> bool {
					((int*)arr_int)[(*(int*)count)++] = list;
					return false;
				}, (void*&)p_count, (void*&)arr_int);
		}

		arr_list->clean(); // Clean up the temp list

		return arr_int;
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

	/* Added functions */

	int ALSP() {
		size_t number = 0;
		size_t numberTotal = getsize_Station();
		int total = 0;
		for (size_t i = 0; i < getsize_Station(); i++) {
			int station_id = Station->at(i).id;
			cout << left << setw(5) << number++ << " of " << numberTotal << " || station_id = " << station_id;
			string point = find_StationGeometry_Station_StationID(station_id);
			int track_id;
			int output = find_StationIDX_Track_StationGeometry(point, track_id);
			if (output != -1) cout << " || track_id = " << track_id << " | INDEX = " << output << " | POINT = " << point << endl;
			else cout << " || Not found\n";
		}
		if (total == 0) return -1;
		return total;
	}

	int find_StationIDX_Track_StationGeometry(string& point, int& track_id) {
		if (point == "\0") return -1;
		size_t getSize = Track->getSize();
		for (size_t i = 0; i < getSize; i++) {
			int count = 0;
			TTrack* pTemp = &Track->at(i);
			string cell_temp;
			stringstream ss_temp;
			ss_temp.str(pTemp->geometry);
			while (getline(ss_temp, cell_temp, ',')) {
				if (cell_temp == point) {
					track_id = pTemp->id;
					return count;
				}
				count++;
			}
		}
		return -1;
	}
};

void LoadData(void*&);
void ReleaseData(void*&);

void createData_City(stringstream&, TCity&);
void createData_Line(stringstream&, TLine&);
void createData_StationLine(stringstream&, TStationLine&);
void createData_Station(stringstream&, TStation&);
void createData_System(stringstream&, TSystem&);
void createData_Track(stringstream&, TTrack&);
void createData_TrackLine(stringstream&, TTrackLine&);

#endif //DSA191_A1_DBLIB_H