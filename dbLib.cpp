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

 /* Requested functions */

int TDataset::find_CityID_City_CityName(string& city_name) {

	// Create pointer
	string* p_city_name = &city_name;
	int city_id = -1;
	int* p_city_id = &city_id;

	// Traverse: City
	City->traverse(
		[](TCity& City, void*& city_name, void*& city_id) -> bool {
			if (City.name == *(string*)city_name) {
				*(int*)city_id = City.id;
				return true;
			}
			return false;
		}
	, (void*&)p_city_name, (void*&)p_city_id);

	return city_id;
}

int TDataset::count_numLine_Line_CityID(int& city_id) {
	if (city_id == -1) return -1;

	// Create pointer 
	int* p_city_id = &city_id;
	int count = 0;
	int* p_count = &count;

	// Traverse: Line
	Line->traverse(
		[](TLine& Line, void*& city_id, void*& count) -> bool {
			if (Line.city_id == *(int*)city_id)
				(*(int*)count)++;
			return false;
		}
	, (void*&)p_city_id, (void*&)p_count);

	if (count == 0) count = -1;
	return count;
}

int* TDataset::list_StationID_Station_CityID(int& city_id, int& N) {

	N = 0;

	// Create pointer 
	int* p_city_id = &city_id;
	int* p_count = &N;
	L1List<int>* arr_list = new L1List<int>;

	if (city_id != -1) {
		// Traverse: Station
		Station->traverse(
			[](TStation& Station, void*& city_id, void*& arr_list) -> bool {
				if (Station.city_id == *(int*)city_id) {
					((L1List<int>*)arr_list)->push_back(Station.id);
				}
				return false;
			}
		, (void*&)p_city_id, (void*&)arr_list);
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
			}
		, (void*&)p_count, (void*&)arr_int);
	}

	arr_list->clean(); // Clean up the temp list

	return arr_int;
}

int* TDataset::list_LineID_Line_CityID(int& city_id, int& N) {

	N = 0;

	// Create pointer 
	int* p_city_id = &city_id;
	int* p_count = &N;
	L1List<int>* arr_list = new L1List<int>;

	if (city_id != -1) {
		// Traverse: Line
		Line->traverse(
			[](TLine& Line, void*& city_id, void*& arr_list) -> bool {
				if (Line.city_id == *(int*)city_id) {
					((L1List<int>*)arr_list)->push_back(Line.id);
				}
				return false;
			}
		, (void*&)p_city_id, (void*&)arr_list);
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
			}
		, (void*&)p_count, (void*&)arr_int);
	}

	arr_list->clean(); // Clean up the temp list

	return arr_int;
}

int* TDataset::list_StationID_StationLine_LineID(int& line_id, int& N) {

	N = 0;

	// Create pointer 
	int* p_line_id = &line_id;
	int* p_count = &N;
	L1List<int>* arr_list = new L1List<int>;

	if (line_id != -1) {
		// Traverse: StationLine
		StationLine->traverse(
			[](TStationLine& StationLine, void*& line_id, void*& arr_list) -> bool {
				if (StationLine.line_id == *(int*)line_id) {
					((L1List<int>*)arr_list)->push_back(StationLine.station_id);
				}
				return false;
			}
		, (void*&)p_line_id, (void*&)arr_list);
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
			}
		, (void*&)p_count, (void*&)arr_int);
	}

	arr_list->clean(); // Clean up the temp list

	return arr_int;
}

int TDataset::find_StationID_Station_StationName(string& station_name) {

	// Create pointer 
	string* p_station_name = &station_name;
	int station_id = -1;
	int* p_station_id = &station_id;

	// Traverse: Station
	Station->traverse(
		[](TStation& Station, void*& p_station_name, void*& p_station_id) -> bool {
			if (Station.name == *(string*)p_station_name) {
				*(int*)p_station_id = Station.id;
				return true;
			}
			return false;
		}
	, (void*&)p_station_name, (void*&)p_station_id);

	return station_id;
}

string TDataset::find_StationGeometry_Station_StationID(int& station_id) {
	if (station_id == -1) return "\0";

	// Create pointer 
	int* p_station_id = &station_id;
	string station_geometry;
	string* p_station_geometry = &station_geometry;

	// Traverse: Station
	Station->traverse(
		[](TStation& Station, void*& p_station_id, void*& p_station_geometry) -> bool {
			if (Station.id == *(int*)p_station_id) {
				*(string*)p_station_geometry = Station.geometry;
				return true;
			}
			return false;
		}
	, (void*&)p_station_id, (void*&)p_station_geometry);

	return station_geometry;
}

int TDataset::find_StationIDX_Track_StationGeometry_TrackID(string& point, int track_id) {
	if (point == "\0" || track_id == NULL) return -1;
	
	// Create pointer
	string* p_point = &point;
	int* p_track_id = &track_id;
	int station_idx = -1;
	int* p_station_idx = &station_idx;

	// Traverse: Track
	Track->traverse(
		[](TTrack& Track, void*& p_point, void*& p_track_id, void*& p_station_idx) -> bool {
			if (Track.id == *(int*)p_track_id) {
				*(int*)p_station_idx = 0;
				string cell;
				stringstream ss;
				ss.str(Track.geometry);
				while (getline(ss, cell, ',')) {
					if (cell == *(string*)p_point) {
						return true;
					}
					(*(int*)p_station_idx)++;
				}
			}
			*(int*)p_station_idx = -1;
			return false;
		}
	, (void*&)p_point, (void*&)p_track_id, (void*&)p_station_idx);

	return station_idx;
}

int TDataset::insert_Station_Station(string& csv_description) {
	if (csv_description == "\0") return -1;

	int id_max = Station->get_IDmax();
	
	if (id_max == -1) {

		int* p_id_max = &id_max; // Update id_max

		Station->traverse(
			[](TStation& Station, void*& p_id_max) -> bool {
				if (Station.id > * (int*)p_id_max)
					*(int*)p_id_max = Station.id;
				return false;
			}
		, (void*&)p_id_max);
	}

	Station->set_IDmax(++id_max);

	// Make new station data from csv to insert
	TStation Station;
	createData_Station(csv_description, Station);

	// Set id and city_id
	Station.id = id_max;
	Station.city_id = NULL;

	// Insert new station
	insertData_Station(Station);

	return id_max;
}

int TDataset::remove_Station_Dataset_StationID(int& station_id) {
	if (station_id == -1) return -1;

	// Create pointer
	int* p_station_id = &station_id;
	string point;
	string* p_point = &point;
	int city_id = -1;
	int* p_city_id = &city_id;
	int idx = 0;
	int* p_idx = &idx;

	// Traverse: Find the Station and get <station_id> and <geometry> of this
	Station->traverse(
		[](TStation& Station, void*& p_station_id, void*& p_point, void*& p_city_id, void*& p_idx) -> bool {
			if (Station.id == *(int*)p_station_id) {
				*(string*)p_point = Station.geometry;
				*(int*)p_city_id = Station.city_id;
				return true;
			}
			(*(int*)p_idx)++;
			return false;
		}
	, (void*&)p_station_id, (void*&)p_point, (void*&)p_city_id, (void*&)p_idx);
	
	// Remove the Station
	if (Station->remove(idx) == -1) return -1;

	// Update id_max
	if (station_id == Station->get_IDmax()) {
		int id_temp = -1;
		Station->set_IDmax(id_temp);
	}

	// Remove any records related to the station
	remove_Station_StationLine_StationID(station_id);
	remove_StationLS_Track_StationGeometry_CityID(point, city_id);

	return 0;
}

int TDataset::update_StationID_Station(int& station_id, string& csv_description) {
	if (station_id == -1) return -1;

	// Create pointer
	int* p_station_id = &station_id;
	string* csv = &csv_description;
	bool success = false;
	bool* p_success = &success;

	// Traverse: Update the information of the Station
	Station->traverse(
		[](TStation& Station, void*& p_station_id, void*& csv, void*& p_success) -> bool {
			if (Station.id == *(int*)p_station_id) {
				createData_Station(*(string*)csv, Station);
				*(bool*)p_success = true;
				return true;
			}
			return false;
		}
	, (void*&)p_station_id, (void*&)csv, (void*&)p_success);

	if (success) return station_id;
	return -1;
}

int TDataset::insert_Station_StationLine(int& station_id, int& line_id, int& p_i) {
	if (station_id == -1 || line_id == -1) return -1;

	// Create pointer
	int* p_station_id = &station_id;
	int* p_line_id = &line_id;
	
	int count = p_i;
	int* p_count = &count;

	int idx = 0;
	int* p_idx = &idx;

	bool satisfy = false;
	bool* p_satisfy = &satisfy;

	// Traverse: Check if <station_id> is valid
	Station->traverse(
		[](TStation& Station, void*& p_station_id, void*& p_satisfy) -> bool {
			if (Station.id == *(int*)p_station_id) {
				*(bool*)p_satisfy = true;
				return true;
			}
			return false;
		}
	, (void*&)p_station_id, (void*&)p_satisfy);

	if (!satisfy) return -1;

	// Traverse: Check if <line_id> contains no given <station_id> and find the index 
	StationLine->traverse(
		[](TStationLine& StationLine, void*& p_station_id, void*& p_line_id, void*& p_count, void*& p_idx) -> bool {
			if (StationLine.line_id == *(int*)p_line_id) {
				if (StationLine.station_id == *(int*)p_station_id) {
					*(int*)p_idx = -1;
					return true;
				}
				(*(int*)p_count)--;
			}
			if (*(int*)p_count >= 0) (*(int*)p_idx)++;
			return false;
		}
	, (void*&)p_station_id, (void*&)p_line_id, (void*&)p_count, (void*&)p_idx);

	/*	If the lines have a given <station_id>, <count> would be -1.
	 *	If the lines don't have given <station_id>, but the <p_i> is not satisfied, <count> would be different than 0.
	 *	Else, <count> would be 0.
	 */	
	if (idx == -1 || count > 0) return -1;
	
	TStationLine StationLine;
	StationLine.station_id = station_id;
	StationLine.line_id = line_id;

	return this->StationLine->insert(idx, StationLine);
}

int TDataset::remove_Station_StationLine_StationID_LineID(int& station_id, int& line_id) {
	if (station_id == -1 || line_id == -1) return -1;

	// Create pointer
	int* p_station_id = &station_id;
	int* p_line_id = &line_id;
	int idx = 0;
	int* p_idx = &idx;
	
	// Traverse: Find the StationLine
	StationLine->traverse(
		[](TStationLine& StationLine, void*& p_station_id, void*& p_line_id, void*& p_p_i) -> bool {
			if (StationLine.station_id == *(int*)p_station_id && StationLine.line_id == *(int*)p_line_id)
				return true;
			(*(int*)p_p_i)++;
			return false;
		}
	, (void*&)p_station_id, (void*&)p_line_id, (void*&)p_idx);

	// Remove the StationLine
	if (StationLine->remove(idx) == -1) return -1;

	return 0;
}

/* Extended functions */

int TDataset::remove_Station_StationLine_StationID(int& station_id) {
	if (station_id == -1) return -1;

	// Create pointer
	int* p_station_id = &station_id;
	int i = 0;
	int* p_i = &i;

	// Traverse: StationLine
	StationLine->traverse(
		[](TStationLine& StationLine, void*& p_station_id, void*& p_i) -> bool {
			if (StationLine.station_id == *(int*)p_station_id)
				return true;
			(*(int*)p_i)++;
			return false;
		}
	, (void*&)p_station_id, (void*&)p_i);

	if (StationLine->remove(i) == -1) return -1;

	return 0;
}

int TDataset::remove_StationLS_Track_StationGeometry_CityID(string& point, int& city_id) {
	if (point == "\0" || city_id == -1) return -1;

	// Create pointer
	string* p_point = &point;
	int* p_city_id = &city_id;
	bool success = false;
	bool* p_success = &success;

	// Traverse: Track
	Track->traverse(
		[](TTrack& Track, void*& p_point, void*& p_city_id, void*& p_success) -> bool {
			if (Track.city_id == *(int*)p_city_id) {
				string point = *(string*)p_point;
				int pos = Track.geometry.find(point);
				if (pos != -1) {
					Track.geometry.erase(pos, point.length() + (pos + point.length() == Track.geometry.length() ? 0 : 1));
					*(bool*)p_success = true;
					return true;
				}
			}
			return false;
		}
	, (void*&)p_point, (void*&)p_city_id, (void*&)p_success);
	
	return success;
}

void LoadData(void*& pData) {
	TDataset* Dataset = new TDataset;
	fstream file;
	string input;
	stringstream ss;

	// cities.csv
	file.open("cities.csv");
	getline(file, input);
	while (getline(file, input)) {
		
		if (input == "") break;

		TCity City;
		createData_City(input, City);
		Dataset->insertData_City(City);
	}
	file.close();

	// lines.csv
	file.open("lines.csv");
	getline(file, input);
	while (getline(file, input)) {
		
		if (input == "") break;

		TLine Line;
		createData_Line(input, Line);
		Dataset->insertData_Line(Line);
	}
	file.close();

	// station_lines.csv
	file.open("station_lines.csv");
	
	getline(file, input);
	while (getline(file, input)) {
		
		if (input == "") break;

		TStationLine StationLine;
		createData_StationLine(input, StationLine);
		Dataset->insertData_StationLine(StationLine);
	}
	file.close();

	// stations.csv
	file.open("stations.csv");
	getline(file, input);
	while (getline(file, input)) {
		
		if (input == "") break;

		TStation Station;
		createData_Station(input, Station);	
		Dataset->insertData_Station(Station);
	}
	file.close();

	// systems.csv
	/*
	file.open("systems.csv");
	getline(file, input);
	while (getline(file, input)) {
		
		if (input == "") break;

		TSystem System;
		createData_System(input, System);
		Dataset->insertData_System(System);
	}
	file.close();
	*/

	// tracks.csv
	file.open("tracks.csv");
	getline(file, input);
	while (getline(file, input)) {

		if (input == "") break;

		TTrack Track;
		createData_Track(input, Track);
		Dataset->insertData_Track(Track);
	}
	file.close();

	// track_lines.csv
	file.open("track_lines.csv");
	getline(file, input);
	while (getline(file, input)) {

		if (input == "") break;

		TTrackLine TrackLine;
		createData_TrackLine(input, TrackLine);
		Dataset->insertData_TrackLine(TrackLine);
	}
	file.close();
	
	// Set database's pointer
	pData = Dataset;
	Dataset = nullptr;
}

void ReleaseData(void*& pData) {
	TDataset* Dataset;
	Dataset = (TDataset *)pData;
	Dataset->~TDataset();
	Dataset = nullptr;
	system("pause");
}

/* Functions that each of other loads its own database; */

void createData_City(string& line, TCity& City) {
	stringstream ss;
	ss.str(line);
	string cell;
	//cout << "lineStream.str() = " << ss.str() << std::endl;

	//id, name, coords, start_year, url_name, country, country_state
	getline(ss, cell, ',');
	if (cell != "\0") City.id = atoi(cell.c_str());
	getline(ss, cell, ',');
	City.name = cell;
	getline(ss, cell, ',');
	City.coords = cell;
	getline(ss, cell, ',');
	if (cell != "\0") City.start_year = atoi(cell.c_str());
	getline(ss, cell, ',');
	City.url_name = cell;
	getline(ss, cell, ',');
	City.country = cell;
	getline(ss, cell);
	City.country_state = cell;
}

void createData_Line(string& line, TLine& Line) {
	stringstream ss;
	ss.str(line);
	string cell;
	//cout << "lineStream.str() = " << ss.str() << std::endl;

	//id, city_id, name, url_name, color, system_id, transport_mode_id
	getline(ss, cell, ',');
	if (cell != "\0") Line.id = atoi(cell.c_str());
	getline(ss, cell, ',');
	if (cell != "\0") Line.city_id = atoi(cell.c_str());
	getline(ss, cell, ',');
	Line.name = cell;
	getline(ss, cell, ',');
	Line.url_name = cell;
	getline(ss, cell, ',');
	Line.color = cell;
	getline(ss, cell, ',');
	if (cell != "\0") Line.system_id = atoi(cell.c_str());
	getline(ss, cell, ',');
	if (cell != "\0") Line.transport_mode_id = atoi(cell.c_str());
};

void createData_StationLine(string& line, TStationLine& StationLine) {
	stringstream ss;
	ss.str(line);
	string cell;
	//cout << "lineStream.str() = " << ss.str() << std::endl;

	//id, station_id, line_id, city_id, created_at, updated_at
	getline(ss, cell, ',');
	if (cell != "\0") StationLine.id = atoi(cell.c_str());
	getline(ss, cell, ',');
	if (cell != "\0") StationLine.station_id = atoi(cell.c_str());
	getline(ss, cell, ',');
	if (cell != "\0") StationLine.line_id = atoi(cell.c_str());
	getline(ss, cell, ',');
	if (cell != "\0") StationLine.city_id = atoi(cell.c_str());
	getline(ss, cell, ',');
	StationLine.created_at = cell;
	getline(ss, cell, ',');
	StationLine.updated_at = cell;
};

void createData_Station(string& line, TStation& Station) {
	stringstream ss;
	ss.str(line);
	string cell;
	//cout << "lineStream.str() = " << ss.str() << std::endl;

	//id, name, geometry, buildstart, opening, closure, city_id
	getline(ss, cell, ',');
	if (cell != "\0") Station.id = atoi(cell.c_str());
	getline(ss, cell, ',');
	Station.name = cell;
	getline(ss, cell, ')');
	Station.geometry = cell.substr(6, cell.length() - 6);
	getline(ss, cell, ',');
	getline(ss, cell, ',');
	if (cell != "\0") Station.buildstart = atoi(cell.c_str());
	getline(ss, cell, ',');
	if (cell != "\0") Station.opening = atoi(cell.c_str());
	getline(ss, cell, ',');
	if (cell != "\0") Station.closure = atoi(cell.c_str());
	getline(ss, cell, ',');
	if (cell != "\0") Station.city_id = atoi(cell.c_str());
};

void createData_System(string& line, TSystem& System) {
	stringstream ss;
	ss.str(line);
	string cell;
	//cout << "lineStream.str() = " << ss.str() << std::endl;

	//id, city_id, name
	getline(ss, cell, ',');
	if (cell != "\0") System.id = atoi(cell.c_str());
	getline(ss, cell, ',');
	if (cell != "\0") System.city_id = atoi(cell.c_str());
	getline(ss, cell, ',');
	System.name = cell;
};

void createData_Track(string& line, TTrack& Track) {
	stringstream ss;
	ss.str(line);
	string cell;
	//cout << "lineStream.str() = " << ss.str() << std::endl;

	//id, geometry, buildstart, opening, closure, length, city_id
	getline(ss, cell, ',');
	if (cell != "\0") Track.id = atoi(cell.c_str());
	getline(ss, cell, ')');
	Track.geometry = cell.substr(12, cell.length() - 12);
	getline(ss, cell, ',');
	getline(ss, cell, ',');
	if (cell != "\0") Track.buildstart = atoi(cell.c_str());
	getline(ss, cell, ',');
	if (cell != "\0") Track.opening = atoi(cell.c_str());
	getline(ss, cell, ',');
	if (cell != "\0") Track.closure = atoi(cell.c_str());
	getline(ss, cell, ',');
	if (cell != "\0") Track.length = atoi(cell.c_str());
	getline(ss, cell, ',');
	if (cell != "\0") Track.city_id = atoi(cell.c_str());
};

void createData_TrackLine(string& line, TTrackLine& TrackLine) {
	stringstream ss;
	ss.str(line);
	string cell;
	//cout << "lineStream.str() = " << ss.str() << std::endl;

	//id, section_id, line_id, created_at, updated_at, city_id
	getline(ss, cell, ',');
	if (cell != "\0") TrackLine.id = atoi(cell.c_str());
	getline(ss, cell, ',');
	if (cell != "\0") TrackLine.section_id = atoi(cell.c_str());
	getline(ss, cell, ',');
	if (cell != "\0") TrackLine.line_id = atoi(cell.c_str());
	getline(ss, cell, ',');
	TrackLine.created_at = cell;
	getline(ss, cell, ',');
	TrackLine.updated_at = cell;
	getline(ss, cell, ',');
	if (cell != "\0") TrackLine.city_id = atoi(cell.c_str());
};