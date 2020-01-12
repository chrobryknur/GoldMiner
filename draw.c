#include "draw.h"

void UpdateBoard(){
    for(int i=0;i<COLS;i++){
        for(int j=0;j<ROWS;j++){
            gtk_image_set_from_file(GTK_IMAGE(Board[i][j]->image),
            Map[i+topleft_x_absolute][j+topleft_y_absolute].current.path);
        }
    }
}

void UpdateScreen(enum Direction dir){
    switch(dir){
        case LEFT:
            if(topleft_y_absolute-1>0 && Map[PLAYER_X_ABSOLUTE-1][PLAYER_Y_ABSOLUTE].object.canPlayerEnter){
                Map[PLAYER_X_ABSOLUTE][PLAYER_Y_ABSOLUTE].current = 
                Map[PLAYER_X_ABSOLUTE][PLAYER_Y_ABSOLUTE].object;
                topleft_x_absolute--;
                Map[PLAYER_X_ABSOLUTE][PLAYER_Y_ABSOLUTE].current = Objects[0];
            }
            break;
        case UP:
            if(topleft_y_absolute-1>0 && Map[PLAYER_X_ABSOLUTE][PLAYER_Y_ABSOLUTE-1].object.canPlayerEnter){
                Map[PLAYER_X_ABSOLUTE][PLAYER_Y_ABSOLUTE].current = 
                Map[PLAYER_X_ABSOLUTE][PLAYER_Y_ABSOLUTE].object;
                topleft_y_absolute--;
                Map[PLAYER_X_ABSOLUTE][PLAYER_Y_ABSOLUTE].current = Objects[0];
            }
            break;
        case RIGHT:
            if(topleft_x_absolute+COLS<MAP_SIZE_X && Map[PLAYER_X_ABSOLUTE+1][PLAYER_Y_ABSOLUTE].object.canPlayerEnter) {
                Map[PLAYER_X_ABSOLUTE][PLAYER_Y_ABSOLUTE].current = 
                Map[PLAYER_X_ABSOLUTE][PLAYER_Y_ABSOLUTE].object;
                topleft_x_absolute++;
                Map[PLAYER_X_ABSOLUTE][PLAYER_Y_ABSOLUTE].current = Objects[0];
            }
            break;
        case DOWN:
            if(topleft_y_absolute+ROWS<MAP_SIZE_Y && Map[PLAYER_X_ABSOLUTE][PLAYER_Y_ABSOLUTE+1].object.canPlayerEnter){
                Map[PLAYER_X_ABSOLUTE][PLAYER_Y_ABSOLUTE].current = 
                Map[PLAYER_X_ABSOLUTE][PLAYER_Y_ABSOLUTE].object;
                topleft_y_absolute++;
                Map[PLAYER_X_ABSOLUTE][PLAYER_Y_ABSOLUTE].current = Objects[0];
            }
            break;
    }
    UpdateBoard();
}


int UpdatePower(){
    if(Power>0){
        gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(powerLeft),Power/100);
        Power -=0.5;
        return 1;
    }
    //else CleanUp();
    return 0;
}

void Attack(Direction dir){
    switch(dir){
        case LEFT:
            //printf("SIEMA");
            break;
            /*if(Map[PLAYER_X_ABSOLUTE-1][PLAYER_Y_ABSOLUTE].object.isInteractive){
                if(Map[PLAYER_X_ABSOLUTE-1][PLAYER_Y_ABSOLUTE].object.vulnerableToID == EquippedItem->id){
                    Map[PLAYER_X_ABSOLUTE-1][PLAYER_Y_ABSOLUTE].object.healthPoints--;
                    if(!Map[PLAYER_X_ABSOLUTE-1][PLAYER_Y_ABSOLUTE].object.healthPoints){
                        Map[PLAYER_X_ABSOLUTE-1][PLAYER_Y_ABSOLUTE].object = Objects[0];
                        Map[PLAYER_X_ABSOLUTE-1][PLAYER_Y_ABSOLUTE].current = Objects[0];
                    }
                }
            }
            break;*/
        case RIGHT:

            break;
        case UP:

            break;

        case DOWN:

            break;
    }
    UpdateBoard();
}
