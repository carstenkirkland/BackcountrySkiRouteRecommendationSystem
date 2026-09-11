#include "route.h"

#include <iomanip>
#include <iostream>
using namespace std;

// default constructor initializes all values to safe defaults
SkiRoute::SkiRoute() {
	_routeName = "";
	_distanceMiles = 0.0;
	_elevationGainFeet = 0;
	_difficulty = "";
	_snowDepth = 0;
	_avalancheRisk = 0;
	_weather = "";
}

// parameterized constructor initializes all route data
SkiRoute::SkiRoute( string routeName, double distanceMiles, int elevationGainFeet,
					string difficulty, int snowDepth, int avalancheRisk, string weather ) {
	_routeName = routeName;
	_distanceMiles = distanceMiles;
	_elevationGainFeet = elevationGainFeet;
	_difficulty = difficulty;
	_snowDepth = snowDepth;
	_avalancheRisk = avalancheRisk;
	_weather = weather;
}

// getters return individual data members
string SkiRoute::get_route_name() const {
	return _routeName;
}

double SkiRoute::get_distance_miles() const {
	return _distanceMiles;
}

int SkiRoute::get_elevation_gain_feet() const {
	return _elevationGainFeet;
}

string SkiRoute::get_difficulty() const {
	return _difficulty;
}

int SkiRoute::get_snow_depth() const {
	return _snowDepth;
}

int SkiRoute::get_avalanche_risk() const {
	return _avalancheRisk;
}

string SkiRoute::get_weather() const {
	return _weather;
}

// estimates tour time based on distance and elevation gain
double SkiRoute::calculate_tour_time() const {
	const double HOURS_PER_MILE = 0.5;
	const double HOURS_PER_1000_FEET = 1.0;

	double timeHours = ( _distanceMiles * HOURS_PER_MILE ) +
					   ( ( _elevationGainFeet / 1000.0 ) * HOURS_PER_1000_FEET );

	return timeHours;
}

// calculates a safety score between 0.0 (dangerous) and 1.0 (safe)
double SkiRoute::calculate_safety_score() const {
	double score = 1.0;

// reduce score based on avalanche risk
	score -= ( _avalancheRisk - 1 ) * 0.20;

// adjust score based on snow depth
	if( _snowDepth < 30 ) {
		score -= 0.20;
	} else if( _snowDepth < 45 ) {
		score -= 0.10;
	}

// adjust score based on weather conditions
	if( _weather == "Windy" ) {
		score -= 0.20;
	} else if( _weather == "Snow" ) {
		score -= 0.15;
	} else if( _weather == "Cloudy" ) {
		score -= 0.05;
	}

// adjust score based on difficulty
	if( _difficulty == "Hard" ) {
		score -= 0.10;
	} else if( _difficulty == "Moderate" ) {
		score -= 0.05;
	}

// clamp score between 0.0 and 1.0
	if( score < 0.0 ) {
		score = 0.0;
	}

	if( score > 1.0 ) {
		score = 1.0;
	}

	return score;
}

// prints all route information to the console
void SkiRoute::print_route_info() const {
	cout << fixed << setprecision( 2 );
	cout << "Route: " << _routeName << endl;
	cout << "Distance: " << _distanceMiles << " miles" << endl;
	cout << "Elevation Gain: " << _elevationGainFeet << " feet" << endl;
	cout << "Difficulty: " << _difficulty << endl;
	cout << "Snow Depth: " << _snowDepth << " inches" << endl;
	cout << "Avalanche Risk: " << _avalancheRisk << endl;
	cout << "Weather: " << _weather << endl;
	cout << "Estimated Tour Time: " << calculate_tour_time() << " hours" << endl;
	cout << "Safety Score: " << calculate_safety_score() << endl;
}