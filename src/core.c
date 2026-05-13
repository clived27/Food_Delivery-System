#include "../include/food_system.h"


//Place ORDER 
 void placeOrder(struct Restaurent R[], int size, struct Time currentTime, struct Date d) {

        char rname[NAME_SIZE];    //Take input of restaurent name
        char foodName[NAME_SIZE]; // Food item name entered by user
        int  qty;                 // Qty needed by user

        printf("\n  Enter restaurent name : "); 
        scanf(" %[^\n]", rname);   


        int idx = findRestaurent(rname, R, size); //Find Restaurent- Return index
        
        //Restaurent Not Found
        if (idx == -1) {                                                     
            printf("  SORRY! restaurent '%s' not found. Going back to menu.\n", rname);
        }

        //Restaurent Found
        else {

        printf("  Enter food item name: "); 
        scanf(" %[^\n]", foodName);   
        printf("  Enter quantity: "); 
        scanf("%d", &qty);             

        struct FoodItem item = search_foo(R[idx], foodName); //Search a Food Item in The restaurent                 

        //Food Item Not Available
        if (item.quantity == -1) {                                           
            printf("  SORRY! '%s' is not available at %s. Going back to menu.\n", foodName, rname);                                                          
        }

        //Food Item Available
        else {

            //Required Quantity is not Available
            if (item.quantity < qty) {                                          
                printf("  SORRY! Only %d quantity of '%s' available at %s. Going back to menu.\n",item.quantity, foodName, rname);                                               
            }

            //Required Quantity is Available
            else{

            char uname[NAME_SIZE]; 
            long long phone;       
            int  plot;             
            char area[NAME_SIZE];  


            printf(" Enter your name: "); 
            scanf(" %[^\n]", uname);      
            printf(" Enter phone number: "); 
            scanf("%lld", &phone);         
            printf(" Enter your plot no: "); 
            scanf("%d", &plot);            
            printf(" Enter your area: "); 
            scanf(" %[^\n]", area);        
        
            
            struct user newOrder; //Making a temporary variable of struct User to put it in the live order of restaurent
            
            //Date and Time
            newOrder.order_time = currentTime;
            newOrder.order_date.day = d.day;
            newOrder.order_date.month = d.month;
            newOrder.order_date.year= d.year;


            //Username, Phone no, Address
            strcpy(newOrder.username, uname);
            newOrder.phone_no = phone;                                           
            newOrder.user_address.plot_no = plot;                                
            strcpy(newOrder.user_address.AreaName, area);

            //Details of Food Item
            newOrder.ordered = item;                                            
            newOrder.ordered.quantity = qty;                                     
            newOrder.ordered.foodCost = item.foodCost * qty; 
            
            //Expected Delivery Time
            newOrder.expected = addTime(currentTime, addTime(item.t, R[idx].DeliveryTime)); //Adds time
            strcpy(newOrder.rest_name, R[idx].Resto_Name);                     
            newOrder.orderID = globalOrderID++;  //Unique Order id 


            // Adding order to restaurent's live record
            if(R[idx].liveCount>=MAX_ORDERS){
                printf("Sorry this Restaurant Can't Accept anymore Orders!\n");
            }
            else{
                 R[idx].liveRecord[R[idx].liveCount++] = newOrder; 
                sortLiveOrders(&R[idx]);   //Keep live orders sorted
            
           


            // Deduct ordered quantity from restaurent 
            //Since All food items are sorted, we can use Binary Search
            
            //Special Food Item
            if(strcmp(R[idx].Sp_Day.foodName, item.foodName)==0) {
                R[idx].Sp_Day.quantity-=qty;
            }

            else {
                int st=0, end=R[idx].gen_food_items-1;
                int find=0;

                while(st<=end && find==0) {
                    int mid=st+ (end-st)/2;

                    if(strcmp(R[idx].Generic[mid].foodName,item.foodName)==0) {
                        R[idx].Generic[mid].quantity-=qty;
                        find=1;        
                    }
                    else if(strcmp(R[idx].Generic[mid].foodName,item.foodName)>0) {
                        end=mid-1;
                    }
                    else {
                        st=mid+1;
                    }
                }
            

            st=0, end=R[idx].spl_food_items-1;
            while(st<=end && find==0) {
                int mid=st+(end-st)/2;

                    if(strcmp(R[idx].Special[mid].foodName,item.foodName)==0) {
                        R[idx].Special[mid].quantity-=qty;
                        find=1;
                    }

                    else if(strcmp(R[idx].Special[mid].foodName,item.foodName)>0) {
                        end=mid-1;
                    }

                    else {
                        st=mid+1;
                    }
                }
            }   
        
                // Print Order Confirmation
                printLine();
                printf("ORDER PLACED SUCCESSFULLY!\n");
                printLine();
                printf("Date        :%d/%d/%d\n", newOrder.order_date.day, newOrder.order_date.month, newOrder.order_date.year);
                printf("Order ID    : %d\n", newOrder.orderID);                 
                printf("restaurent  : %s\n", R[idx].Resto_Name);                
                printf("Item        : %s x%d\n", foodName, qty);                   
                printf("Total Cost  : Rs %f\n", newOrder.ordered.foodCost);      
                printf("Expected By : %d : %d \n", newOrder.expected.hour, newOrder.expected.minute);            
                printLine();
            }
            }
        }
        }
    }


     // Prints all restaurents with their address and delivery time 
    void printAllrestaurents(struct Restaurent R[], int size) {
        printLine();
        printf("  Restaurents Available\n");                                   
        printLine();

        for (int i = 0; i < size; i++) {                                       
            printf("  %d) %s |Plot %d , %s | Delivery Time: %d hr %d min\n",i+1,R[i].Resto_Name,R[i].add.plot_no,R[i].add.AreaName,R[i].DeliveryTime.hour,R[i].DeliveryTime.minute);                                  
        }

        printLine();
    }


     //a) Get Restaurent that delivers in minimum time
    void getMinTime(char food[], int qt, struct Restaurent R[], int size) {
        struct Time minTime;     //Stores minimum time      
        minTime.hour   = INT_MAX;      
        minTime.minute = INT_MAX;      
        int resto_number = -1;         //Index of found restaurent
        struct FoodItem searched;      
        struct Time total;
        
        for (int i = 0; i < size; i++) {                          
            searched = search_foo(R[i], food); //Searches whether the required food item is available or not                    
            if (searched.quantity >= qt) {

                    total = addTime(searched.t, R[i].DeliveryTime); 
                
                if (compareTimes(total, minTime) ==-1 ) {           
                    minTime      = total;                         
                    resto_number = i;                             
                }
            }
        }


        printLine();
        if (resto_number == -1) {                                 // No restaurent found with sufficient quantity
            printf("  SORRY! %d quantity of '%s' is not available in any restaurent.\n", qt, food);
        } 
        else {
            printf("FASTEST DELIVERY restaurent\n");
            printLine();
            printf("Restaurent   : %s\n", R[resto_number].Resto_Name);                              
            printf("Address      : Plot No-%d, %s\n", R[resto_number].add.plot_no,R[resto_number].add.AreaName);                                                   
            printf("Time         : %d hr %d min\n", minTime.hour, minTime.minute);                  
        }

        printLine();

    }


      //2) Checks if the item is available
    //If yes, prints which restaurents has it
    void getItemAvailability(char food[], struct Restaurent Original[], int size) {
        int status = 0; //checks if at least one restaurent has the required food item
        int count  = 0; //number of restaurents having the dish
        struct FoodItem searched;

        printLine();
        printf("Availability of: %s\n", food); 
        printLine();

        for (int i = 0; i < size; i++) {                                     
             searched = search_foo(Original[i], food);        
            if (searched.quantity != -1) {                                   
                count++;                                                     
                printf("  %d) %s  Rs %f  (Available Qty: %d)\n",count, Original[i].Resto_Name, searched.foodCost, searched.quantity);
                status = 1;                                                  
            }
        }

        if (status == 0) {                                                   
            printf("  SORRY! '%s' is not available in any restaurent.\n", food);
        }
        printLine();
    }


    //4) Prints all the dishes of a restaurent in alphabetical order
    void getItemListInSortedOrder_Food(struct Restaurent R) {
        
        int genSize=R.gen_food_items;
        int splSize=R.spl_food_items;
        int i=0, j=0, count=1;
        int flag=0; //To Check Whether Special Item of the Day is merged or not

        while(i<genSize && j<splSize) {
            if(strcmp(R.Generic[i].foodName,R.Special[j].foodName)<0) {
                if(flag==0) {
                    if(strcmp(R.Generic[i].foodName, R.Sp_Day.foodName)<0) {
                        printf("%d) %s\n", count++, R.Generic[i].foodName);
                        printf(     "Price: %f\n\n", R.Generic[i].foodCost);
                    }
                    else {
                        printf("%d) %s\n", count++, R.Sp_Day.foodName);
                        printf(     "Price: %f\n\n", R.Sp_Day.foodCost);
                        printf("%d) %s\n", count++, R.Generic[i].foodName);
                        printf(     "Price: %f Rs\n\n", R.Generic[i].foodCost);
                        flag=1;
                    }
                }
                else {
                    printf("%d) %s\n", count++, R.Generic[i].foodName);
                    printf(     "Price: %f\n\n", R.Generic[i].foodCost);
                }
                i++;
            }
            else {
                if(flag==0) {
                    if(strcmp(R.Special[j].foodName, R.Sp_Day.foodName)<0) {
                        printf("%d) %s\n", count++, R.Special[j].foodName);
                        printf("    Price: %f Rs\n\n", R.Special[j].foodCost);
                    }
                    else {
                        printf("%d) %s\n", count++, R.Sp_Day.foodName);
                        printf("    Price: %f Rs\n\n", R.Sp_Day.foodCost);

                        printf("%d) %s\n", count++, R.Special[j].foodName);
                        printf("    Price: %f Rs\n\n", R.Special[j].foodCost);
                        flag=1;
                    }
                }
                else {
                        printf("%d) %s\n", count++, R.Special[j].foodName);
                        printf("    Price: %f Rs\n\n", R.Special[j].foodCost);
                }
                j++;
            }
        }


        while(i<genSize) {
            if(flag==0) {
                if(strcmp(R.Generic[i].foodName, R.Sp_Day.foodName)<0) {
                    printf("%d) %s\n", count++, R.Generic[i].foodName);
                    printf("    Price: %f Rs\n\n", R.Generic[i].foodCost);
                }

                else {
                    printf("%d) %s\n", count++, R.Sp_Day.foodName);
                    printf("    Price: %f Rs\n\n", R.Sp_Day.foodCost);
                    
                    printf("%d) %s\n", count++, R.Generic[i].foodName);
                    printf("    Price: %f Rs\n\n", R.Generic[i].foodCost);
                    flag=1;
                }
                
            }
            else {
                printf("%d) %s\n", count++, R.Generic[i].foodName);
                printf("    Price: %f Rs\n\n", R.Generic[i].foodCost);
            }

            i++;
        }
        

        
        while(j<splSize) {
            if(flag==0) {
                if(strcmp(R.Special[j].foodName, R.Sp_Day.foodName)<0) {
                    printf("%d) %s\n", count++, R.Special[j].foodName);
                    printf("    Price: %f Rs\n\n", R.Special[j].foodCost);
                }
                else {
                    printf("%d) %s\n", count++, R.Sp_Day.foodName);
                    printf("    Price: %f Rs\n\n", R.Sp_Day.foodCost);

                    printf("%d) %s\n", count++, R.Special[j].foodName);
                    printf("    Price: %f Rs\n\n", R.Special[j].foodCost);
                    flag=1;
                }
            }
            else {
                printf("%d) %s\n", count++, R.Special[j].foodName);
                printf("    Price: %f Rs\n\n", R.Special[j].foodCost);
            }
            j++;
        
        }

        if(flag == 0) {
            printf("%d) %s\n", count++, R.Sp_Day.foodName);
            printf("    Price: %f Rs\n\n", R.Sp_Day.foodCost);
        }
    }


     //5) Print all items of a restaurent in Descending order of prices
      void getItemListInSortedOrder_Prices(struct Restaurent R) { 
                    
        mergesortPrice(R.Generic, 0,R.gen_food_items-1);
        mergesortPrice(R.Special, 0,R.spl_food_items-1);

        int genSize=R.gen_food_items;
        int splSize=R.spl_food_items;
        int i=0, j=0, count=1;
        int flag=0; //To Check Whether Special Item of the Day is merged or not

        while(i<genSize && j<splSize) {
            if(R.Generic[i].foodCost>R.Special[j].foodCost) {
                if(flag==0){
                    if(R.Generic[i].foodCost>R.Sp_Day.foodCost) {
                        printf("%d) %s\n", count++, R.Generic[i].foodName);
                        printf("Price: %f Rs\n\n", R.Generic[i].foodCost);
                    }
                    else {
                        printf("%d) %s\n", count++, R.Sp_Day.foodName);
                        printf("Price: %f Rs\n\n", R.Sp_Day.foodCost);

                        
                        printf("%d) %s\n", count++, R.Generic[i].foodName);
                        printf("Price: %f Rs\n\n", R.Generic[i].foodCost);

                        flag=1;
                    }
                }
                else {
                        printf("%d) %s\n", count++, R.Generic[i].foodName);
                        printf("Price: %f Rs\n\n", R.Generic[i].foodCost);
                }
                i++;
            }
            else {
                if(flag==0){
                    if(R.Special[j].foodCost>R.Sp_Day.foodCost) {
                        printf("%d) %s\n", count++, R.Special[j].foodName);
                        printf("Price: %f Rs\n\n", R.Special[j].foodCost);
                    }
                    else {
                        printf("%d) %s\n", count++, R.Sp_Day.foodName);
                        printf("Price: %f Rs\n\n", R.Sp_Day.foodCost);

                        
                        printf("%d) %s\n", count++, R.Special[j].foodName);
                        printf("Price: %f Rs\n\n", R.Special[j].foodCost);

                        flag=1;
                    }
                }
                else {
                        printf("%d) %s\n", count++, R.Special[j].foodName);
                        printf("Price: %f Rs\n\n", R.Special[j].foodCost);   
                }
                j++;
                
            }
        }

        while(i<genSize) {
            if(flag==0) {
                if(R.Generic[i].foodCost>R.Sp_Day.foodCost) {
                    printf("%d) %s\n", count++, R.Generic[i].foodName);
                    printf("Price: %f Rs\n\n", R.Generic[i].foodCost);
                }
                else {
                    printf("%d) %s\n", count++, R.Sp_Day.foodName);
                    printf("Price: %f Rs\n\n", R.Sp_Day.foodCost);

                    
                    printf("%d) %s\n", count++, R.Generic[i].foodName);
                    printf("Price: %f Rs\n\n", R.Generic[i].foodCost);

                    flag=1;
                }
                
            }
            else {
                printf("%d) %s\n", count++, R.Generic[i].foodName);
                printf("Price: %f Rs\n\n", R.Generic[i].foodCost);
            }

            i++;
        }
        

        
        while(j<splSize) {
            if(flag==0) {
                if(R.Special[j].foodCost>R.Sp_Day.foodCost) {
                    printf("%d) %s\n", count++, R.Special[j].foodName);
                    printf("Price: %f Rs\n\n", R.Special[j].foodCost);
                }
                else {
                    printf("%d) %s\n", count++, R.Sp_Day.foodName);
                    printf("Price: %f Rs\n\n", R.Sp_Day.foodCost);

                    
                    printf("%d) %s\n", count++, R.Special[j].foodName);
                    printf("Price: %f Rs\n\n", R.Special[j].foodCost);

                    flag=1;
                }
                
            }
            else {
                printf("%d) %s\n", count++, R.Special[j].foodName);
                printf("Price: %f Rs\n\n", R.Special[j].foodCost);
            }

            j++;
        }
        if(flag==0){
             printf("%d) %s\n", count++, R.Sp_Day.foodName);
             printf("Price: %f Rs\n\n", R.Sp_Day.foodCost);
        }

    }


    //6) For a given area, print food items of all restaurents in that area sorted by restaurent name
    void getItemListInAreaSortedOrder(char area[], struct Restaurent Original[], int size) {

        int count = 0;                           // Count of restaurents found in the area

        printLine();
        printf("  restaurents in Area: %s\n", area);
        printLine();

        for (int i = 0; i < size; i++) {         
            if (strcmp(Original[i].add.AreaName, area) == 0) { 
                count++;               
            printf("\n  [%d] %s  (Plot %d)\n", count, Original[i].Resto_Name, Original[i].add.plot_no);
            getItemListInSortedOrder_Food(Original[i]);
            }
        }

     
        if (count == 0) {                        
            printf("  SORRY! No restaurents found in '%s'.\n", area);
            printLine();
        
        }

        printLine();
    }
    

    //7) Prints all the special items in all restaurents
    void getAllSpecialItemListinSortedOrder(struct Restaurent R[], int size) {
        int total = 0;   // Total number of special items across all restaurents
        for (int i = 0; i < size; i++) {
            total += R[i].spl_food_items; 
        }

        struct FoodItem allSpecial[MAX_RESTO*MAX_FOOD_ITEM];       
        int idxResto[MAX_RESTO*MAX_FOOD_ITEM];                  
        int count = 0;

        for (int i = 0; i < size; i++) {         
            for (int j = 0; j < R[i].spl_food_items; j++) { 
                allSpecial[count] = R[i].Special[j];         // Copy item into combined array
                idxResto[count++] = i;                       // Record which restaurent it belongs to: to print its name and address
           }
        }
        // Bubble sort
        for (int i = 0; i < total - 1; i++) {
            for (int j = 0; j < total - i - 1; j++) {
                if (strcmp(allSpecial[j].foodName, allSpecial[j+1].foodName) > 0) {
                    struct FoodItem tmpF = allSpecial[j]; 
                    allSpecial[j] = allSpecial[j+1]; 
                    allSpecial[j+1] = tmpF; 

                    int tmpI = idxResto[j]; 
                    idxResto[j] = idxResto[j+1]; 
                    idxResto[j+1] = tmpI;                    // Swap restaurent indices
                }
            }
        }


        printLine();
        printf("  ALL SPECIAL ITEMS (Sorted by Name)\n");
        printLine();
        
        for (int i = 0; i < total; i++) {        
            printf("  %d) %s Rs %f\n", i+1, allSpecial[i].foodName, allSpecial[i].foodCost); 
            printf("restaurent: %s, Plot %d, %s\n\n",R[idxResto[i]].Resto_Name,R[idxResto[i]].add.plot_no,R[idxResto[i]].add.AreaName);                             
        }
        printLine();
    }


     //8) Prints item of the day for all restaurents in a given area
      void getItemofDayListinSortedOrder(char area[], struct Restaurent Original[], int size) {
        struct Restaurent areaR[MAX_RESTO]; // restaurents in the given area
        int count = 0;                      // Count of matching restaurents

        for (int i = 0; i < size; i++) {    
            if (strcmp(Original[i].add.AreaName, area) == 0) { 
                areaR[count++] = Original[i];                    
            }
        }
        if (count == 0) {                   // No restaurents found in this area
            printf("  No restaurents found in '%s'.\n", area);
        }
        else {
            mergeSortItem(areaR,0,count-1);

            printLine();
            printf("  ITEMS OF THE DAY in Area: %s\n", area); 
            printLine();

            
            for (int i = 0; i < count; i++) {   
                printf("%d) %s Rs %f  | %s\n", i+1,areaR[i].Sp_Day.foodName, areaR[i].Sp_Day.foodCost, areaR[i].Resto_Name);
            }
        }
        printLine();
    }

    //9 Get Common Items
     void getCommonItem(struct Restaurent R[], int size) {
        
        struct Restaurent one = R[0];       // Reference restaurent to start comparison from
        char candidates[MAX_FOOD_ITEM * 2 +1][NAME_SIZE]; // Array of candidate item names
        int  candCount = 0;                  

        // Collect all item names from the one restaurent
        for (int i = 0; i < one.gen_food_items; i++) {
            strcpy(candidates[candCount++], one.Generic[i].foodName);
        } 
        for (int i = 0; i < one.spl_food_items; i++){
            strcpy(candidates[candCount++], one.Special[i].foodName); // Special items
        }
        
        strcpy(candidates[candCount++], one.Sp_Day.foodName);             // Item of the day

        // Sort items alphabetically
        mergeSortCommon(candidates, 0, candCount-1);
        
        printLine();
        printf("  COMMON ITEMS across ALL restaurents\n");
        printLine();
        int found = 0;                       // Flag: at least one common item found

        for (int c = 0; c < candCount; c++) { 
            int common = 1;                   
            for (int r = 1; r < size && common==1; r++) {  

                struct FoodItem fi = search_foo(R[r], candidates[c]); 
                if (fi.quantity == -1) { 
                    common = 0; 
                }         
                    
            }

            if (common==1) {                     // Item is present in all restaurents
                found = 1;              

                printf("  Item: %s\n", candidates[c]); 
            
                for (int r = 0; r < size; r++) {        // Print price at each restaurent
                    struct FoodItem fi = search_foo(R[r], candidates[c]);
                    printf("    %s Rs %f\n", R[r].Resto_Name, fi.foodCost); 
                }
                printf("\n");
            }
        }

        if (found==0) {
            printf("  No common items found across all restaurents.\n"); 
        } 
        printLine();
    }


    
    //10) Get Unique Item
    void getAllUniqueItem(struct Restaurent R[], int size) {
        printLine();
        printf("  UNIQUE ITEMS per restaurent\n");
        printLine();

        for (int r = 0; r < size; r++) {   
            char candidates[MAX_FOOD_ITEM * 2 +1][NAME_SIZE]; // Array of candidate item names
            int  candCount = 0;                  

            // Collect all item names from the rth restaurent
            for (int i = 0; i < R[r].gen_food_items; i++) {
                strcpy(candidates[candCount++], R[r].Generic[i].foodName);
            }    
            for (int i = 0; i < R[r].spl_food_items; i++){
                strcpy(candidates[candCount++], R[r].Special[i].foodName); // Special items
            }
        
            strcpy(candidates[candCount++], R[r].Sp_Day.foodName);             // Item of the day

             // Sort items alphabetically
            mergeSortCommon(candidates, 0, candCount-1);

            int printedHeader = 0;           // Flag: restaurent header printed for this restaurent
            for (int i = 0; i < candCount; i++) { 
                struct FoodItem fi;
                int unique = 1;              // Assume unique until found in another restaurent

                for (int other = 0; other < size && unique==1 && other!=r ; other++) { // Check all other restaurents
                
                    fi= search_foo(R[other], candidates[i]); // Search in other restaurent
                    
                    if (fi.quantity != -1) { 
                        unique = 0; 
                    }                 //Not unique
            }

                    if (unique) {                // Item is unique to this restaurent 
                        struct FoodItem found=search_foo(R[r], candidates[i]);
                        if (!printedHeader) {    //If multiple unique elements are there in the same restaurent, print the restaurent only once    
                        printf("\n  [%s]  Plot %d, %s\n",R[r].Resto_Name, R[r].add.plot_no, R[r].add.AreaName);
                        printedHeader = 1;
                        }
                    printf("    %s Rs %f\n", candidates[i],found.foodCost);
                    }
                }
            }
            printLine();

        }


