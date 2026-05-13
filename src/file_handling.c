#include "../include/food_system.h"


 //Initialise Restaurents with Data
    void load(struct Restaurent R[], int *size, char filename[]) {

        FILE *fp=fopen(filename, "r");
    
        if(fp==NULL) {
            printf("Warning: Error opening the File\n");
        }
    
    
        else {
            fscanf(fp, "%d", size);

            for(int i=0;i<*size;i++) {
                fscanf(fp, " %[^\n]", R[i].Resto_Name);  //Restaurent Name


                fscanf(fp, "%d", &R[i].add.plot_no);  //Restaurent Address
                fscanf(fp, " %[^\n]", R[i].add.AreaName);


                fscanf(fp, "%d %d", &R[i].DeliveryTime.hour, &R[i].DeliveryTime.minute);


                R[i].liveCount=0;  //Live Count


                //Generic Items
                fscanf(fp, "%d", &R[i].gen_food_items);
                for(int j=0;j<R[i].gen_food_items;j++) {
                    
                    fscanf(fp, " %[^\n]", R[i].Generic[j].foodName);
                    fscanf(fp, "%d %f %d %d",&R[i].Generic[j].quantity,&R[i].Generic[j].foodCost,&R[i].Generic[j].t.hour,&R[i].Generic[j].t.minute);
                }
                

                //Special Food Items
                fscanf(fp, "%d", &R[i].spl_food_items);
                for (int j = 0; j < R[i].spl_food_items; j++) {
                    
                    fscanf(fp, " %[^\n]", R[i].Special[j].foodName);
                    fscanf(fp, "%d %f %d %d",&R[i].Special[j].quantity,&R[i].Special[j].foodCost,&R[i].Special[j].t.hour,&R[i].Special[j].t.minute);
                }


                // Special item of the day
                fscanf(fp, " %[^\n]", R[i].Sp_Day.foodName);
                fscanf(fp, "%d %f %d %d", &R[i].Sp_Day.quantity,&R[i].Sp_Day.foodCost,&R[i].Sp_Day.t.hour,&R[i].Sp_Day.t.minute);
                }


                fclose(fp);
                printf("Loaded %d restaurants from '%s'.\n", *size, filename);
                }
    }


    void saveToFile(struct Restaurent R[], int size, char filename[]) {

        FILE *fp = fopen(filename, "w");
        
        if (fp == NULL) {
        
            printf("Error: Could not save");
        }
        
        
        else {
        
            fprintf(fp, "%d\n", size);

            for (int i = 0; i < size; i++) {
                fprintf(fp, "%s\n", R[i].Resto_Name);
                fprintf(fp, "%d\n", R[i].add.plot_no);
                fprintf(fp, "%s\n", R[i].add.AreaName);
                fprintf(fp, "%d %d\n", R[i].DeliveryTime.hour, R[i].DeliveryTime.minute);
                
                fprintf(fp, "%d\n", R[i].gen_food_items);
                for (int j = 0; j < R[i].gen_food_items; j++) {
                    fprintf(fp, "%s\n", R[i].Generic[j].foodName);
                    fprintf(fp, "%d %f %d %d\n",R[i].Generic[j].quantity,R[i].Generic[j].foodCost,R[i].Generic[j].t.hour,R[i].Generic[j].t.minute);
                }


                fprintf(fp, "%d\n", R[i].spl_food_items);
                for (int j = 0; j < R[i].spl_food_items; j++) {
                
                    fprintf(fp, "%s\n", R[i].Special[j].foodName);
                    fprintf(fp, "%d %f %d %d\n",R[i].Special[j].quantity,R[i].Special[j].foodCost,R[i].Special[j].t.hour,R[i].Special[j].t.minute);
                
                }

                fprintf(fp, "%s\n", R[i].Sp_Day.foodName);
                fprintf(fp, "%d %f %d %d\n",R[i].Sp_Day.quantity,R[i].Sp_Day.foodCost,R[i].Sp_Day.t.hour,R[i].Sp_Day.t.minute);
            }
        
         fclose(fp);
         printf("Saved %d restaurants to '%s'.\n", size, filename);
         }
    }

