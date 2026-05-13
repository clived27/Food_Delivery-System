#include "../include/food_system.h"

void timeConvert(int *hour, int *minute) {
        while (*minute >= 60) {  
            *hour   += 1;
            *minute -= 60;      
        }
    }




    //to add Delivery time + Service time in current time to give the expected time to the User 
    struct Time addTime(struct Time a, struct Time b) {
        struct Time result;                        
        result.hour   = a.hour   + b.hour;         
        result.minute = a.minute + b.minute;       
        timeConvert(&result.hour, &result.minute); 
        return result;                             
    }



    //Function to compare Time
    //used in sorting Live Orders based on Order time and Expected Time 
    // Returns -1 if a < b, 0 if equal, 1 if a > b
    int compareTimes(struct Time a, struct Time b) {
        int ans;
        if (a.hour != b.hour) {
            if(a.hour<b.hour) {
                ans=-1;
            }
            else {
                ans=1;
            }
        }

        else if (a.minute != b.minute) {
            if(a.minute<b.minute) {
                ans=-1;
            }
            else {
                ans=1;
            }                                                          
        }
        else {
            ans=0;
        }

        return ans;
        
    }



    //Done for Decoration and Seperation
    void printLine() {
        printf("**********************************************************\n"); 
    }




    //Binary Search to Find a Restaurent since they are sorted
    int findRestaurent(char rname[], struct Restaurent R[], int size) {
        int st=0, end=size-1;
        int idx=-1;

        while(st<=end && idx==-1) {
                int mid=st+(end-st)/2;
                    
                if(strcmp(R[mid].Resto_Name, rname)==0) {
                    idx=mid;
                }
                else if(strcmp(R[mid].Resto_Name, rname)>0) {
                    end=mid-1;
                }
                else {
                    st=mid+1;
                }
        }

        return idx;
    }




    //Search Food item in a restaurent
    struct FoodItem search_foo(struct Restaurent R, char food[]) {
        struct FoodItem found;      
        found.foodName[0] = '\0';   
        found.quantity    = -1;     
        found.foodCost    = -1;     
        found.t.hour      = -1;     
        found.t.minute    = -1;     
        //initialized each to -1 if food item doesnt exist anywhere

        
        //First Search in Special Food item as it is easier
        if (strcmp(food, R.Sp_Day.foodName) == 0) {
            found = R.Sp_Day;       
        }   

        else { 
            int flag = 0; //To know if food item has been found               

            
            //Search in Generic Food Items - Binary Search
            int st = 0, end = R.gen_food_items - 1;

            while (st <= end && flag == 0) {

                int mid = st + (end - st) / 2;                      
        
                if (strcmp(food, R.Generic[mid].foodName)== 0) { 
                    found = R.Generic[mid]; 
                    flag = 1; 
                } 

                else if (strcmp(food, R.Generic[mid].foodName) > 0)  {
                    st = mid + 1;
                }                     

                else {
                    end = mid - 1;
                }                    
            }


            //Search in Special Food items - Binary Search
            st = 0; end = R.spl_food_items - 1;

            while (st <= end && flag == 0) {

                int mid = st + (end - st) / 2;                      

                if (strcmp(food, R.Special[mid].foodName)== 0) {
                    found = R.Special[mid]; 
                    flag = 1; 
                } 
                else if (strcmp(food, R.Special[mid].foodName)> 0) {
                    st = mid + 1;
                }                     
                else {
                    end = mid - 1;
                }                    
            }
        }

        return found; 
    }


       //MERGE SORTING FOOD ITEMS IN THE RESTAURENT
    void merge(struct FoodItem arr[], int l, int m, int r) {
        int i=l, j=m+1, k=0;
        static struct FoodItem temp[MAX_FOOD_ITEM];

        while(i<=m && j<=r) {
            if(strcmp(arr[i].foodName, arr[j].foodName)<=0) {
                temp[k++]=arr[i++];
            }
            else {
                temp[k++]=arr[j++];
            }
        }

        while(i<=m) {
            temp[k++]=arr[i++];
        }

        while(j<=r) {
            temp[k++]=arr[j++];
        }

        for(int p=0;p<k;p++) {
            arr[l+p]=temp[p];
        }

    }
    
    void mergeSort(struct FoodItem arr[] , int l, int r) {
        if(l<r) {
            int m=l+(r-l)/2;

            mergeSort(arr, l, m);
            mergeSort(arr, m+1, r);

            merge(arr, l,m,r);
        }
    } 
    void sortFood(struct Restaurent *R) {
        if((*R).gen_food_items>0) { //Ensure that there are Generic Food Items
            mergeSort((*R).Generic, 0, (*R).gen_food_items-1);    
        }

        if((*R).spl_food_items>0) { //Ensure that there are Special Food Items
            mergeSort((*R).Special, 0, (*R).spl_food_items-1);    
        }
    }




    //Sort Restaurents primarly by Name and then by address
    void mergeR(struct Restaurent R[], int l, int m, int r) {
        int i=l, j=m+1, k=0;
        static struct Restaurent temp[MAX_RESTO];

        while(i<=m && j<=r) {
            if(strcmp(R[i].Resto_Name, R[j].Resto_Name)<0) {
                temp[k++]=R[i++];
            }
            else if(strcmp(R[i].Resto_Name, R[j].Resto_Name)>0) {
                temp[k++]=R[j++];
            }
            else {
                if(strcmp(R[i].add.AreaName, R[j].add.AreaName)<0) {
                    temp[k++]=R[i++];
                }
                else if(strcmp(R[i].add.AreaName, R[j].add.AreaName)>0) {
                    temp[k++]=R[j++];
                }
                else {
                    if(R[i].add.plot_no<R[j].add.plot_no) {
                        temp[k++]=R[i++];
                    }
                    else {
                        temp[k++]=R[j++];
                    }
                }
            }
        }

        while(i<=m){
            temp[k++]=R[i++];
        }
        while(j<=r){
            temp[k++]=R[j++];
        }
        for(int s=0;s<k;s++){
            R[l+s]=temp[s];
        }
    }

    void mergeSortResto(struct Restaurent R[], int l, int r) {
        if(l<r) {
            int m=l+(r-l)/2;

            mergeSortResto(R,l,m);
            mergeSortResto(R, m+1, r);
            mergeR(R, l,m,r);
        }
    }
    
    void sortResto(struct Restaurent R[], int size) {
        int l=0, r=size-1;
        mergeSortResto(R,l,r);
    }




    // Sort live orders of a restaurent ; Primarly oned on Order time and then delivery Time
    void mergeLive(struct user arr[], int l, int m, int r) {
        int i=l, j=m+1, k=0;
        static struct user temp[MAX_ORDERS];

        while(i<=m && j<=r) {
            if(compareTimes(arr[i].order_time, arr[j].order_time)<0) {
                temp[k++]=arr[i++];
            }
            else if(compareTimes(arr[i].order_time, arr[j].order_time)>0) {
                temp[k++]=arr[j++];
            }
            else {
                if(compareTimes(arr[i].expected, arr[j].expected)<0) {
                    temp[k++]=arr[i++];
                }
                else {
                    temp[k++]=arr[j++];
                }
            }
        }

        while(i<=m) {
            temp[k++]=arr[i++];
        }

        while(j<=r) {
            temp[k++]=arr[j++];
        }
        for(int s=0;s<k;s++){
            arr[l+s]=temp[s];
        }

    }

    
    void mergesortlive(struct user arr[], int l, int r) {
        if(l<r) {
            int m=l+(r-l)/2;

            mergesortlive(arr,l,m);
            mergesortlive(arr,m+1,r);
            mergeLive(arr,l,m,r);
        }
    } 

    void sortLiveOrders(struct Restaurent *R) {

        mergesortlive((*R).liveRecord,0,(*R).liveCount-1);
    }


    //Sort Food Items by PRICES
    void mergePrice(struct FoodItem arr[], int l, int m, int r) {
        int i=l, j=m+1, k=0;
        static struct FoodItem temp[MAX_FOOD_ITEM];

        while(i<=m && j<=r) {
            if(arr[i].foodCost>=arr[j].foodCost) {
                temp[k++]=arr[i++];
            }
            else {
                temp[k++]=arr[j++];
            }
        }

        while(i<=m) {
            temp[k++]=arr[i++];
        }
        while(j<=r) {
            temp[k++]=arr[j++];
        }
        for(int s=0;s<k;s++){
            arr[l+s]=temp[s];
        }
    }

     void mergesortPrice(struct FoodItem arr[], int l, int r) {
        if(l<r) {
            int m=l+(r-l)/2;

            mergesortPrice(arr, l,m);
            mergesortPrice(arr,m+1, r);
            mergePrice(arr, l,m,r);
        }
    }


     void mergeItem(struct Restaurent arr[], int l, int m, int r) {
        int i=l, j=m+1, k=0;
        static struct Restaurent temp[MAX_RESTO];

        while(i<=m && j<=r) {
            if(strcmp(arr[i].Sp_Day.foodName, arr[j].Sp_Day.foodName)<0) {
                temp[k++]=arr[i++];
            }

            else if(strcmp(arr[i].Sp_Day.foodName, arr[j].Sp_Day.foodName)>0) {
                temp[k++]=arr[j++];
            }

            else {
                if(arr[i].Sp_Day.foodCost<=arr[j].Sp_Day.foodCost) {
                    temp[k++]=arr[i++];
                }
                else {
                    temp[k++]=arr[j++];
                }
            }
        }

        while(i<=m) {
            temp[k++]=arr[i++];
        }

        while(j<=r) {
            temp[k++]=arr[j++];
        }

        for(int p=0;p<k;p++) {
            arr[l+p]=temp[p];
        }
    }
    void mergeSortItem(struct Restaurent arr[],int l ,int r){
        if(l<r){
            int m = l+ (r-l)/2;

            mergeSortItem(arr, l, m);
            mergeSortItem(arr, m+1,r);

            mergeItem(arr, l, m, r);
        }
    }


      void mergeCommon(char arr[][NAME_SIZE], int l, int m, int r) {
        int i=l, j=m+1, k=0;
        char temp[MAX_FOOD_ITEM*2 + 1][NAME_SIZE];

        while(i<=m && j<=r) {
            if(strcmp(arr[i], arr[j])<=0) {
                strcpy(temp[k++], arr[i++]);
            }
            else {
                strcpy(temp[k++], arr[j++]);
            }
        }

        while(i<=m) {
            strcpy(temp[k++], arr[i++]);
        }

        while(j<=r) {
            strcpy(temp[k++], arr[j++]);
        }

        for(int p=0;p<k;p++) {
            strcpy(arr[p+l], temp[p]);
        }

    }


    void mergeSortCommon(char arr[][NAME_SIZE], int l, int r) {
        if(l<r) {
            int m=l+(r-l)/2;
            mergeSortCommon(arr, l, m);
            mergeSortCommon(arr, m+1, r);
            mergeCommon(arr, l, m, r);
        }


    }

    


