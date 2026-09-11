# Backcountry Ski Route Recommendation System

[main.cpp](https://github.com/carstenkirkland/BackcountrySkiRouteRecommendationSystem/blob/main/main.cpp)  
[route.cpp](https://github.com/carstenkirkland/BackcountrySkiRouteRecommendationSystem/blob/main/route.cpp)
<br>
[route.h](https://github.com/carstenkirkland/BackcountrySkiRouteRecommendationSystem/blob/main/route.h) <br>
[Makefile](https://github.com/carstenkirkland/BackcountrySkiRouteRecommendationSystem/blob/main/Makefile) <br>
[routes.txt - example](https://github.com/carstenkirkland/BackcountrySkiRouteRecommendationSystem/blob/main/routes.txt) <br>
[recommended_routes.txt - example](https://github.com/carstenkirkland/BackcountrySkiRouteRecommendationSystem/blob/main/recommended_routes.txt) <br>

## Description

This C++ program helps backcountry skiers evaluate and compare potential ski tours based on route characteristics and conditions such as distance, elevation gain, difficulty, snow depth, avalanche risk, and weather.

I developed this project because I enjoy backcountry skiing and wanted to apply programming to a problem that interested me personally. The idea was partly inspired by my dad, who has said that one of the most time-consuming parts of backcountry skiing is planning a tour.

The program reads route information from an external file and stores each route as a `SkiRoute` object. Users can view available routes, filter routes by difficulty or avalanche risk, calculate estimated tour times, and receive recommendations based on a calculated safety score.

> **Note:** The safety score used in this project was created for programming purposes and is not an avalanche forecasting model. It should not be used to make real-world backcountry safety decisions.

---

## How to Use the Program

Compile the project using the included Makefile with **make**, then run **./Final**.

When the program starts, the following menu appears:

1. Display all ski routes
2. Filter routes by difficulty
3. Filter routes by avalanche risk
4. Recommend safe routes
5. Save recommended routes to file
6. Exit

### Option 1: Display All Routes

Displays all routes loaded from `routes.txt` along with:

- Distance
- Elevation gain
- Difficulty
- Snow depth
- Avalanche risk
- Weather
- Estimated tour time
- Safety score

### Option 2: Filter by Difficulty

Users can filter routes by **Easy, Moderate, or Hard**.

### Option 3: Filter by Avalanche Risk

Users enter a maximum avalanche-risk rating from **1–5**. The program displays routes with an avalanche-risk value at or below the selected threshold.

### Option 4: Recommend Routes by Safety Score

Users enter a minimum safety score between **0.0 and 1.0**.

The program calculates a safety score for each route using:

- Avalanche risk
- Snow depth
- Weather conditions
- Route difficulty

Routes meeting or exceeding the selected minimum score are displayed.

### Option 5: Save Recommended Routes

Users enter a minimum safety score and qualifying routes are written to `recommended_routes.txt`.

The output file includes each route's characteristics, estimated tour time, and calculated safety score.

### Option 6: Exit

Exits the program.

---

## Program Structure

The program uses a custom `SkiRoute` class to store route information and perform calculations related to each route.

Each `SkiRoute` object contains:

- Route name
- Distance
- Elevation gain
- Difficulty
- Snow depth
- Avalanche risk
- Weather

Routes are stored in a `vector<SkiRoute>`, allowing the program to dynamically load and process route data from an external file.

### Project Files

- `main.cpp` — Main program, menu, filtering, and recommendations
- `route.cpp` — `SkiRoute` class function implementations
- `route.h` — `SkiRoute` class declaration
- `routes.txt` — Input route dataset
- `Makefile` — Compilation instructions and dependencies

---

## Safety Score

One of the major changes I made during development was replacing my original `isSafeRoute()` function with `calculate_safety_score()`.

Instead of classifying a route as simply safe or unsafe, the program calculates a value between **0.0 and 1.0**, with higher values representing higher calculated safety.

The calculation starts at 1.0 and makes deductions based on route conditions:

- **Avalanche Risk:** Each increase above avalanche risk 1 reduces the score by 0.20
- **Snow Depth:** Below 30 inches reduces the score by 0.20; 30–44 inches reduces it by 0.10
- **Weather:** Windy reduces the score by 0.20, snow by 0.15, and cloudy conditions by 0.05
- **Difficulty:** Hard routes reduce the score by 0.10 and moderate routes by 0.05

The final score is limited to the range **0.0–1.0**.

This approach allowed me to incorporate multiple variables into the recommendation rather than using a simple Boolean safe/unsafe classification.

---

## Estimated Tour Time

The program estimates tour duration using distance and elevation gain.

The calculation assumes **0.5 hours per mile plus 1.0 hour per 1,000 feet of elevation gain**.

For example, Berthoud Pass has a distance of 6.5 miles and 2,500 feet of elevation gain:

**(6.5 × 0.5) + (2.5 × 1.0) = 5.75 hours**

---

## File I/O

The program uses `ifstream` to read route information from `routes.txt`.

Each route is converted into a `SkiRoute` object and added to a vector, allowing the dataset to be modified without hardcoding individual routes into the program.

The program also uses `ofstream` to save recommendations to `recommended_routes.txt`.

An example saved route includes the route name, distance, elevation gain, difficulty, snow depth, avalanche risk, weather, estimated tour time, and safety score.

---

## Reflection

This project gave me experience designing and implementing a larger C++ program from scratch. One of my biggest challenges was determining how to organize the program into separate components, particularly creating a class that encapsulated both route data and related functionality.

Separating responsibilities between the `SkiRoute` class and the main program helped me better understand object-oriented programming and made the overall structure easier to manage.

I also gained experience reading structured data from an external file and converting that information into objects. Debugging issues related to file reading and data types was an important part of the development process.

Another major takeaway was the importance of incremental development. Building and testing individual components before integrating them into the complete program made debugging easier and helped prevent larger problems later.

If I continued developing the project, I would add more advanced sorting and filtering, improve input validation, and explore more sophisticated methods for comparing routes.

Overall, this project strengthened my understanding of C++, object-oriented programming, file I/O, data structures, debugging, and the process of turning an idea into a functioning program.

---

## Tools & Technologies

- **C++**
- **Visual Studio Code**
- **Make / Makefile**

## Key Concepts

- Object-Oriented Programming
- Classes and Objects
- Vectors
- File I/O
- Data Filtering
- Algorithm Development
- Modular Program Design
- Testing and Debugging
- Multi-File C++ Projects
