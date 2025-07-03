# 🗺 Smart City Planner – A DSA-based City Mapping & Navigation System

Welcome to the **Smart City Planner**, a console-based project built using **Data Structures and Algorithms** in C. This project simulates a smart city navigation and management system, allowing users to explore city networks, manage urban data, and plan journeys efficiently.

---

## 🚀 Features & Functionalities

1. **Display City List** – View all available cities in the network.
2. **Explore Routes** – Explore direct and indirect city-to-city travel routes.
3. **Plan Your Trip** – Input start and end cities and plan your journey.
4. **Search for a Place** – Find a specific location/building in the city.
5. **View City Connections** – See which cities are directly connected.
6. **Add a City** – Dynamically add new cities to the map.
7. **Add a Route** – Define new travel paths between existing cities.
8. **Register a Building** – Add key locations or landmarks within a city.
9. **Discover Key Locations** – List popular or notable locations per city.
10. **Find Top-Rated Buildings** – Show locations/buildings with the best user ratings.
11. **Discover Best Neighborhood Hangout Cities** – Find cities with most fun/relaxing places.
12. **Plot the Most Efficient Journey** – Use algorithms to find the shortest path between two cities.
13. **Find the Closest City** – From a given city, discover the nearest neighbor by distance.
14. **Create Your Own Customized Map** – Modify the graph to suit your needs.
15. **Calculate Overall and City-wise Average Rating** – Analyze average ratings for city buildings.
16. **Play Game in Traffic** – A fun simulation/game to entertain during congestion.
17. **Display Directly Connected Routes for a City** – Show routes that are one-hop away.
---

## 📂 Data Files

### 📄 `placess.txt`

This file contains the **list of all cities** in the format:

```
<city_id> <city_name>
```

Example:

```
0 Ayodhya
1 Belgaum
2 Delhi
```

### 📄 `place.txt`

This file contains **buildings, places or landmarks** within each city along with their **user ratings** in stars (represented by `*`):

```
<city_name> <place_name> <rating>
```

Example:

```
Ayodhya Ram_Temple ******
Delhi India_gate ******
Surat Gas_Station ****
```

### 📄 `graph_data.txt`

This file defines the **graph connectivity** between cities. Each line represents a route:

```
<city1> <city2> <distance_in_km>
```

Example:

```
Ayodhya Belgaum 200
Delhi Faridabad 500
Surat Mumbai 2500
```

> Note: The graph is **undirected** unless specified otherwise.

---

## ⚙️ Technologies Used

* Language: **C++**
* Concepts: **Graph Data Structures**, **Priority Queue**, **Dijkstra’s Algorithm**, **File I/O**, **Greedy Algorithms**, **Hash Maps**, **Vectors**, **DFS/BFS**

---

## 💡 How to Run

1. Clone this repository:

   ```bash
   git clone https://github.com/yourusername/smart-city-planner.git
   cd smart-city-planner
   ```

2. Compile the code:

   ```bash
   g++ main.cpp -o planner
   ```

3. Run the executable:

   ```bash
   ./planner
   ```

> Make sure the text data files (`placess.txt`, `place.txt`, `graph_data.txt`) are in the same directory as the compiled executable.

---

## 🛠️ Project Goals

* Apply DSA concepts in a real-world simulation.
* Practice file handling and graph traversal.
* Model city connections for travel and urban planning.

---
## 👨‍💻 Author

**Nagendra B Hanchinale**  
Email: [nagendrahanchinale19@google.com](mailto:nagendrahanchinale19@google.com)


