#include<stdio.h>    
#include<string.h>   
#include<limits.h> 

#define NAME_SIZE 50     
#define MAX_FOOD_ITEM 50   
#define MAX_RESTO 25   
#define MAX_ORDERS 100

    struct Time {
        int hour;    
        int minute;  
    };

    struct Date {
        int day;
        int month;
        int year;
    };

    struct Address {
        int  plot_no;             
        char AreaName[NAME_SIZE]; 
    };


    struct FoodItem {
        char foodName[NAME_SIZE]; 
        int quantity;            
        float foodCost;            
        struct Time t;  //Time of Prepartion
    };



    struct user {
        struct Time order_time;  
        struct Date order_date;        
        char username[NAME_SIZE];  
        long long phone_no;             
        struct Address user_address;         
        struct FoodItem ordered;             
        struct Time expected;           //Expected Time= Current Time + (Service Time of a food item + Deliver time of the restaurent)  
        char rest_name[NAME_SIZE]; 
        int orderID;             
    };


    struct Restaurent {
        char Resto_Name[NAME_SIZE];     
        int gen_food_items;            //Count of the Generic Food items
        int spl_food_items;            //Count of the Special Food items 
        struct FoodItem Generic[MAX_FOOD_ITEM];    //Generic Food items
        struct FoodItem Special[MAX_FOOD_ITEM];    //Special Food Items
        struct FoodItem Sp_Day;                    //Special item of the day
        struct Address add;                       
        struct user liveRecord[MAX_ORDERS];    
        int liveCount;                 
        struct Time DeliveryTime;   //Fixed Delivery Time of the restaurent           
    };

    
  // ==========================================
// GLOBAL VARIABLES
// ==========================================
extern int globalOrderID;

// ==========================================
// HELPER & UTILITY FUNCTIONS
// ==========================================
void timeConvert(int *hour, int *minute);
struct Time addTime(struct Time a, struct Time b);
int compareTimes(struct Time a, struct Time b);
void printLine();
int findRestaurent(char rname[], struct Restaurent R[], int size);
struct FoodItem search_foo(struct Restaurent R, char food[]);

// ==========================================
// SORTING FUNCTIONS
// ==========================================
void merge(struct FoodItem arr[], int l, int m, int r);
void mergeSort(struct FoodItem arr[] , int l, int r);
void sortFood(struct Restaurent *R);

void mergeR(struct Restaurent R[], int l, int m, int r);
void mergeSortResto(struct Restaurent R[], int l, int r);
void sortResto(struct Restaurent R[], int size);

void mergeLive(struct user arr[], int l, int m, int r);
void mergesortlive(struct user arr[], int l, int r);
void sortLiveOrders(struct Restaurent *R);

void mergePrice(struct FoodItem arr[], int l, int m, int r);
void mergesortPrice(struct FoodItem arr[], int l, int r);

void mergeItem(struct Restaurent arr[], int l, int m, int r);
void mergeSortItem(struct Restaurent arr[],int l ,int r);

void mergeCommon(char arr[][NAME_SIZE], int l, int m, int r);
void mergeSortCommon(char arr[][NAME_SIZE], int l, int r);

// ==========================================
// FILE HANDLING FUNCTIONS
// ==========================================
void load(struct Restaurent R[], int *size, char filename[]);
void saveToFile(struct Restaurent R[], int size, char filename[]);

// ==========================================
// CORE LOGIC & DISPLAY FUNCTIONS
// ==========================================
void placeOrder(struct Restaurent R[], int size, struct Time currentTime, struct Date d);
void printAllrestaurents(struct Restaurent R[], int size);
void getMinTime(char food[], int qt, struct Restaurent R[], int size);
void getItemAvailability(char food[], struct Restaurent Original[], int size);
void getItemListInSortedOrder_Food(struct Restaurent R);
void getItemListInSortedOrder_Prices(struct Restaurent R);
void getItemListInAreaSortedOrder(char area[], struct Restaurent Original[], int size);
void getAllSpecialItemListinSortedOrder(struct Restaurent R[], int size);
void getItemofDayListinSortedOrder(char area[], struct Restaurent Original[], int size);
void getCommonItem(struct Restaurent R[], int size);
void getAllUniqueItem(struct Restaurent R[], int size);

// ==========================================
// MENU & UI FUNCTIONS
// ==========================================
void postResultPrompt(struct Restaurent R[], int size, struct Time currentTime, struct Date d);
void displayrestaurent(struct Restaurent R);
void displayLiveOrders(struct Restaurent R);
void customerMenu(struct Restaurent R[], int size, struct Time currentTime, struct Date d);
void ownerMenu(struct Restaurent R[], int *size, struct Time currentTime, struct Date d);