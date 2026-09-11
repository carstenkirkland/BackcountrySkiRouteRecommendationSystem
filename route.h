#ifndef ROUTE_H
#define ROUTE_H

#include <string>
using namespace std;

class SkiRoute {
public:
	SkiRoute();
	SkiRoute( string routeName, double distanceMiles, int elevationGainFeet,
			  string difficulty, int snowDepth, int avalancheRisk, string weather );

	string get_route_name() const;
	double get_distance_miles() const;
	int get_elevation_gain_feet() const;
	string get_difficulty() const;
	int get_snow_depth() const;
	int get_avalanche_risk() const;
	string get_weather() const;

	double calculate_tour_time() const;
	double calculate_safety_score() const;
	void print_route_info() const;

private:
	string _routeName;
	double _distanceMiles;
	int _elevationGainFeet;
	string _difficulty;
	int _snowDepth;
	int _avalancheRisk;
	string _weather;
};

#endif // ROUTE_H