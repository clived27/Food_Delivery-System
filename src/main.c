#include "../include/food_system.h"
int globalOrderID = 100;

int main() {
        struct Restaurent R[MAX_RESTO]; 
        int size = 0;                 

        load(R, &size, "data/restaurents.txt" );
        sortResto(R, size);             //Sort Restaurents

        for (int i = 0; i < size; i++) {
            sortFood(&R[i]);  //Sort food items
        }

        struct Date d;
        struct Time currentTime;
        int choice; 

            
            printf("Enter Date (DD MM YYYY)   : ");
            scanf("%d %d %d", &d.day,&d.month,&d.year);
            printf("Enter Current Time (HH MM): ");
            scanf("%d %d", &currentTime.hour, &currentTime.minute);
            printf("\n");
            timeConvert(&currentTime.hour, &currentTime.minute);


        do {
            printf("\n");
            
            printLine();
            printf("VNIT ONLINE FOOD MANAGEMENT SYSTEM\n");
            printLine();
    
            printf("  1. Customer Interface\n");                               
            printf("  2. Admin Interface\n");                          
            printf("  0. Exit\n");                                             
            printLine();
            
            printf("  Enter choice: "); 
            scanf("%d", &choice);                  

            if(choice == 1) {
                customerMenu(R, size, currentTime, d);                       
            }
            else if(choice == 2) {
                ownerMenu(R, &size, currentTime, d);                         
            }
            else if (choice == 0) {
                printf("\n  Thank you! Goodbye.\n");         
            }

        } 
        while (choice != 0);         

        return 0;                      
    }

