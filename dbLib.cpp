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

int TDataset::find_CityID_City(string& city_name) {

	remove_DQMarks(city_name);
	
	// Create pointer
	string* p_city_name = &city_name;
	int city_id = -1;
	int* p_city_id = &city_id;

	// Traverse: City
	// * Find <city_id> with the given <city_name>
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

int TDataset::count_numLine_Line(int& city_id) {
	if (city_id == -1) return -1;

	// Create pointer 
	int* p_city_id = &city_id;
	int count = 0;
	int* p_count = &count;

	// Traverse: Line
	// * Count the number of lines with the given <city_id>
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

int* TDataset::list_StationID_Station(int& city_id, int& N) {

	N = 0;

	// Create pointer 
	int* p_city_id = &city_id;
	int* p_count = &N;
	L1List<int>* arr_list = new L1List<int>;

	if (city_id != -1) {
		// Traverse: Station
		// * List all <station_id> with the given <city_id>
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
		// Turn the linked list to int array
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

int* TDataset::list_LineID_Line(int& city_id, int& N) {

	N = 0;

	// Create pointer 
	int* p_city_id = &city_id;
	int* p_count = &N;
	L1List<int>* arr_list = new L1List<int>;

	if (city_id != -1) {
		// Traverse: Line
		// * List all <line_id> with the give <city_id>
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
		// Turn the linked list to int array
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

int* TDataset::list_StationID_StationLine(int& line_id, int& N) {

	N = 0;

	// Create pointer 
	int* p_line_id = &line_id;
	int* p_count = &N;
	L1List<int>* arr_list = new L1List<int>;

	if (line_id != -1) {
		// Traverse: StationLine
		// * List all <station_id> with the given <line_id>
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
		// Turn the linked list to int array
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

int TDataset::find_StationID_Station(string& station_name) {

	remove_DQMarks(station_name);

	// Create pointer 
	string* p_station_name = &station_name;
	int station_id = -1;
	int* p_station_id = &station_id;

	// Traverse: Station
	// * Find <station_id> with the given <station_name>
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

string TDataset::find_StationGeometry_Station(int& station_id) {
	if (station_id == -1) return "\0";

	// Create pointer 
	int* p_station_id = &station_id;
	string station_geometry;
	string* p_station_geometry = &station_geometry;

	// Traverse: Station
	// * Find <geometry> of the station with the given <station_id>
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

int TDataset::find_StationIDX_Track(string& point, int track_id) {
	if (point == "\0") return -1;
	
	// Create pointer
	string* p_point = &point;
	int* p_track_id = &track_id;
	int station_idx = -1;
	int* p_station_idx = &station_idx;

	// Traverse: Track
	// * Find the position of the station in the track with the given <track_id> and <station_id>
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

	// Examine the <csv_description>
	// * If the description has the same format as in "stations.csv" except the <station_id> and <city_id>
	// * Count the number of rows in <csv_description>
	int num_row = 0;
	stringstream ss;
	ss.str(csv_description);
	while (!ss.eof()) {
		string cell;
		csv_row_reader(ss, cell);
		num_row++;
	}

	if (num_row == 5) {
		csv_description.insert(csv_description.begin(), ',');
		csv_description.insert(csv_description.end(), ',');
	}
	
	int id_max = Station->get_IDmax();
	
	// Update id_max
	if (id_max == -1) {

		int* p_id_max = &id_max; 
		
		// Traverse: Station
		// * Update <id_max>
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
	Station.city_id = '\0';

	// Insert new station
	insertData_Station(Station);

	return id_max;
}

int TDataset::remove_Station_Dataset(int& station_id) {
	if (station_id == -1) return -1;

	// Create pointer
	int* p_station_id = &station_id;
	string point;
	string* p_point = &point;
	int city_id = -1;
	int* p_city_id = &city_id;
	int idx = 0;
	int* p_idx = &idx;

	// Traverse: Station
	// * Find the Station and get <station_id> and <geometry> of this
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
	remove_Station_StationLine(station_id);
	remove_StationLS_Track(point, city_id);

	return 0;
}

int TDataset::update_Station_Dataset(int& station_id, string& csv_description) {
	if (station_id == -1) return -1;

	// Create pointer
	int* p_station_id = &station_id;
	string* csv = &csv_description;
	string point;
	string* p_point = &point;
	bool success = false;
	bool* p_success = &success;
	
	// Traverse: Station
	// * Update the information of the Station
	this->Station->traverse(
		[](TStation& Station, void*& p_station_id, void*& csv, void*& p_point, void*& p_success) -> bool {
			if (Station.id == *(int*)p_station_id) {
				*(string*)p_point = Station.geometry;
				createData_Station(*(string*)csv, Station);
				*(bool*)p_success = true;
				return true;
			}
			return false;
		}
	, (void*&)p_station_id, (void*&)csv, (void*&)p_point, (void*&)p_success);

	if(!success) return -1;

	TStation Station;
	createData_Station(csv_description, Station);
	
	// Update any records related to the station
	update_Station_StationLine(station_id, Station.id);
	update_StationLS_Track(point, Station.city_id, Station.geometry);

	return 0;
}

int TDataset::insert_Station_StationLine(int& station_id, int& line_id, int& p_i) {
	if (station_id == -1 || line_id == -1) return -1;

	// Create pointer
	int* p_station_id = &station_id;
	int* p_line_id = &line_id;
	
	// * <p_i> is now represented by <p_idx>,
	int idx = p_i;
	int* p_idx = &idx;

	// * <pos> is for the StationLine's insert function
	int pos = 0;
	int* p_pos = &pos;

	bool satisfy = false;
	bool* p_satisfy = &satisfy;

	// Traverse: Station
	// * Check if <station_id> is valid
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

	// Traverse: StationLine
	// * Check if <line_id> contains none of station that has the given <station_id>, then return the <index> (not p_i)
	StationLine->traverse(
		[](TStationLine& StationLine, void*& p_station_id, void*& p_line_id, void*& p_idx, void*& p_pos) -> bool {
			if (StationLine.line_id == *(int*)p_line_id) {
				if (StationLine.station_id == *(int*)p_station_id) {
					*(int*)p_pos = -1;
					return true;
				}
				(*(int*)p_idx)--;
			}
			if (*(int*)p_idx >= 0) (*(int*)p_pos)++; // Cannot use "Else" case: to find the <station_id>
			return false;
		}
	, (void*&)p_station_id, (void*&)p_line_id, (void*&)p_idx, (void*&)p_pos);

	// * If lines have the given <station_id>, <idx> would be -1.
	// * If lines don't have given <station_id>, but <p_i> is not satisfied, <idx> would be larger than 0.
	// * Else <idx> would be 0.
	if (pos == -1 || idx > 0) return -1;
	
	TStationLine StationLine;
	StationLine.station_id = station_id;
	StationLine.line_id = line_id;

	return this->StationLine->insert(pos, StationLine);
}

int TDataset::remove_Station_StationLine(int& station_id, int& line_id) {
	if (station_id == -1 || line_id == -1) return -1;

	// Create pointer
	int* p_station_id = &station_id;
	int* p_line_id = &line_id;
	int idx = 0;
	int* p_idx = &idx;
	
	// Traverse: StationLine
	// * Find the given <station_id> in <line_id>, then return the index
	StationLine->traverse(
		[](TStationLine& StationLine, void*& p_station_id, void*& p_line_id, void*& p_p_i) -> bool {
			if (StationLine.station_id == *(int*)p_station_id && StationLine.line_id == *(int*)p_line_id)
				return true;
			(*(int*)p_p_i)++;
			return false;
		}
	, (void*&)p_station_id, (void*&)p_line_id, (void*&)p_idx);

	// Remove the station line
	if (StationLine->remove(idx) == -1) return -1;

	return 0;
}




/* Child function */

/* Child function of the Remove Station function */

void TDataset::remove_Station_StationLine(int& station_id) {
	if (station_id == -1) return;

	// Create pointer
	int* p_station_id = &station_id;
	int i = 0;
	int* p_i = &i;

	// Traverse: StationLine
	// Find the station line with the given <station_id> and return the index
	StationLine->traverse(
		[](TStationLine& StationLine, void*& p_station_id, void*& p_i) -> bool {
			if (StationLine.station_id == *(int*)p_station_id)
				return true;
			(*(int*)p_i)++;
			return false;
		}
	, (void*&)p_station_id, (void*&)p_i);

	// Remove the station line
	StationLine->remove(i);

	return;
}

void TDataset::remove_StationLS_Track(string& point, int& city_id) {
	if (point == "\0" || city_id == -1) return;

	// Create pointer
	string* p_point = &point;
	int* p_city_id = &city_id;

	// Traverse: Track
	// Find the track that contains station's geometry, then remove it
	Track->traverse(
		[](TTrack& Track, void*& p_point, void*& p_city_id) -> bool {
			if (Track.city_id == *(int*)p_city_id) {
				string point = *(string*)p_point;
				int pos = Track.geometry.find(point);
				if (pos != -1) {
					int pos_begin = pos + (pos != 0 ? -1 : 0);
					int erase_length = point.length() + (pos + point.length() == Track.geometry.length() ? 0 : 1);

					// Remove Station's point in Track's geometry
					Track.geometry.erase(pos_begin, erase_length);

					return true;
				}
			}
			return false;
		}
	, (void*&)p_point, (void*&)p_city_id);

	return;
}

/* Child function of the Update Station function */

void TDataset::update_Station_StationLine(int& station_id, int& station_id_new) {
	if (station_id == -1) return;

	// Create pointer
	int* p_station_id = &station_id;
	int* p_station_id_new = &station_id_new;

	// Traverse: StationLine
	// Find the station line with the given <station_id> and update if with new "Station" entity
	StationLine->traverse(
		[](TStationLine& StationLine, void*& p_station_id, void*& p_station_id_new) -> bool {
			if (StationLine.station_id == *(int*)p_station_id) {
				StationLine.station_id = *(int*)p_station_id_new;
				return true;
			}
			return false;
		}
	, (void*&)p_station_id, (void*&) p_station_id_new);

	return;
};

void TDataset::update_StationLS_Track(string& point, int& city_id, string& point_new) {
	if (point == "\0" || city_id == -1) return;

	// Create pointer
	string* p_point = &point;
	int* p_city_id = &city_id;
	string* p_point_new = &point_new;

	// Traverse: Track
	// Find the track that contains old station's geometry and change it
	Track->traverse(
		[](TTrack& Track, void*& p_point, void*& p_city_id, void*& p_point_new) -> bool {
			if (Track.city_id == *(int*)p_city_id) {
				string point = *(string*)p_point;
				int pos = Track.geometry.find(point);
				if (pos != -1) {
					
					string point = *(string*)p_point;
					bool add_comma = false;
					// Replace old geometry with the new one
					string geometry_new;

					string cell;
					stringstream ss;
					ss.str(Track.geometry);
					while (getline(ss, cell, ',')) {
						if (add_comma) geometry_new += ',';
						if (cell == point) {
							geometry_new += *(string*)p_point_new;
						}
						else {
							geometry_new += cell;
						}

						add_comma = true;
					}

					Track.geometry = geometry_new;
					return true;
				}
			}
			return false;
		}
	, (void*&)p_point, (void*&)p_city_id, (void*&) p_point_new);

	return;
};

/* Added function */

int TDataset::ASLP(int &choose) {
	
	// Create pointer
	void* p_Station = this->Station;
	int counter = 0;
	int* p_counter = &counter;
	
	cout << Track->getSize() << endl;
	switch (choose) {
		case 1: {
			
			int counter = 0;
			int* p_counter = &counter;

			// Traverse: Track
			Track->traverse(
				[](TTrack& Track, void*& p_Station, void*& p_counter) -> bool {

					int* p_city_id = &Track.city_id;
					string* p_geometry = &Track.geometry;
					bool success = false;
					bool* p_success = &success;

					string cell;
					stringstream ss;
					ss.str(*(string*)p_geometry);

					// Create pointer
					string* p_point = &cell;
					int idx = 0;
					int* p_idx = &idx;

					while (getline(ss, cell, ',')) {
						// Traverse: Station
						// Check if the station's geometry is valid or not, then print out the <station_id> and <idx>
						((L1List<TStation>*)p_Station)->traverse(
							[](TStation& Station, void*& p_city_id, void*& p_point, void*& p_idx, void*& p_success) -> bool {
								if (Station.city_id == *(int*)p_city_id) {
									if (*(string*)p_point == Station.geometry) {
										cout << setw(6) << left << Station.id << setw(4) << left << *(int*)p_idx << "|";
										*(bool*)p_success = true;
										return true;
									}
								}
								return false;
							}
						, (void*&)p_city_id, (void*&)p_point, (void*&)p_idx, (void*&)p_success);
						idx++;
					}

					(*(int*)p_counter)++;

					// Print the <track_id> and if the opeation is success
					if (success) cout << endl << "==========" << setw(5) << left << Track.id << "==========" << setw(5) << left << *(int*)p_counter << "==========" << idx << endl;
					return false;
				}
			, (void*&)p_Station, (void*&)p_counter);

			break;
		}
		case 2: {

			// Traverse: Track
			Track->traverse(
				[](TTrack& Track, void*& p_Station, void*& p_counter) -> bool {

					int* p_city_id = &Track.city_id;
					string* p_geometry = &Track.geometry;
					bool success = false;
					bool* p_success = &success;

					// Traverse: Station
					// Check if the station's geometry is valid or not, then print out the <station_id> and <idx>
					((L1List<TStation>*)p_Station)->traverse(
						[](TStation& Station, void*& p_city_id, void*& p_geometry, void*& p_success) -> bool {
							if (Station.city_id == *(int*)p_city_id) {

								string cell;
								stringstream ss;
								ss.str(*(string*)p_geometry);

								int idx = 0;
								int idx_last = -1;

								while (getline(ss, cell, ',')) {
									if (cell == Station.geometry) {
										cout << setw(6) << left << Station.id << setw(4) << left << idx << "|";
										idx_last = idx;
										*(bool*)p_success = true;
										break;
									}
									idx++;
								}

								if (idx == ++idx_last) cout << "*";
							}
							return false;
						}
					, (void*&)p_city_id, (void*&)p_geometry, (void*&)p_success);

					(*(int*)p_counter)++;

					// Print the <track_id> and if the opeation is success
					if (success) cout << endl << "==========" << setw(5) << left << Track.id << "==========" << setw(5) << left << *(int*)p_counter << endl;
					return false;
				}
			, (void*&)p_Station, (void*&)p_counter);

			break;
		}
		default: 
			return -1;
	}

	return 0;
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
	/*
	file.open("track_lines.csv");
	getline(file, input);
	while (getline(file, input)) {

		if (input == "") break;

		TTrackLine TrackLine;
		createData_TrackLine(input, TrackLine);
		Dataset->insertData_TrackLine(TrackLine);
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
	getline(ss, cell, ',');
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
	csv_row_reader(ss, cell);	// double quotation marks
	remove_DQMarks(cell);		// Remove double-quote marks
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
	csv_row_reader(ss, cell);	// double quotation marks
	remove_DQMarks(cell);		// Remove double-quote marks
	Station.name = cell;
	csv_row_reader(ss, cell);	// double quotation marks
	remove_DQMarks(cell);		// Remove quotation marks
	Station.geometry = cell.substr(6, cell.length() - 7);	// Specify for station geometry
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
	csv_row_reader(ss, cell);		// double quotation marks
	remove_DQMarks(cell);			// Remove double-quote marks
	Track.geometry = cell.substr(11, cell.length() - 12);	// Specify for track geometry
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

void remove_DQMarks(string& s) {
	int sl = s.length();
	if (sl == 0 || s[0] != '"') return;
	s.erase(0, 1);
	s.erase(sl - 2, 1);
	return;
};

void csv_row_reader(stringstream& ss, string& cell) {
	string row;
	
	// * In case that field may be quoted: we'll deal with the following things:
	// * 1. The number of quotation marks
	// * 2. The started index of the cell string which will be examined
	int num_QMark = 0;
	int idx; 
	int merge = 0;

	while(getline(ss, cell, ',')) {
		
		merge++;
		int cl = cell.length();
		idx = 0;

		// * a. 
		// Adjacent fields are only separated by a single comma
		if (num_QMark == 0 && (cl == 0 || cell[0] != '"')) {
			return;
		}

		// * b. 
		// Any field may be quoted, which is enclosed within double-quote characters
		// Fields with embedded commas or double-quote characters must be quoted
		while (idx < cl) {
			// Count the number of quotation mark
			if (cell[idx] == '"') num_QMark++;
			idx++;
		}

		if (merge > 1) row += ',';
		row += cell;

		// The string is only valid if the number of quotation mark is even
		if (num_QMark % 2 == 0) {
			cell = row; // Copy the result string to cell
			return;
		}
	}
};