#include "MYhead.c"
#include "Locals.h"

int main()
{
    welcome();
    load_from_file();
    char source[30];
    char destination[30];
    TREE *city_root = NULL;
    while (1) {

       printf("-------------------------------------------------------\n");
       printf("\n\t\tMENU\n");
       printf("-------------------------------------------------------\n");
       printf("\n1. Display City List\n");
       printf("2. Explore Routes\n");
       printf("3. Plan Your Trip\n");
       printf("4. Search for a Place\n");
       printf("5. View City Connections\n");
       printf("6. Add a City\n");
       printf("7. Add a Route\n");
       printf("8. Register a Building\n");
       printf("9. Discover Key Locations\n");
       printf("10. Find Top-Rated Buildings\n");
       printf("11. Discover best neighborhood hangout cities\n");
       printf("12. Plot the Most Efficient Journey\n");
       printf("13. Find the Closest City\n");
       printf("14. Create your own customized map\n");
       printf("15. Calculate Overall and City-wise Average Rating\n");
       printf("16. Play game in traffic\n");
       printf("17. Display the directly connected route for the city\n");
       printf("18. Exit Program\n");
       printf("--------------------------------------------------------\n");
        int case_choice;
        printf("\nEnter your choice: ");
        scanf("%d", &case_choice);
        printf("\n");
        load_map();

        switch (case_choice)
        {
            case 1:
                city_root = load_from_file1(city_root);
                inorder(city_root);
                break;

            case 2:
                print_route();
                break;

            case 3:
                printf("Enter source:");
                scanf("%s", source);
                printf("Enter Destination:");
                scanf("%s", destination);
                convert_case(source);
                convert_case(destination);
                if (isvalid(source) && isvalid(destination))
                {
                    dijkstra(global_count, map,source, destination);
                    loading();
                }
                else
                {
                      printf("\nIncorrect source or destination\n");
                }
                break;

            case 4:
                Find_location();
                loading();
                break;

            case 5:
                creating();
                SpanningTree(global_count);
                break;

            case 6:
                 addPlace();
                 break;

            case 7:
                 addroute();
                 loading();
                 break;

            case 8:
                 add_building();
                 creating();
                 break;

            case 9:
                 important_places();
                 break;

            case 10:
                  Display_wrt_rating();
                  break;

            case 11:
                  findNearbyPlaces();
                  break;

            case 12:
                  rootfortrip();
                  break;

            case 13:
                  nearest_place();
                  break;

            case 14:
                  create_map();
                  break;

            case 15:
                  calculateAverageRating();
                  break;

            case 16:
                  game();
                  break;

            case 17:
                 check_and_print_connected_cities();
                 break;

            case 18:
                  exit(0);
                  break;

            default:
                printf("\nInvalid Data\n");

        }
    }

    return 0;
}
