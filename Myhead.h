#ifndef MYHEAD_H_INCLUDED
#define MYHEAD_H_INCLUDED

// Including all the required header files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h>
#include <unistd.h>
#include <time.h>


#define MAX 999999
#define SIZE 100

//structure to store the data from the file.
struct list_of_city
{
    int pindex;
    char placess[100];
};

struct optimalroot
{
    char from[50];
    char destination[50];
    int distance;
};

struct places
{
    char place[100];
    char what[100];
    char rating[100];
};

struct tree {
    char place_name[100];
    struct tree *left;
    struct tree *right;
};

typedef struct optimalroot RD;
typedef struct places Place;
typedef struct list_of_city Cities;
typedef struct tree TREE;



// Function Declarations
void welcome();
void load_from_file();
void print();
void printPlaces();
void print_route();
void printmatrix();
int indexof(char city[]);
int Hashof(char city_name[]);
int isvalid(char city_name[]);
void convert_case(char Data[]);
void load_map();
void dijkstra(int nn, int Matrix[SIZE][SIZE], char sourceNode[30], char destNode[30]);
void sort();
void quicksort(int low, int high);
int partition(int low, int high);
void Find_location();
void dfs(int node, int size, int *Total_distance);
void SpanningTree(int size);
void addPlace();
void addroute();
void add_building();
void important_places();
void creating();
int check_for_importance(char* ratting);
void exit_function();
void closing();
void loading();
int bfss(int i, char pattern[], char city[]);
void Display_wrt_rating();
void its_speciality(char* location);
void findNearbyPlaces();
void bfs(int start_node, int size, int distance_limit);
void mergeSort(struct optimalroot routes[], int left, int right);
void merge(struct optimalroot routes[], int left, int right);
void dijkstra1(int nn, int Matrix[SIZE][SIZE], char sourceNode[30], char destNode[30], int remainingRoutes);
void rootfortrip();
TREE *insert_into_bst(TREE *root, char p_name[]);
void inorder(TREE *root);
TREE* load_from_file1(TREE *city_root);
int check_greatest(char place1[], char place2[]);
int floyd_warshall(int graph[100][100], int V, int source);
void nearest_place();
int check_greatest(char place1[], char place2[]);
void inorder(TREE *root);
void create_map();
void calculateAverageRating();
void calculate_city_avg();
void game();
void print_connected_cities(char cityname[30], int map[SIZE][SIZE]);
void check_and_print_connected_cities();



#endif // MYHEAD_H_INCLUDED
