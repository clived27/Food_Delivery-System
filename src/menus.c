#include "../include/food_system.h"

  
    void postResultPrompt(struct Restaurent R[], int size, struct Time currentTime, struct Date d) {
        int sub;                                                             
        printf("\n  1. Place Order\n"); 
        printf("  0. Go Back\n"); 
        printf("  Enter choice: "); 
        scanf("%d", &sub); 

        if (sub == 1) {                                                      
            placeOrder(R, size, currentTime, d);                                
        }
    }



        // Prints full details of a single restaurent including all menu categories - Used for OWNER
    void displayrestaurent(struct Restaurent R) {
        printLine();
        printf("  restaurent : %s\n", R.Resto_Name);                                    
        printf("  Address    : Plot %d, %s\n", R.add.plot_no, R.add.AreaName);          
        printf("  Delivery   : %d hr %d min overhead\n", R.DeliveryTime.hour, R.DeliveryTime.minute); 
        
        printf("\n  --- Generic Items ---\n");
        for (int i = 0; i < R.gen_food_items; i++) {                                    // Print each generic item
            printf("  %s Rs %f  (Qty: %d, Prep: %dh%dm)\n",R.Generic[i].foodName, R.Generic[i].foodCost,R.Generic[i].quantity, R.Generic[i].t.hour, R.Generic[i].t.minute);
        }

        printf("\n  --- Special Items ---\n");
        for (int i = 0; i < R.spl_food_items; i++) {                                    // Print each special item
            printf("  %s Rs %f  (Qty: %d, Prep: %dh%dm)\n",R.Special[i].foodName, R.Special[i].foodCost,R.Special[i].quantity, R.Special[i].t.hour, R.Special[i].t.minute);
        }

        printf("\n  --- Item of the Day ---\n");
        printf("  %s Rs %f  (Qty: %d, Prep: %dh%dm)\n", R.Sp_Day.foodName, R.Sp_Day.foodCost,R.Sp_Day.quantity, R.Sp_Day.t.hour, R.Sp_Day.t.minute);
        printLine();
    }



    // Prints all live/active orders of a restaurent in sorted order - Used for OWNER
    void displayLiveOrders(struct Restaurent R) {
        printLine();
        printf("  LIVE ORDERS for %s\n", R.Resto_Name);                                 
        printLine();

        if (R.liveCount == 0) {                                                          
            printf("  No active orders.\n");
            printLine();
        }
        else {
        for (int i = 0; i < R.liveCount; i++) {                                        
            
            struct user u = R.liveRecord[i];                                             
            
            printf("  OrderID: %d | %s | %s x%d | Rs %f\n",u.orderID, u.username, u.ordered.foodName, u.ordered.quantity, u.ordered.foodCost);                              
            printf("  Ordered at: %dh%dm | Expected: %dh%dm\n\n",u.order_time.hour, u.order_time.minute,u.expected.hour, u.expected.minute);                                  
        }
        printLine();
        }
        return;
    }




    // CUSTOMER INTERFACE
    void customerMenu(struct Restaurent R[], int size, struct Time currentTime, struct Date d) {
        int choice;               
        char foodName[NAME_SIZE]; 
        int  qty;                 
        char area[NAME_SIZE];     
        char rname[NAME_SIZE];      

    

        do {
            printf("\n");
            printAllrestaurents(R, size);      // Print all restaurents before showing menu
            printLine();
            printf("  CUSTOMER MENU\n");
            printLine();
            printf("  1. Find fastest restaurent for a food item\n");          
            printf("  2. Check where a food item is available\n");             
            printf("  3. Browse menu of a restaurent (by name A-Z)\n");        
            printf("  4. Browse menu of a restaurent (by price high-low)\n");  
            printf("  5. Browse all restaurents in an area\n");                
            printf("  6. View items of the day in an area\n");                 
            printf("  7. Common items across ALL restaurents\n");             
            printf("  8. Unique items per restaurent\n");    
            printf("  9. Get all Special Items in the Restaurents\n");                  
            printf("  0. Back to Main Menu\n");                                
            printLine();
            printf("  Enter choice: "); scanf("%d", &choice);                  // Read user choice

            if (choice == 1) {
                printf("  Enter food item : "); 
                scanf(" %[^\n]", foodName);    
                printf("  Enter quantity  : "); 
                scanf("%d", &qty);             

                getMinTime(foodName, qty, R, size);                            
                postResultPrompt(R, size, currentTime, d);                        // Show place order / go back

            }
            else if (choice == 2) {
                printf("  Enter food item : "); 
                scanf(" %[^\n]", foodName);    
                getItemAvailability(foodName, R, size);                        
                postResultPrompt(R, size, currentTime, d);                        // Show place order / go back

            } 
            else if (choice == 3) {
                printf("  Enter restaurent name: "); 
                scanf(" %[^\n]", rname); 

                int index=findRestaurent(rname, R, size);                                                 

                if (index==-1) {
                    printf("  Restaurent not found.\n");              
                }
                else {
                    getItemListInSortedOrder_Food(R[index]);
                }

                postResultPrompt(R, size, currentTime, d);                        // Show place order / go back

            } 
            else if (choice == 4) {
                
                printf("  Enter restaurent name: "); 
                scanf(" %[^\n]", rname); 
                
                int index=findRestaurent(rname, R, size);

                if (index==-1) {
                    printf("  restaurent not found.\n");              
                }
                else {
                    getItemListInSortedOrder_Prices(R[index]);
                }

                postResultPrompt(R, size, currentTime,d);                        

            }
            else if (choice == 5) {
                
                printf("  Enter area name: "); 
                scanf(" %[^\n]", area);        
                getItemListInAreaSortedOrder(area, R, size);                   
                postResultPrompt(R, size, currentTime,d);                        

            }
            else if (choice == 6) {
                printf("  Enter area name: "); scanf(" %[^\n]", area);        
                getItemofDayListinSortedOrder(area, R, size);                 
                postResultPrompt(R, size, currentTime,d);                       
            }
            
            else if (choice == 7) {
                getCommonItem(R, size);                                        
                postResultPrompt(R, size, currentTime,d);                       

            } 
            
            else if (choice == 8) {
                
                getAllUniqueItem(R, size);                                      
                postResultPrompt(R, size, currentTime,d);                        
            }
            else if (choice==9) {
                getAllSpecialItemListinSortedOrder(R,size);
                postResultPrompt(R, size, currentTime,d);
            }

        } while (choice != 0);              
    }



    //OWNER 
    void ownerMenu(struct Restaurent R[], int *size, struct Time currentTime, struct Date d) {
        int choice;            // Menu choice variable
        char rname[NAME_SIZE]; // restaurent name input
        char area[NAME_SIZE];  // Area name input    

        do {
            printf("\n");
            printAllrestaurents(R, *size);      // Print all restaurents before showing menu
            printLine();
            printf("ADMIN PANEL\n");
            printLine();
            printf("  1. View full menu of a restaurent\n");                   
            printf("  2. View live orders of a restaurent\n");
            printf("  3. Add A Restaurent\n");                
            printf("  0. Back to Main Menu\n");                                
            printLine();
            printf("  Enter choice: "); 
            scanf("%d", &choice);                  


            if (choice == 1) {
                printf("  Enter restaurent name: "); 
                scanf(" %[^\n]", rname); 
                int index = findRestaurent(rname, R, *size);                                                 
                    
                if (index==-1){
                    printf("  Restaurent not found.\n");              
                }
                else {
                    displayrestaurent(R[index]);
                }
                            

            } 
            else if (choice == 2) {
                printf("  Enter restaurent name: "); {
                    scanf(" %[^\n]", rname); // Read restaurent name
                }
                int index = findRestaurent(rname, R, *size);                                                 
            
                if (index==-1){
                    printf("  restaurent not found.\n");              // Not found message
                }
                else {
                    displayLiveOrders(R[index]);
                }
                            

            }
            else if (choice == 3) {
                if(*size>=MAX_RESTO) {
                    printf("Maximum Restaurent Limit Reached\n");
                }
                else {
                //Declare a new Restaurent and fill it with user input
                struct Restaurent newR;
                newR.liveCount = 0; //No live orders initially

                //Read Restaurent Name
                printf("Enter the Name of the Restaurent        : ");
                scanf(" %[^\n]", newR.Resto_Name);

                //Read Address
                printf("Enter Plot Number                       : ");
                scanf("%d", &newR.add.plot_no);
                printf("Enter Area Name                         : ");
                scanf(" %[^\n]", newR.add.AreaName);

                //Read Delivery Time 
                printf("Enter Delivery Time (HH MM)         : ");
                scanf("%d %d", &newR.DeliveryTime.hour, &newR.DeliveryTime.minute);

                //Read Generic Food Items
                printf("Enter the Number of Generic Food Items  : ");
                scanf("%d", &newR.gen_food_items);
                for (int i = 0; i < newR.gen_food_items; i++) {
                    printf("  Generic Item %d Name     : ", i+1);
                    scanf(" %[^\n]", newR.Generic[i].foodName);
                    printf("  Generic Item %d Quantity : ", i+1);
                    scanf("%d", &newR.Generic[i].quantity);
                    printf("  Generic Item %d Price    : ", i+1);
                    scanf("%f", &newR.Generic[i].foodCost);
                    printf("  Generic Item %d Prep Time (HH MM): ", i+1);
                    scanf("%d %d", &newR.Generic[i].t.hour, &newR.Generic[i].t.minute);
                }

                //Read Special Food Items
                printf("Enter the Number of Special Food Items  : ");
                scanf("%d", &newR.spl_food_items);
                for (int i = 0; i < newR.spl_food_items; i++) {
                    printf("  Special Item %d Name     : ", i+1);
                    scanf(" %[^\n]", newR.Special[i].foodName);
                    printf("  Special Item %d Quantity : ", i+1);
                    scanf("%d", &newR.Special[i].quantity);
                    printf("  Special Item %d Price    : ", i+1);
                    scanf("%f", &newR.Special[i].foodCost);
                    printf("  Special Item %d Prep Time (HH MM): ", i+1);
                    scanf("%d %d", &newR.Special[i].t.hour, &newR.Special[i].t.minute);
                }

                //Read Item of the Day
                printf("Enter Item of the Day Name              : ");
                scanf(" %[^\n]", newR.Sp_Day.foodName);
                printf("Enter Item of the Day Quantity          : ");
                scanf("%d", &newR.Sp_Day.quantity);
                printf("Enter Item of the Day Price             : ");
                scanf("%f", &newR.Sp_Day.foodCost);
                printf("Enter Item of the Day Prep Time (HH MM): ");
                scanf("%d %d", &newR.Sp_Day.t.hour, &newR.Sp_Day.t.minute);

                //Add the new Restaurent to the array and re-sort
                R[*size] = newR;
                sortFood(&R[*size]);

                (*size)++;
                
                sortResto(R, *size);          //Re-sort after adding
                            
                saveToFile(R, *size, "restaurents.txt");
                printf("  Restaurent '%s' added successfully!\n", newR.Resto_Name);

                }
            } 
        } while (choice != 0);              
    }



    