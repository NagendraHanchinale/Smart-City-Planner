#include "Myhead.h"
#include "Locals.h"


// Function:    load_from_file
// Description: Loads data from three text files:
//              graph_data.txt: Contains route information (starting point, destination, distance).
//              place.txt: Contains places information (name, description, rating).
//              placess.txt: Contains a list of place names.
// Input param: None
// Return Type: void (No return value)
void load_from_file()
{
  // Open the files in read mode
  FILE *fp_routes = fopen("graph_data.txt", "r");
  FILE *fp_places = fopen("place.txt", "r");
  FILE *fp_placess = fopen("placess.txt", "r");

  // Check if any files failed to open
  if (fp_routes == NULL || fp_places == NULL || fp_placess == NULL)
  {
    printf("File Not found\n");
    exit(EXIT_FAILURE);  // Exit the program if any file is missing
  }

  // Load route information from graph_data.txt
  global_count = 0;

  while (fscanf(fp_routes, "%s %s %d", route[global_count].from, route[global_count].destination,
                                       &route[global_count].distance) != EOF) {
    global_count++;  // Increment the route count
  }

  // Load place information from place.txt
  while (fscanf(fp_places, "%s %s %s", places[places_count].place, places[places_count].what, places[places_count].rating) != EOF) {
    places_count++;  // Increment the place count
  }

  // Close the route and place files
  fclose(fp_routes);
  fclose(fp_places);

  // Load place names from placess.txt
  pcount = 0;

  while (fscanf(fp_placess, "%d %s", &City[pcount].pindex, City[pcount].placess) != EOF) {
    pcount++;  // Increment the place name count
  }

  fclose(fp_placess);  // Close the place names file
}


// Function:    load_map
// Description: Initializes distance in 'map'(adjacency matrix) based on route information.
//              Sets 'MAX'(999999) values for places with no direct path and fills in distances for existing paths.
// Input param: None
// Return Type: void (No return value)

void load_map()
{

  // Initialize the adjacency matrix with 'MAX' values (indicating no direct path)
  for (int i = 0; i < global_count; ++i)
  {
    for (int j = 0; j < global_count; ++j)
    {
      map[i][j] = MAX;  // No direct path by default
    }
  }

  // Populate the adjacency matrix with distances from the 'route' data
  for (int i = 0; i < global_count; ++i)
  {
    int k = indexof(route[i].from);  // Get the index of the starting place
    int m = indexof(route[i].destination);  // Get the index of the destination place
    map[k][m] = route[i].distance;  // Set the distance between them
    map[m][k] = route[i].distance;  //distance is the same in both directions
  }
}

///***********************************FUNCTION1***********************************///

// Function:    load_from_file1
// Description: Loads place names from a file and inserts them into a BST
// Input param: city_root - The root node of the BST
// Return Type: TREE* - The new root of the BST with loaded place names
TREE *load_from_file1(TREE *city_root)
{
    city_root = NULL;
    for (int i = 0; i < pcount; ++i)
    {
        // Insert each place name into the BST
        city_root = insert_into_bst(city_root, City[i].placess);
    }

    return city_root;
}


// Function:    insert_into_bst
// Description: Inserts a new node with the given place name into a binary search tree (BST)
// Input param: root - The root node of the BST,The place name to insert
// Return Type: TREE* - The new root of the BST
TREE *insert_into_bst(TREE *root, char p_name[])
{
    if (root == NULL) {
        // Create a new node if the BST is empty
        root = (TREE *)malloc(sizeof(TREE));
        strcpy(root->place_name, p_name);
        root->left = root->right = NULL;
        return root;
    }

    // Traverse the BST to find the insertion point based on alphabetical order
    if (p_name[0] < root->place_name[0]) {
        root->left = insert_into_bst(root->left, p_name);
    } else if (p_name[0] > root->place_name[0]) {
        root->right = insert_into_bst(root->right, p_name);
    } else if (p_name[0] == root->place_name[0]) {
        // If names have the same first letter, use check_greatest for further comparison
        if (check_greatest(p_name, root->place_name)) {
            root->right = insert_into_bst(root->right, p_name);
        } else {
            root->left = insert_into_bst(root->left, p_name);
        }
    }

    return root;
}



// Function:    check_greatest
// Description: Compares two place names lexicographically
// Input param: place1 - The first place name
//              place2 - The second place name
// Return Type: int - 1 if place1 is lexicographically greater, 0 otherwise
int check_greatest(char *place1, char *place2)
{
    int n = fmin(strlen(place1), strlen(place2));
    for (int i = 0; i < n; ++i)
    {
        if (place1[i] > place2[i])
        {
            return 1;
        }
        else if (place1[i] < place2[i])
        {
            return 0;
        }
        // No need for an 'else' statement here
    }

    // Handle the case when one string is a prefix of the other
    if (strlen(place1) < strlen(place2))
    {
        return 0;
    }
    else if (strlen(place1) > strlen(place2))
    {
        return 1;
    }

    // Strings are equal
    return 0;
}


// Function:    inorder
// Description: Performs an inorder traversal of a BST and prints node place names
// Input param: root - The root node of the BST
void inorder(TREE *root)
{
    if (root != NULL)
    {
        inorder(root->left);  // Visit left subtree
        printf("%s\n", root->place_name); // Print node value
        inorder(root->right); // Visit right subtree
    }
}



///*****************************FUNCTION 2***********************************///



// Function:    print_route
// Description: Prints a list of all routes in the format "Starting Point -> Destination Distance".
// Input param: None
// Return Type: void (No return value)
void print_route()
{
    int num_routes = global_count; // Number of routes read from RD

    // Sort routes by distance using merge sort
    mergeSort(route, 0, num_routes - 1);
    for (int i = 0; i < global_count; ++i)
    {
        printf("%s -> %s %d\n", route[i].from, route[i].destination, route[i].distance);
    }
}



// Function:    merge
// Description: Merges two sorted subarrays of an array of optimalroot structs into a single sorted subarray.
// Input params:routes: The array of optimalroot structs to be merged.
//              left: The index of the first element in the left subarray.
//              right: The index of the last element in the right subarray.
// Return Type: void (No return value, modifies the original array)
void merge(struct optimalroot routes[], int left, int right) {
    int mid = left + (right - left) / 2;  // Calculate mid index

    // Calculate lengths of subarrays
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temporary arrays to hold subarrays
    struct optimalroot L[n1], R[n2];

    // Copy elements into temporary arrays
    for (int i = 0; i < n1; i++)
    {
        L[i] = routes[left + i];
    }
    for (int j = 0; j < n2; j++)
    {
        R[j] = routes[mid + 1 + j];
    }

    // Merge temporary arrays back into original array in sorted order
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i].distance <= R[j].distance) {
            routes[k] = L[i];
            i++;
        } else {
            routes[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy any remaining elements from L or R
    while (i < n1) {
        routes[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        routes[k] = R[j];
        j++;
        k++;
    }
}



// Function:    mergeSort
// Description: Sorts an array of optimalroot structs in ascending order of their "distance" members using the merge sort algorithm.
// Input param: routes: The array of optimalroot structs to be sorted.
//              left: The index of the first element in the subarray to be sorted.
//              right: The index of the last element in the subarray to be sorted.
// Return Type: void (No return value, modifies the original array)
void mergeSort(struct optimalroot routes[], int left, int right) {

    if (left < right) {
        // Divide the array into two halves
        int mid = left + (right - left) / 2;

        // Recursively sort the two halves
        mergeSort(routes, left, mid);
        mergeSort(routes, mid + 1, right);

        // Merge the sorted halves back together
        merge(routes, left, right);
    }
}


///*********************FUNCTION 3**************************************///



// Function:    dijkstra
// Description: Implements Dijkstra's algorithm to find the shortest path and distance between two nodes in a graph.
// Input params:nn: The total number of nodes in the graph.
//              Matrix: The adjacency matrix representing the graph, where Matrix[i][j] stores the distance between node i and node j.
//              sourceNode: The name of the starting node.
//              destNode: The name of the destination node.
// Return Type: void (No return value)
void dijkstra(int nn, int Matrix[SIZE][SIZE], char sourceNode[30], char destNode[30]) {
  // Get the indices of the source and destination nodes in the adjacency matrix
  int source = indexof(sourceNode);
  int destination = indexof(destNode);

  // Arrays to store distances, paths, and visited status
  int dist[SIZE], path[SIZE], visited[SIZE];

  // Initialization
  for (int i = 0; i < nn; i++) {
    // Initialize distances to direct distances from the source
    dist[i] = Matrix[source][i];
    // Initialize paths to point back to the source
    path[i] = source;
    // Mark all nodes as unvisited
    visited[i] = 0;
  }

  // Mark the source node as visited
  visited[source] = 1;

  // Main loop of Dijkstra's algorithm
  for (int i = 1; i < nn - 1; i++) {
    // Find the unvisited node with the minimum distance
    int min = MAX, k = 0;
    for (int j = 0; j < nn; j++) {
      if (!visited[j] && dist[j] < min) {
        min = dist[j];
        k = j;
      }
    }

    // Mark the found node as visited
    visited[k] = 1;

    // Update distances and paths for neighbors of the found node
    for (int j = 0; j < nn; j++) {
      if (!visited[j]) {
        int distance = dist[k] + Matrix[k][j];
        if (distance < dist[j]) {
          dist[j] = distance;
          path[j] = k;
        }
      }
    }
  }
   if(dist[destination] == MAX)
   {
       printf("\nSorry i couldn't find the root\n");
       return;
   }
  // Print the shortest path
  int current = destination;
  printf("Path: %s", City[current].placess);
  while (current != source) {
    current = path[current];
    printf(" <- %s", City[current].placess);
  }

  // Print the shortest distance
  printf("\nShortest distance from %s to %s: %dkm\n", sourceNode, destNode, dist[destination]);

  // Calculate and print travel time based on user-selected speed
  float speed;
  printf("\nEnter the traveling medium\n");
  printf("1. Car\n");
  printf("2. Walk\n");
  scanf("%f", &speed);
  if (speed == 1) {
    speed = 50.0;  // Speed for car
  } else if (speed == 2) {
    speed = 7.0;   // Speed for walking
  } else {
    speed = 30.0;   // Default speed
  }
  printf("Time required: %0.2f hrs\n", dist[destination] / speed);
}


///*****************FUNCTION 4***************************///


// Function:    sort
// Description: Sorts the places array in ascending order based on their ratings.
// Input param: None
// Return Type: void (No return value)
void sort()
{
  quicksort(0, places_count - 1);
}



// Function:    quicksort
// Description: Implements the quicksort algorithm to sort a portion of the places array.
// Input param: low: The starting index of the portion to be sorted.
//              high: The ending index of the portion to be sorted.
// Return Type: void (No return value)
void quicksort(int low, int high)
{
  if (low < high)
  {
    // Partition the array and recursively sort the subarrays
    int pi = partition(low, high);
    quicksort(low, pi - 1);
    quicksort(pi + 1, high);
  }
}




// Function:    partition
// Description: Partitions the places array around a pivot element for quicksort.
// Input param: low: The starting index of the portion to be partitioned.
//              high: The ending index of the portion to be partitioned.
// Return Type: int (The index of the pivot element after partitioning)
int partition(int low, int high)
{
  // Select the first element as the pivot
  char pivot[100];
  strcpy(pivot, places[low].rating);

  // Partition the array around the pivot
  int i = low;
  int j = high + 1;

  do {
    do {
      i++;
    } while (strcmp(places[i].rating, pivot) > 0);

    do {
      j--;
    } while (strcmp(places[j].rating, pivot) < 0);

    if (i < j)
    {
      // Swap elements
      Place temp = places[i];
      places[i] = places[j];
      places[j] = temp;
    }
  } while (i < j);

  // Place the pivot in its final position
  Place temp = places[low];
  places[low] = places[j];
  places[j] = temp;

  return j;
}



// Function:    Find_location
// Description: Allows the user to search for places of a specific type.
// Input param: None
// Return Type: void (No return value)
void Find_location()
{
  // Sort places array (not directly used in search)
  sort();

  // Prompt user for desired place type
  char Place_type[20];
  printf("Enter the type of place you are looking for: ");
  scanf("%s", Place_type);

  // Convert input to uppercase for case-insensitive search
  convert_case(Place_type);

  bool found_place = false;
  printf("%s in:\n", Place_type);

  // Iterate through all places
  for (int i = 0; i < places_count; ++i)
 {
    // Use bfss to check if place type matches user input
    if (bfss(i, Place_type, places[i].what))
    {
      // Match found - print city name, type, and rating
      printf("%s->%s <rating:%d>\n", places[i].place, places[i].what, strlen(places[i].rating));
      found_place = true;
    }
  }
  // No match found - inform user
  if (!found_place)
  {
    printf("Sorry, there is no such place\n");
  }
}



// Function:    bfss (Brute-force String Search)
// Description: Checks if a pattern (place type) exists within a city name.
// Input param: Unused index,pattern,city_name
// Return Type: int (1 if pattern found, 0 if not found)
int bfss(int i, char pattern[], char city[])
{
  // Get string lengths for efficiency
  int n = strlen(city);
  int m = strlen(pattern);

  // Compare substrings for each possible starting position in the city name
  for (int k = 0; k <= n - m; k++)
    {
    int j = 0; // Index for pattern characters
    while (j < m && pattern[j] == city[k + j])
    {
      j++; // Match found so far
    }
    // Pattern found if entire pattern matches a substring
    if (j == m)
    {
      return 1;
    }
  }

  // No match found after iterating through all positions
  return 0;
}



///**********************FUNCTION 5******************************///



// Function:    dfs
// Description: Performs a depth-first search (DFS) traversal on the graph to explore a spanning tree.
// Input param: node: The starting node for the DFS traversal.size: The number of nodes in the graph.
//              Total_distance: A pointer to an integer to store the total distance of the spanning tree.
// Return Type: void (No return value)
void dfs(int node, int size, int *Total_distance)
{
  // Mark current node as visited.
  visited[node] = 1;

  // Loop through all adjacent nodes.
  for (int i = 0; i < size; ++i)
    {
    if (!visited[i] && map[node][i] != MAX)
    {
      // Add edge distance to total distance.
      *Total_distance += map[node][i];

      // Print the edge using city names.
      printf("%s -> %s\n", City[node].placess, City[i].placess);

      // Recursively call dfs on adjacent node.
      dfs(i, size, Total_distance);
    }
  }
}



// Function:    SpanningTree
// Description: Initiates the process of finding and displaying a spanning tree.
// Input param: size: The number of nodes in the graph.
// Return Type: void (No return value)
void SpanningTree(int size)
{
  int Total_distance = 0; // Initialize total distance to 0.

  // Reset visited array to mark all nodes unvisited.
  for (int i = 0; i < size; ++i)
  {
    visited[i] = 0;
  }

  // Print a header for the spanning tree output.
  printf("\nMinimum Spanning Tree:\n");

  // Start DFS traversal from node 0 to explore the spanning tree.
  dfs(0, size, &Total_distance);

  // Print the total distance of the spanning tree.
  printf("Total distance: %d km\n", Total_distance);
}



///*************************FUNCTION 6******************************///



// Function:    addPlace
// Description: Allows the user to add new cities to the list of places.
// Input param: None
// Return Type: void (No return value)
void addPlace()
{
  int Ncity;
  printf("Enter no of city you want add:");
  scanf("%d", &Ncity);

  while (Ncity--)
    {
    char City_name[20];
    printf("Enter city name:");
    scanf("%s", City_name);

    // Convert input to uppercase for case-insensitive handling
    convert_case(City_name);

    // Check for duplicates before adding
    if (!isvalid(City_name))
    {
      // Add the city to the City array
      strcpy(City[pcount].placess, City_name);
      City[pcount].pindex = City[pcount - 1].pindex + 1;  // Assign a unique index
      pcount++;  // Increment the place count
      printf("City '%s' added successfully\n", City_name);
      addroute();
    }
    else
    {
      printf("City with name '%s' is already there\n", City_name);
      Ncity++;  // Re-prompt for the same city input
    }
  }
}



///**************************FUNCTION 7*****************************///



// Function:    addroute
// Description: Allows the user to add new routes between existing cities.
// Input param: None
// Return Type: void (No return value)
void addroute()
{
  int Nroutes;
  printf("Enter no of routes you want to add: ");
  scanf("%d", &Nroutes);

  while (Nroutes--)
  {
    char from[30], destination[30];
    int distance;

    printf("Enter details for the new route:\n");
    printf("From: ");
    scanf("%s", from);
    convert_case(from);  // Convert to uppercase for consistency

    printf("Destination: ");
    scanf("%s", destination);
    convert_case(destination);  // Convert to uppercase for consistency

    printf("Distance: ");
    scanf("%d", &distance);

    // Ensure both cities are valid before adding the route
    if (isvalid(from) && isvalid(destination))
    {
      // Add route details to the route array
      strcpy(route[global_count].from, from);
      strcpy(route[global_count].destination, destination);
      route[global_count].distance = distance;
      global_count++;  // Increment route count

      printf("New route added successfully!\n");
      load_map();  // Update the adjacency matrix to reflect the new route
    }
    else
    {
      printf("Either '%s' or '%s' is not a valid city. Please add first.\n", from, destination);
      Nroutes++;
    }
  }
}


///**************************FUNCTION 8*****************************///

// Function:    add_building
// Description: Allows the user to add new buildings to existing cities.
// Input param: None
// Return Type: void (No return value)
void add_building()
{
  int NO_building;
  printf("Enter no of Places:");
  scanf("%d", &NO_building);

  while (NO_building--)
  {
    char city_name[10];
    char building[10];
    char c_ratting[10];

    printf("City Name:");
    scanf("%s", city_name);
    printf("Place_name:");
    scanf("%s", building);

    convert_case(city_name);  // Convert city and building names to uppercase
    convert_case(building);

    printf("Its Ratting(Ex:***):");
    scanf("%s", c_ratting);

    // Limit rating length to 6 characters for consistency
    if (strlen(c_ratting) > 6)
    {
      strcpy(c_ratting, "******");
    }

    // Ensure the city exists before adding the building
    if (isvalid(city_name))
    {
      // Add building details to the places array
      strcpy(places[places_count].place, city_name);
      strcpy(places[places_count].rating, c_ratting);
      strcpy(places[places_count].what, building);
      places_count++;  // Increment place count
    }
    else
    {
      printf("There is no city named -> '%s'\n", city_name);
      break;  // Exit the loop if the city is invalid
    }
  }
}


///**************************FUNCTION 9*****************************///


// Function:    important_places
// Description: Prints the names and types of important places based on their rating.
// Input param: None
// Return Type: void (No return value)
void important_places()
{
  for (int i = 0; i < places_count; ++i)
 {
    // Check if a place's rating meets the importance criteria
    if (check_for_importance(places[i].rating))
    {
      // Print the details of important places
      printf("%s->%s\n", places[i].place, places[i].what);
    }
  }
}



// Function:    check_for_importance
// Description: Determines if a place's rating is considered important.
// Input param: rating: The rating string to evaluate.
// Return Type: int (1 if important, 0 if not important)
int check_for_importance(char* rating)
{
  // Importance criterion: rating length greater than 5 characters
  if (strlen(rating) > 5)
  {
    return 1;  // Place is important
  }
  else
  {
    return 0;  // Place is not important
  }
}


///**************************FUNCTION 10*****************************///


// Function:    Display_wrt_rating
// Description: Prints places from the 'places' array that have a specified rating.
// Input param: None
// Return Type: void (No return value)
void Display_wrt_rating()
{
    // Stores the user-entered rating
    char rating[50];

    printf("Rating (Ex: ***): ");
    scanf("%s", rating);

    // Check for valid rating length before comparison
    if (strlen(rating) > 6)
    {
        printf("Invalid rating length! Please enter a rating of 6 characters or less.\n");
        return; // Exit the function if the rating is invalid
    }

    // Loop through all places in the 'places' array
    for (int i = 0; i < places_count; ++i)
    {
        // Compare the current place's rating with the user-entered rating
        if (strcmp(rating, places[i].rating) == 0)
        {
            // Ratings match, so print the place's name and type
            printf("%s -> %s\n", places[i].place, places[i].what);
        }
    }
}



///**************************FUNCTION 11*****************************///



// Function:    bfs
// Description: Performs Breadth-First Search (BFS) to find nearby places within a distance limit.
// Input params:start_node: The index of the starting city in the 'map' and 'City' arrays.
//              size: The total number of cities.
//              distance_limit: The maximum distance to explore from the starting city.
// Return Type: void (No return value)
void bfs(int start_node, int size, int distance_limit)
{
  // Queue for BFS traversal
  int queue[SIZE];
  int front = -1, rear = -1;
  bool found = false;
  // Keep track of visited cities and cumulative distances
  int visited[size];
  int current_node, cumulative_distance;

  printf("\nNearby Places:\n");

  // Initialize all cities as unvisited
  for (int i = 0; i < size; ++i)
  {

    visited[i] = 0;

  }

  // Enqueue the starting city and mark it as visited
  queue[++rear] = start_node;
  visited[start_node] = 1;

  // BFS loop
  while (front != rear)
  {

    current_node = queue[++front];

    // Explore neighbors of the current city
    for (int i = 0; i < size; ++i)
    {
      // Check if neighbor is unvisited and has a direct path
      if (!visited[i] && map[current_node][i] != MAX)
      {
        visited[i] = 1;  // Mark neighbor as visited
        cumulative_distance = map[current_node][i];

        // If neighbor is within distance limit, print its details
        if (cumulative_distance <= distance_limit)
        {
          found = true;
          printf("%s (Distance: %d Km)\n", City[i].placess, cumulative_distance);
          its_speciality(City[i].placess);  // Print special features
          queue[++rear] = i;

        }

      }
    }
  }

    if(!found)
    {
        printf("\nThere are no places nearby within distance limit of : %dkm\n",distance_limit);
    }
}




// Function:    findNearbyPlaces
// Description: Prompts the user for their location and distance limit, then calls bfs to find nearby places.
// Input param: None
// Return Type: void (No return value)
void findNearbyPlaces()
{
  char location[30];
  int distance_limit;

  printf("Enter your current location: ");
  scanf("%s", location);
  convert_case(location);

  if (!isvalid(location))
  {
    printf("Invalid location!\n");
    return;
  }

  printf("Maximum distance between places:");
  scanf("%d", &distance_limit);

  int start_node = indexof(location);
  if (start_node == -1)
  {
    printf("Invalid location!\n");
    return;
  }

  bfs(start_node, global_count, distance_limit);
  loading();
}


///**************************FUNCTION 12*****************************///



// Function :   start the route-finding process
// Description: Prompts the user for route input, handles multiple routes, and calls Dijkstra's algorithm for each route.
// Input param: None (takes input from the user directly)
// Return Type: void (does not return a value)
void rootfortrip()
{
    int numcities;
    printf("\nEnter the number of cities you want to visit: ");
    scanf("%d", &numcities);

    char startPlace[50], endPlace[50];

    // Get input for the starting and ending places of the first route
    printf("Enter starting place: ");
    scanf("%s", startPlace);
    printf("Enter Destination: ");
    scanf("%s", endPlace);

    convert_case(startPlace);
    convert_case(endPlace);
    int startIdx = indexof(startPlace);
    int endIdx = indexof(endPlace);

    if (startIdx != -1 && endIdx != -1)
    {
        dijkstra1(pcount, map, startPlace, endPlace, numcities - 1);
    }
    else
    {
        printf("Invalid places!\n");
    }
}



// Function :   implement Dijkstra's algorithm to find the shortest path
// Description: Implements Dijkstra's algorithm to find the shortest path between two places in a map, handling multiple routes recursively.
// Input param: nn (number of nodes), Matrix (adjacency matrix), sourceNode (starting place), destNode (ending place), remainingRoutes (number of remaining routes)
// Return Type: void (does not return a value)
void dijkstra1(int nn, int Matrix[SIZE][SIZE], char sourceNode[30], char destNode[30], int remainingRoutes)
{
       int source = indexof(sourceNode);
       int destination = indexof(destNode);


 int dist[SIZE], path[SIZE], visited[SIZE];


 for (int i = 0; i < nn; i++)
 {

   dist[i] = Matrix[source][i];

   path[i] = source;

   visited[i] = 0;
 }


 visited[source] = 1;


 for (int i = 1; i < nn - 1; i++)
 {

   int min = MAX, k = 0;
   for (int j = 0; j < nn; j++) {
   if (!visited[j] && dist[j] < min)
   {
       min = dist[j];
       k = j;
   }
 }

 visited[k] = 1;

 for (int j = 0; j < nn; j++)
 {
  if (!visited[j])
  {
   int distance = dist[k] + Matrix[k][j];
   if (distance < dist[j])
  {
   dist[j] = distance;
   path[j] = k;
  }
  }
 }
 }

 int current = destination;
    printf("Path:%s", City[destination].placess);
    while (current != source)
    {
        current = path[current];
        printf(" <- %s", City[current].placess);
    }
    if (remainingRoutes == 0)
    {
        return;
    }
    else
    {
        char nextDestination[10];
        printf("\nEnter next destination: ");
        scanf("%s", nextDestination);
        convert_case(nextDestination);

        if(isvalid(nextDestination)){
        if (strcmp(destNode, nextDestination) == 0)
        {
                printf("\nYou are already in %s\n", nextDestination);

        }
        else
        {
            dijkstra1(pcount, map, destNode, nextDestination, remainingRoutes - 1);
        }
        }
        else{
            printf("\nInvalid place!\n");
        }
    }
}


///**************************FUNCTION 13*****************************///


// Function:    nearest_place
// Description: Prompts the user for a city name and finds the nearest city using the Floyd-Warshall algorithm
// Input param: None
// Return Type: void
void nearest_place()
{
    char City_name[100];
    printf("City name:");
    scanf("%s", City_name);
    convert_case(City_name);  //  this function converts case for consistency
    int sourceIndex = indexof(City_name);  // this function finds the city's index

    if (sourceIndex != -1)
    {
        int nearest_vertex = floyd_warshall(map, global_count, sourceIndex);
        printf("Nearest city from %s is: %s\n", City_name, City[nearest_vertex].placess);
    }
    else
    {
        printf("City not found.\n");
    }
}



// Function:    floyd_warshall
// Description: Implements the Floyd-Warshall algorithm to find all-pairs shortest paths in a weighted graph.
// Input params:graph: The adjacency matrix representing the graph (distances between vertices).
//              V: The number of vertices in the graph.
//              source: The index of the source vertex for which we want to find the nearest vertex.
// Return Type: int - The index of the nearest vertex to the source.
int floyd_warshall(int graph[100][100], int V, int source) {

    int dist[100][100];  // Distance matrix to store shortest distances

    // Initialize distance matrix with initial distances from the graph
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            dist[i][j] = graph[i][j];
        }
    }

    // Floyd-Warshall algorithm:
    // Iterate through all possible intermediate vertices to update shortest paths
    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    // If a shorter path is found through vertex k, update the distance
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    // Handle unreachable vertices (marked as MAX) by setting their distances to 0
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (dist[i][j] == MAX) {
                dist[i][j] = 0;
            }
        }
    }

    // Find the nearest vertex to the source:
    int nearest_vertex = -1;  // Initialize to an invalid value
    int min_dist = 9999;  // Initialize with a large value to find the minimum

    for (int i = 0; i < V; i++) {
        // Exclude the source itself and unreachable vertices
        if (i != source && dist[source][i] < min_dist && dist[source][i] != 0) {
            // Update the nearest vertex and minimum distance if a closer one is found
            min_dist = dist[source][i];
            nearest_vertex = i;
        }
    }

    printf("\nWith distance: %dkm\n", min_dist);
    return nearest_vertex;  // Return the index of the nearest vertex
}

///***************************FUNCTION 14********************************///

// Function:    create_map
// Description: Customizes the map by allowing the user to add cities, routes, and places.
// Input param: None
// Return Type: void (No return value)
void create_map()
{

  global_count = 0;
  pcount = 0;
  places_count = 0;


  printf("\nHow many cities do you want to add? ");
  int num_cities;
  scanf("%d", &num_cities);
  for (int i = 0; i < num_cities; ++i)
  {
    printf("\nEnter name of city #%d: ", i + 1);
    scanf(" %s", City[pcount].placess);
    convert_case(City[pcount].placess);
    City[pcount].pindex = pcount;
    pcount++;
  }


  printf("\nHow many routes do you want to add? ");
  int num_routes;
  scanf("%d", &num_routes);
  for (int i = 0; i < num_routes; ++i)
  {
    char source_city[100], destination_city[100];
    int distance;


    printf("\nEnter source city: ");
    scanf(" %s", source_city);
    convert_case(source_city);


    printf("\nEnter destination city: ");
    scanf(" %s", destination_city);
    convert_case(destination_city);

    int source_index = indexof(source_city);
    int destination_index = indexof(destination_city);

    while (source_index == -1 || destination_index == -1)
    {
      printf("\nInvalid city name(s). Please enter valid city names.\n");


      printf("Enter source city: ");
      scanf(" %s", source_city);
       convert_case(source_city);

      printf("Enter destination city: ");
      scanf(" %s", destination_city);
      convert_case(destination_city);


      source_index = indexof(source_city);
      destination_index = indexof(destination_city);
    }


    printf("Enter distance between these cities: ");
    scanf("%d", &distance);

    strcpy(route[global_count].from, source_city);
    strcpy(route[global_count].destination, destination_city);
    route[global_count].distance = distance;
    global_count++;
  }


  printf("\nHow many places do you want to add details for? ");
  int num_places;
  scanf("%d", &num_places);
  for (int i = 0; i < num_places; ++i)
  {
    printf("\nEnter name of the city: ");
    scanf(" %s", places[places_count].place);
    convert_case(places[places_count].place);

    printf("Enter the place type: ");
    scanf(" %s", places[places_count].what);
    convert_case(places[places_count].what);

    char rating[7];


      printf("Enter the rating of the place (out of 6): ");
      scanf("%s", &rating);

      if (strlen(rating) > 6)
      {
        printf("Invalid rating. Please enter a rating between 0 and 5.\n");
      }
      else
        {
            strcmp(places[places_count].rating,rating);
            places_count++;
        }
  }


  load_map();

  printf("\nYour custom map has been created!\n");
}

///***********************Function 15*********************************///



// Function:    cityAverageRating
// Description: Displays the overall average rating and prompts the user for a specific city's average rating.
// Input param: None
// Return Type: void (No return value)
void calculateAverageRating()
{

    if (places_count == 0)
    {
        printf("No places available to calculate average rating.\n");
        return;
    }

    int totalRating = 0;

    for (int i = 0; i < places_count; ++i)
    {
        totalRating += strlen(places[i].rating);
    }

    double overallAverageRating = (double)totalRating / places_count;

    printf("Overall Average Rating of all places: %.2f\n", overallAverageRating);

    calculate_city_avg();
}


// Function:    calculate_city_avg
// Description: Displays the overall average rating of the city.
// Input param: None
// Return Type: void (No return value)
void calculate_city_avg()
{

    int choice;
    printf("Do you want to know the average rating of a particular city? (1 for Yes / 0 for No): ");
    scanf("%d", &choice);

    if (choice == 1)
    {
        char city_name[100];
        printf("Enter the name of the city: ");
        scanf("%s", city_name);
        convert_case(city_name);

        int totalCityRating = 0;
        int cityPlacesCount = 0;

        for (int i = 0; i < places_count; ++i)
        {
            if (strcasecmp(city_name, places[i].place) == 0)
            {
                totalCityRating += strlen(places[i].rating);
                cityPlacesCount++;
            }
        }

        if (cityPlacesCount > 0)
        {
            double cityAverageRating = (double)totalCityRating / cityPlacesCount;
            printf("Average Rating of %s: %.2f\n", city_name, cityAverageRating);
        }
        else
        {
            printf("No places found for the specified city.\n");
        }
    }
    else
    {
      printf("\nthank you\n");
    }
}

///***************************Function 16****************************///



// Function:    displayNumberGuessing
// Description: Displays the instructions for the Number Guessing game.
// Input param: None
// Return Type: void (No return value)
void displayNumberGuessing()
{
    printf("\nNumber Guessing Game:\n");
    printf("I have selected a number between 1 and 100.\n");
    printf("Try to guess the number!\n\n");
}



// Function:    displayRockPaperScissors
// Description: Displays the instructions for the Rock-Paper-Scissors game.
// Input param: None
// Return Type: void (No return value)
void displayRockPaperScissors()
{
    printf("\nRock-Paper-Scissors Game:\n");
    printf("You are playing against the computer.\n");
    printf("Enter 'r' for rock, 'p' for paper, or 's' for scissors.\n\n");
}


// Function:     game
// Description:  Simulates an interactive game menu based on traffic conditions.
//               Offers Rock-Paper-Scissors, Number Guessing, and Instagram Reels options.
// Input params: None
// Return Type:  void (No return value)
void game()
{
    char stuckInTraffic;
    int trafficTime;

    // Ask the user if they are stuck in traffic
    printf("Are you stuck in traffic? (y/n): ");
    scanf(" %c", &stuckInTraffic);

    if (stuckInTraffic == 'y' || stuckInTraffic == 'Y')
    {
        // If yes, ask for estimated traffic time
        printf("Enter estimated traffic time (in minutes): ");
        scanf("%d", &trafficTime);

        if (trafficTime > 15)
        {
            // If traffic time is greater than 15 minutes, prompt user to choose a game
            printf("You have more than 15 minutes of traffic time.\n");

            int gameChoice;

            // Ask the user to choose a game
            printf("Choose a game:\n");
            printf("1. Rock-Paper-Scissors\n");
            printf("2. Number Guessing\n");
            printf("3. Watch Instagram Reels\n");
            printf("Enter your choice (1, 2, or 3): ");
            scanf("%d", &gameChoice);

            if (gameChoice == 1)
            {
                // Rock-Paper-Scissors game
                displayRockPaperScissors();

                char userChoice;
                char computerChoice;

                do {
                    // Get user's choice
                    printf("Enter your choice (r/p/s): ");
                    scanf(" %c", &userChoice);

                    // Validate user's choice
                    if (userChoice != 'r' && userChoice != 'p' && userChoice != 's')
                    {
                        printf("Invalid choice. Please enter 'r', 'p', or 's'.\n");
                        continue;
                    }

                    // Get computer's choice
                    srand(time(NULL));
                    int randomChoice = rand() % 3;
                    switch (randomChoice)
                    {
                        case 0:
                            computerChoice = 'r';
                            break;
                        case 1:
                            computerChoice = 'p';
                            break;
                        case 2:
                            computerChoice = 's';
                            break;
                    }

                    // Display choices
                    printf("Your choice: %c\n", userChoice);
                    printf("Computer's choice: %c\n", computerChoice);

                    // Determine the winner
                    if (userChoice == computerChoice)
                    {
                        printf("It's a tie!\n");
                    }
                    else if ((userChoice == 'r' && computerChoice == 's') ||
                               (userChoice == 'p' && computerChoice == 'r') ||
                               (userChoice == 's' && computerChoice == 'p'))
                    {
                        printf("You win!\n");
                    }
                    else
                    {
                        printf("Computer wins!\n");
                    }

                    // Ask if the user wants to play again
                    printf("Do you want to play again? (y/n): ");
                    scanf(" %c", &userChoice);

                } while (userChoice == 'y' || userChoice == 'Y');
            }
            else if (gameChoice == 2)
            {
                // Number Guessing game
                displayNumberGuessing();

                // Generate a random number between 1 and 100
                srand(time(NULL));
                int targetNumber = rand() % 100 + 1;

                int userGuess;
                int attempts = 0;

                do {
                    // Get user's guess
                    printf("Enter your guess: ");
                    scanf("%d", &userGuess);

                    // Check if the guess is correct
                    if (userGuess == targetNumber)
                    {
                        printf("Congratulations! You guessed the correct number in %d attempts.\n", attempts + 1);
                        break;
                    }
                    else if (userGuess < targetNumber)
                    {
                        printf("Try a higher number.\n");
                    }
                    else
                    {
                        printf("Try a lower number.\n");
                    }

                    attempts++;

                } while (1);
            }
            else if (gameChoice == 3)
            {
                // Watch Instagram Reels
                printf("You chose to watch Instagram Reels. YOU ARE AN INSTAGRAM ADDICT\n");
            }
            else
            {
                // Invalid choice
                printf("Invalid choice. Exiting...\n");
            }
        }
        else
        {
            // If traffic time is less than or equal to 15 minutes
            printf("You have less than or equal to 15 minutes of traffic time. Keep waiting!\n");
        }
    }
    else
    {
        // If not stuck in traffic
        printf("Great! No traffic. Keep moving!\n");
    }
}
///**************************FUNCTION 17*******************************///



// Function:    checkAndPrintConnectedCities
// Description: Prompts the user for a city name, checks if it is valid, and prints connected cities.
// Input param: None
// Return Type: void (No return value)
void check_and_print_connected_cities()
{
    char cityname[30];

    // Prompt the user for a city name
    printf("Enter the name of the city: ");
    scanf("%s", cityname);
    convert_case(cityname);

    // Check if the entered city is valid
    if (isvalid(cityname))
    {
        // Assuming 'map' is your adjacency matrix
        print_connected_cities(cityname, map);
    }
    else
    {
        printf("Invalid city name!\n");
    }
}


// Function:    printConnectedCities
// Description: Prints cities directly connected to the given city.
// Input param: cityName: The name of the city to check for connections.
//              map: The adjacency matrix representing connections between cities.
// Return Type: void (No return value)
void print_connected_cities(char cityname[30], int map[SIZE][SIZE])
{
    int cityIndex = indexof(cityname);

    if (cityIndex != -1)
    {
        printf("Cities directly connected to %s are:\n", cityname);

        int dist[SIZE][SIZE];

        for(int i = 0 ;i < pcount; ++i)
        {
            for(int j = 0;j < pcount ; ++j)
            {
                dist[i][j] = 0;
            }
        }


        for (int i = 0; i < pcount; i++) {
            for (int j = 0; j < pcount; j++) {
                if(map[i][j] != MAX)
                {
                    dist[i][j] = 1;
                }
            }
        }

        for (int j = 0; j < pcount; j++) {
            if (dist[cityIndex][j] == 1 && cityIndex != j) {
                printf("- %s\n", City[j].placess);
            }
        }
    }
    else
    {
        printf("City not found!\n");
    }
}



///**********************************************************************


// Function:    its_speciality
// Description: Prints the "specialities" (considered as important things to highlight) of a given location.
// Input param: location: The name of the location to display specialities for.
// Return Type: void (No return value)
void its_speciality(char* location)
{
  printf("\tSpeciality :\n");  // Print a header for specialities

  int found = 0;

  // Iterate through all places in the 'places' array
  for (int i = 0; i < places_count; ++i)
 {
    // Check if the current place matches the given location
    if (strcmp(location, places[i].place) == 0)
    {
      // If the place's rating is considered "important", print its "what" field as a speciality
      if (check_for_importance(places[i].rating))
      {
        found = 1;
        printf("\t%s\n", places[i].what);

      }
    }
  }
  if(!found)
  {
      printf("\nThere are no special places!\n");
  }
}


// Function:    convert_case
// Description: Converts a string to title case (first letter uppercase, rest lowercase).
// Input param: Data: The string to be converted.
// Return Type: void (No return value)
void convert_case(char Data[])
{
  // Capitalize the first letter of the string
  Data[0] = toupper(Data[0]);

  for (int i = 1; i < strlen(Data); ++i)
 {
    // Capitalize the first letter of each word
    if (Data[i - 1] == ' ' || Data[i - 1] == '_')
    {
      Data[i] = toupper(Data[i]);
    }
    else if (isupper(Data[i]))
    {
      Data[i] = tolower(Data[i]);
    }
    else
    {
      Data[i] = tolower(Data[i]);
    }
  }
}


// Function:    loading
// Description: Prints a "Loading..." message with 3 dots, one per second, to simulate a process taking time.
// Input param: None
// Return Type: void (No return value)
void loading()
{
  printf("Loading");
  for (int i = 0; i < 3; ++i)
  {

    sleep(1);
    printf(".");

  }
  printf("\n");
}



// Function:    creating
// Description: Prints a "Creating..." message with 3 dots, one per second, to simulate a process taking time.
// Input param: None
// Return Type: void (No return value)
void creating()
{
  printf("Creating");
  for (int i = 0; i < 3; ++i)
  {
    sleep(1);
    printf(".");
  }
  printf("\n");
}


// Function:    indexof
// Description: Finds the index of a given city in the 'City' array, based on its name.
// Input param: city: The name of the city to search for.
// Return Type: int
//              The index of the city in the array, if found.
//              -1, if the city is not found.
int indexof(char city[])
{
  // Iterate through the 'City' array
  for (int i = 0; i < pcount; ++i)
 {

    // Perform a case-insensitive comparison of the city names
    if (strcasecmp(city, City[i].placess) == 0)
    {
      // City found, return its index
      return City[i].pindex;
    }
  }
  // City not found, return -1
  return -1;
}




// Function:    Hashof
// Description: Calculates a simple hash value for a city name.
// Input param: city_name: The city name to hash.
// Return Type: int(The calculated hash value).
int Hashof(char city_name[])
{
  int hash = 0;  // Initialize hash value

  int k = strlen(city_name) - 1;  // Start with the exponent as the length of the string - 1

  for (int i = 0; i < strlen(city_name); ++i)
  {
    // Multiply the character code by 10 raised to the current exponent
    hash += (int)(city_name[i]) * pow(10, k);

    k--;  // Decrement the exponent for the next character
  }

  return hash;  // Return the calculated hash value
}




// Function:    isvalid
// Description: Checks if a given city name exists in the 'City' array of places.
// Input param: city_name: The name of the city to check.
// Return Type: int
//              1: If the city exists.
//              0: If the city does not exist.
int isvalid(char city_name[])
{

  // Calculate the hash value of the input city name
  int hash_value = Hashof(city_name);

  // Iterate through the 'City' array
  for (int i = 0; i < pcount; ++i)
 {

    // If the hash values match, perform a case-insensitive comparison
    if (hash_value == Hashof(City[i].placess))
    {
      if (strcasecmp(city_name, City[i].placess) == 0)
      {
        // City found, return 1
        return 1;
      }
    }
  }

  // City not found, return 0
  return 0;
}



// Function:    welcome
// Description: Prints a welcome message with a border of asterisks and a centered title.
// Input param: None
// Return Type: void (No return value)
void welcome()
{

  for (int i = 0; i < 80; i++)
  {
    printf("*");
  }

  printf("\n\n\t\t\t\tPathOptimizer\n\n\n");

  for (int i = 0; i < 80; i++)
  {
    printf("*");
  }
  printf("\n\n");
}

