/* Created by Nguyen Duc Dung on 2019-09-03.
 * =========================================================================================
 * Name        : dbLib.cpp
 * Author      : Duc Dung Nguyen
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - HCMUT
 * Description : The data structure library for Assignment 1
 * Course      : Data Structure and Algorithms - Fall 2019
 * =========================================================================================
 */

#include "dbLib.h"

/* TODO: You can implement methods, functions that support your data structures here.
 * */

void LoadData(void*& pData) {
	TDataset* Dataset = new TDataset;

	fstream file;

	string input;
	stringstream ss;
	string cell;

	// cities.csv
	file.open("cities.csv");
	TCity* City;
	getline(file, input);
	while (getline(file, input)) {
		ss.clear();
		ss.str(input);
		if (ss.str() != "") {
			City = new TCity;
			LoadData_City(ss, City);
			Dataset->setData_City(*City);
			delete City;
		}
	}
	file.close();

	// lines.csv
	file.open("lines.csv");
	TLine* Line;
	getline(file, input);
	while (getline(file, input)) {
		ss.clear();
		ss.str(input);
		if (ss.str() != "") {
			Line = new TLine;
			LoadData_Line(ss, Line);
			Dataset->setData_Line(*Line);
			delete Line;
		}
	}
	file.close();

	// station_lines.csv
	file.open("station_lines.csv");
	TStationLine* StationLine;
	getline(file, input);
	while (getline(file, input)) {
		ss.clear();
		ss.str(input);
		if (ss.str() != "") {
			StationLine = new TStationLine;
			LoadData_StationLine(ss, StationLine);
			Dataset->setData_StationLine(*StationLine);
			delete StationLine;
		}
	}
	file.close();

	// stations.csv
	file.open("stations.csv");
	TStation* Station;
	getline(file, input);
	while (getline(file, input)) {
		ss.clear();
		ss.str(input);
		if (ss.str() != "") {
			Station = new TStation;
			LoadData_Station(ss, Station);
			
			// Update id_max
			int id_max = Dataset->get_IDmax_Station();
			int id_temp = Station->id;
			if (id_max < id_temp) id_max = id_temp;
			Dataset->set_IDmax_Station(id_max);
			// End Update id_max
			
			
			Dataset->setData_Station(*Station);
			delete Station;
		}
	}
	file.close();

	// systems.csv
	/*
	file.open("systems.csv");
	TSystem *System;
	getline(file, input);
	while (getline(file, input)) {
		ss.clear();
		ss.str(input);
		if (ss.str() != "") {
			System = new TSystem;
			LoadData_System(ss, System);
			Dataset->setData_System(*System);
		}
	}
	file.close();
	*/

	// tracks.csv
	file.open("tracks.csv");
	TTrack* Track;
	getline(file, input);
	while (getline(file, input)) {
		ss.clear();
		ss.str(input);
		if (ss.str() != "") {
			Track = new TTrack;
			LoadData_Track(ss, Track);
			Dataset->setData_Track(*Track);
			delete Track;
		}
	}
	file.close();

	// track_lines.csv
	/*
	file.open("track_lines.csv");
	TTrackLine* TrackLine;
	getline(file, input);
	while (getline(file, input)) {
		ss.clear();
		ss.str(input);
		if (ss.str() != "") {
			TrackLine = new TTrackLine;
			LoadData_TrackLine(ss, TrackLine);
			Dataset->setData_TrackLine(*TrackLine);
			delete TrackLine;
		}
	}
	file.close();
	*/

	// Set database's pointer
	pData = Dataset;
	Dataset = nullptr;
}

void ReleaseData(void*& pData) {
	TDataset* Dataset;
	Dataset = (TDataset *)pData;
	Dataset->~TDataset();
	Dataset = nullptr;
}

/* Functions that each of other loads its own database; */

void LoadData_City(stringstream& ss, TCity*& City) {
	string cell;
	//cout << "lineStream.str() = " << ss.str() << std::endl;

	//id, name, coords, start_year, url_name, country, country_state
	getline(ss, cell, ',');
	if (cell != "\0") City->id = atoi(cell.c_str());
	getline(ss, cell, ',');
	City->name = cell;
	getline(ss, cell, ',');
	City->coords = cell;
	getline(ss, cell, ',');
	if (cell != "\0") City->start_year = atoi(cell.c_str());
	getline(ss, cell, ',');
	City->url_name = cell;
	getline(ss, cell, ',');
	City->country = cell;
	getline(ss, cell);
	City->country_state = cell;
}

void LoadData_Line(stringstream& ss, TLine*& Line) {
	string cell;
	//cout << "lineStream.str() = " << ss.str() << std::endl;

	//id, city_id, name, url_name, color, system_id, transport_mode_id
	getline(ss, cell, ',');
	if (cell != "\0") Line->id = atoi(cell.c_str());
	getline(ss, cell, ',');
	if (cell != "\0") Line->city_id = atoi(cell.c_str());
	getline(ss, cell, ',');
	Line->name = cell;
	getline(ss, cell, ',');
	Line->url_name = cell;
	getline(ss, cell, ',');
	Line->color = cell;
	getline(ss, cell, ',');
	if (cell != "\0") Line->system_id = atoi(cell.c_str());
	getline(ss, cell, ',');
	if (cell != "\0") Line->transport_mode_id = atoi(cell.c_str());
};

void LoadData_StationLine(stringstream& ss, TStationLine*& StationLine) {
	string cell;
	//cout << "lineStream.str() = " << ss.str() << std::endl;

	//id, station_id, line_id, city_id, created_at, updated_at
	getline(ss, cell, ',');
	if (cell != "\0") StationLine->id = atoi(cell.c_str());
	getline(ss, cell, ',');
	if (cell != "\0") StationLine->station_id = atoi(cell.c_str());
	getline(ss, cell, ',');
	if (cell != "\0") StationLine->line_id = atoi(cell.c_str());
	getline(ss, cell, ',');
	if (cell != "\0") StationLine->city_id = atoi(cell.c_str());
	getline(ss, cell, ',');
	StationLine->created_at = cell;
	getline(ss, cell, ',');
	StationLine->updated_at = cell;
};

void LoadData_Station(stringstream& ss, TStation*& Station) {
	string cell;
	//cout << "lineStream.str() = " << ss.str() << std::endl;

	//id, name, geometry, buildstart, opening, closure, city_id
	getline(ss, cell, ',');
	if (cell != "\0") Station->id = atoi(cell.c_str());
	getline(ss, cell, ',');
	Station->name = cell;
	getline(ss, cell, ')');
	Station->geometry = cell.substr(6, cell.length() - 6);
	getline(ss, cell, ',');
	getline(ss, cell, ',');
	if (cell != "\0") Station->buildstart = atoi(cell.c_str());
	getline(ss, cell, ',');
	if (cell != "\0") Station->opening = atoi(cell.c_str());
	getline(ss, cell, ',');
	if (cell != "\0") Station->closure = atoi(cell.c_str());
	getline(ss, cell, ',');
	if (cell != "\0") Station->city_id = atoi(cell.c_str());
};

void LoadData_System(stringstream& ss, TSystem*& System) {
	string cell;
	//cout << "lineStream.str() = " << ss.str() << std::endl;

	System = new TSystem;
	//id, city_id, name
	getline(ss, cell, ',');
	if (cell != "\0") System->id = atoi(cell.c_str());
	getline(ss, cell, ',');
	if (cell != "\0") System->city_id = atoi(cell.c_str());
	getline(ss, cell, ',');
	System->name = cell;
};

void LoadData_Track(stringstream& ss, TTrack*& Track) {
	string cell;
	//cout << "lineStream.str() = " << ss.str() << std::endl;

	//id, geometry, buildstart, opening, closure, length, city_id
	getline(ss, cell, ',');
	if (cell != "\0") Track->id = atoi(cell.c_str());
	getline(ss, cell, ')');
	Track->geometry = cell.substr(12, cell.length() - 12);
	getline(ss, cell, ',');
	getline(ss, cell, ',');
	if (cell != "\0") Track->buildstart = atoi(cell.c_str());
	getline(ss, cell, ',');
	if (cell != "\0") Track->opening = atoi(cell.c_str());
	getline(ss, cell, ',');
	if (cell != "\0") Track->closure = atoi(cell.c_str());
	getline(ss, cell, ',');
	if (cell != "\0") Track->length = atoi(cell.c_str());
	getline(ss, cell, ',');
	if (cell != "\0") Track->city_id = atoi(cell.c_str());
};

void LoadData_TrackLine(stringstream& ss, TTrackLine*& TrackLine) {
	string cell;
	//cout << "lineStream.str() = " << ss.str() << std::endl;

	//id, section_id, line_id, created_at, updated_at, city_id
	getline(ss, cell, ',');
	if (cell != "\0") TrackLine->id = atoi(cell.c_str());
	getline(ss, cell, ',');
	if (cell != "\0") TrackLine->section_id = atoi(cell.c_str());
	getline(ss, cell, ',');
	if (cell != "\0") TrackLine->line_id = atoi(cell.c_str());
	getline(ss, cell, ',');
	TrackLine->created_at = cell;
	getline(ss, cell, ',');
	TrackLine->updated_at = cell;
	getline(ss, cell, ',');
	if (cell != "\0") TrackLine->city_id = atoi(cell.c_str());
};

/* From Dataset */

int TDataset::insert_Station_Station(string& csv_description) {
	if (csv_description == "\0") return -1;

	size_t getSize = Station->getSize();

	// Update id_max
	int id_max = Station->get_IDmax();
	if (id_max == -1) {
		for (size_t i = 0; i < getSize; i++) {
			int temp = Station->at(i).id;
			if (id_max < temp) id_max = temp;
		}
	}
	Station->set_IDmax(++id_max);
	// End Update id_max

	string cell_temp;
	stringstream ss_temp;
	ss_temp.str(csv_description);
	
	TStation* Station;
	Station = new TStation;
	LoadData_Station(ss_temp, Station);

	Station->id = id_max;
	Station->city_id = NULL;

	setData_Station(*Station);
	delete Station;
	
	return id_max;
}

int TDataset::remove_Station_Dataset_StationID(int& station_id) {
	if (station_id == NULL) return -1;

	size_t getSize = Station->getSize();
	TStation* temp;
	
	string point; 
	int city_id;
	
	bool notExisted = true;
	for (size_t i = 0; i < getSize; i++) {
		temp = &Station->at(i);
		if (temp->id == station_id) {

			point = temp->geometry;
			city_id = temp->city_id;

			if (Station->remove(i) == -1) return -1;
			notExisted = false;
			break;
		}
	}
	if (notExisted) return -1;

	// Update id_max
	if (station_id == Station->get_IDmax()) {
		int id_temp = -1;
		Station->set_IDmax(id_temp);
	}
	// End Update id_max

	// Remove any records related to the station
	remove_Station_StationLine_StationID(station_id);
	remove_StationLS_Track_StationGeometry_CityID(point, city_id);
	return 0;
}

int TDataset::update_StationID_Station(int& station_id, string& csv_description) {
	size_t getSize = Station->getSize();
	TStation* Station;
	bool notExisted = true;
	for (size_t i = 0; i < getSize; i++) {
		Station = &this->Station->at(i);
		if (Station->id == station_id) {
			notExisted = false;
			break;
		}
	}
	if (notExisted)	return -1;

	stringstream ss_temp;
	ss_temp.str(csv_description);
	LoadData_Station(ss_temp, Station);
	Station = nullptr;
	return 0;
};

int TDataset::remove_StationLS_Track_StationGeometry_CityID(string& point, int& city_id) {
	if (point == "\0" || city_id == NULL) return -1;
	size_t getSize = Track->getSize();
	TTrack* pCur;
	for (size_t i = 0; i < getSize; i++) {
		pCur = &Track->at(i);
		if (pCur->city_id == city_id) {
			int pos = pCur->geometry.find(point);
			if (pos != -1) {
				pCur->geometry.erase(pos, point.length());
				return 0;
			}
		}
	}
	return -1;
}