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
	void insertData_City(TCity& City) {
		this->City->push_back(City);
	}
	void insertData_Line(TLine& Line) {
		this->Line->push_back(Line);
	}
	void insertData_StationLine(TStationLine& StationLine) {
		this->StationLine->push_back(StationLine);
	}
	void insertData_Station(TStation Station) {
		this->Station->push_back(Station);
	}
	void insertData_System(TSystem& System) {
		this->System->push_back(System);
	}
	void insertData_Track(TTrack& Track) {
		this->Track->push_back(Track);
	}
	void insertData_TrackLine(TTrackLine& TrackLine) {
		this->TrackLine->push_back(TrackLine);
	}

	/* Requested functions */
	
	int find_CityID_City(string& city_name);
	int count_numLine_Line(int& city_id);

	int* list_StationID_Station(int& city_id, int& N);
	int* list_LineID_Line(int& city_id, int& N);
	int* list_StationID_StationLine(int& line_id, int& N);

	int find_StationID_Station(string& station_name);
	string find_StationGeometry_Station(int& station_id);
	int find_StationIDX_Track(string& point, int track_id);

	int insert_Station_Station(string& csv_description);
	int remove_Station_Dataset(int& station_id);
	
	int update_Station_Dataset(int& station_id, string& csv_description);
	
	int insert_Station_StationLine(int& station_id, int& line_id, int& p_i);
	int remove_Station_StationLine(int& station_id, int& line_id);

	/* Child function */

	void remove_Station_StationLine(int& station_id);
	void remove_StationLS_Track(string& point, int& city_id);

	void update_Station_StationLine(int& station_id, int& station_id_n);
	void update_StationLS_Track(string& point, int& city_id, string& point_n);

	int get_IDmax_Station() {
		return Station->get_IDmax();
	}

	void set_IDmax_Station(int& id_max) {
		Station->set_IDmax(id_max);
	}

	/* Added functions */

	int ASLP(int&);
};

void LoadData(void*&);
void ReleaseData(void*&);

void createData_City(string&, TCity&);
void createData_Line(string&, TLine&);
void createData_StationLine(string&, TStationLine&);
void createData_Station(string&, TStation&);
void createData_System(string&, TSystem&);
void createData_Track(string&, TTrack&);
void createData_TrackLine(string&, TTrackLine&);

void remove_DQMarks(string&);
void csv_row_reader(stringstream&, string&);

#endif //DSA191_A1_DBLIB_H