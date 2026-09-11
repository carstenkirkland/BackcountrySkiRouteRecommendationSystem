// Carsten Kirkland
// Final Project CSCI 200 - Backcountry Ski Planner
// Rest of info can be found in final.txt



#include "route.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// function prototypes
void load_routes( vector<SkiRoute>& routes );
void display_menu();
void display_all_routes( const vector<SkiRoute>& routes );
void filter_by_difficulty( const vector<SkiRoute>& routes );
void filter_by_avalanche_risk( const vector<SkiRoute>& routes );
void recommend_safe_routes( const vector<SkiRoute>& routes );
void save_recommended_routes( const vector<SkiRoute>& routes );

int main() {
	vector<SkiRoute> routes;
	int userChoice = 0;

// load data from file
	load_routes( routes );

	if( routes.size() == 0 ) {
		cout << "No routes were loaded. Please check routes.txt." << endl;
		return 1;
	}

// main menu loop
	while( userChoice != 6 ) {
		display_menu();
		cin >> userChoice;

		if( userChoice == 1 ) {
			display_all_routes( routes );
		} else if( userChoice == 2 ) {
			filter_by_difficulty( routes );
		} else if( userChoice == 3 ) {
			filter_by_avalanche_risk( routes );
		} else if( userChoice == 4 ) {
			recommend_safe_routes( routes );
		} else if( userChoice == 5 ) {
			save_recommended_routes( routes );
		} else if( userChoice == 6 ) {
			cout << "Goodbye!" << endl;
		} else {
			cout << "Invalid choice. Please try again." << endl;
		}
	}

	return 0;
}

// reads route data from file and stores in vector
void load_routes( vector<SkiRoute>& routes ) {
	ifstream inputFile;
	string routeName;
	double distanceMiles;
	int elevationGainFeet;
	string difficulty;
	int snowDepth;
	int avalancheRisk;
	string weather;

	inputFile.open( "routes.txt" );

	if( !inputFile ) {
		cout << "Could not open routes.txt." << endl;
		return;
	}

	while( inputFile >> routeName >> distanceMiles >> elevationGainFeet
					 >> difficulty >> snowDepth >> avalancheRisk >> weather ) {
		SkiRoute newRoute( routeName, distanceMiles, elevationGainFeet,
						   difficulty, snowDepth, avalancheRisk, weather );

		routes.push_back( newRoute );
	}

	inputFile.close();
}

// displays menu options
void display_menu() {
	cout << endl;
	cout << "===== Backcountry Ski Planner =====" << endl;
	cout << "1. Display all ski routes" << endl;
	cout << "2. Filter routes by difficulty" << endl;
	cout << "3. Filter routes by avalanche risk" << endl;
	cout << "4. Recommend safe routes" << endl;
	cout << "5. Save recommended routes to file" << endl;
	cout << "6. Exit" << endl;
	cout << "Enter choice: ";
}

// prints all routes
void display_all_routes( const vector<SkiRoute>& routes ) {
	cout << endl;
	cout << "===== All Ski Routes =====" << endl;

	for( int i = 0; i < static_cast<int>( routes.size() ); i++ ) {
		cout << endl;
		routes.at( i ).print_route_info();
	}
}

// filters routes by difficulty
void filter_by_difficulty( const vector<SkiRoute>& routes ) {
	string wantedDifficulty;
	bool foundRoute = false;

	cout << "Enter difficulty to search for (Easy, Moderate, Hard): ";
	cin >> wantedDifficulty;

	cout << endl;
	cout << "===== Routes With Difficulty: " << wantedDifficulty << " =====" << endl;

	for( int i = 0; i < static_cast<int>( routes.size() ); i++ ) {
		if( routes.at( i ).get_difficulty() == wantedDifficulty ) {
			cout << endl;
			routes.at( i ).print_route_info();
			foundRoute = true;
		}
	}

	if( !foundRoute ) {
		cout << "No routes matched that difficulty." << endl;
	}
}

// filters routes by avalanche risk
void filter_by_avalanche_risk( const vector<SkiRoute>& routes ) {
	int maxRisk;
	bool foundRoute = false;

	cout << "Enter maximum avalanche risk allowed (1-5): ";
	cin >> maxRisk;

	cout << endl;
	cout << "===== Routes With Avalanche Risk " << maxRisk << " Or Lower =====" << endl;

	for( int i = 0; i < static_cast<int>( routes.size() ); i++ ) {
		if( routes.at( i ).get_avalanche_risk() <= maxRisk ) {
			cout << endl;
			routes.at( i ).print_route_info();
			foundRoute = true;
		}
	}

	if( !foundRoute ) {
		cout << "No routes matched that avalanche risk." << endl;
	}
}

// recommends routes based on safety score
void recommend_safe_routes( const vector<SkiRoute>& routes ) {
	double minSafetyScore;
	bool foundRoute = false;

	cout << "Enter minimum safety score wanted between 0.0 and 1.0: ";
	cin >> minSafetyScore;

	cout << endl;
	cout << "===== Recommended Safe Routes =====" << endl;

	for( int i = 0; i < static_cast<int>( routes.size() ); i++ ) {
		if( routes.at( i ).calculate_safety_score() >= minSafetyScore ) {
			cout << endl;
			routes.at( i ).print_route_info();
			foundRoute = true;
		}
	}

	if( !foundRoute ) {
		cout << "No routes met that safety score." << endl;
	}
}

// saves recommended routes to file
void save_recommended_routes( const vector<SkiRoute>& routes ) {
	ofstream outputFile;
	double minSafetyScore;
	bool foundRoute = false;

	cout << "Enter minimum safety score to save between 0.0 and 1.0: ";
	cin >> minSafetyScore;

	outputFile.open( "recommended_routes.txt" );

	if( !outputFile ) {
		cout << "Could not open recommended_routes.txt." << endl;
		return;
	}

	outputFile << fixed << setprecision( 2 );
	outputFile << "Recommended Backcountry Ski Routes" << endl;
	outputFile << "Minimum Safety Score: " << minSafetyScore << endl;
	outputFile << endl;

	for( int i = 0; i < static_cast<int>( routes.size() ); i++ ) {
		if( routes.at( i ).calculate_safety_score() >= minSafetyScore ) {
			outputFile << "Route: " << routes.at( i ).get_route_name() << endl;
			outputFile << "Distance: " << routes.at( i ).get_distance_miles() << " miles" << endl;
			outputFile << "Elevation Gain: " << routes.at( i ).get_elevation_gain_feet() << " feet" << endl;
			outputFile << "Difficulty: " << routes.at( i ).get_difficulty() << endl;
			outputFile << "Snow Depth: " << routes.at( i ).get_snow_depth() << " inches" << endl;
			outputFile << "Avalanche Risk: " << routes.at( i ).get_avalanche_risk() << endl;
			outputFile << "Weather: " << routes.at( i ).get_weather() << endl;
			outputFile << "Estimated Tour Time: " << routes.at( i ).calculate_tour_time() << " hours" << endl;
			outputFile << "Safety Score: " << routes.at( i ).calculate_safety_score() << endl;
			outputFile << endl;

			foundRoute = true;
		}
	}

	if( !foundRoute ) {
		outputFile << "No routes met the selected safety score." << endl;
	}

	outputFile.close();

	cout << "Recommended routes saved to recommended_routes.txt." << endl;
}