#ifndef LOCALS_H_INCLUDED
#define LOCALS_H_INCLUDED

//stores the City name and its index
Cities City[200];

//Stores the root information in it.
RD route[200];

//store the place_type and their ratting with the location.
Place places[200];

int map[100][100];
int global_count = 0;
int pcount = 0;
int places_count = 0;
int visited[SIZE];
char trip[MAX];



#endif // LOCALS_H_INCLUDED
