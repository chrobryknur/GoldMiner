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
            if(topleft_y_absolute-1>0 && Map[topleft_x_absolute+PLAYER_X_RELATIVE-1][topleft_y_absolute+PLAYER_Y_RELATIVE].object.canPlayerEnter){
                Map[topleft_x_absolute+PLAYER_X_RELATIVE][topleft_y_absolute+PLAYER_Y_RELATIVE].current = 
                Map[topleft_x_absolute+PLAYER_X_RELATIVE][topleft_y_absolute+PLAYER_Y_RELATIVE].object;
                topleft_x_absolute--;
                Map[topleft_x_absolute+PLAYER_X_RELATIVE][topleft_y_absolute+PLAYER_Y_RELATIVE].current = Objects[0];
            }
            //dopisac else
            break;
        case UP:
            if(topleft_y_absolute-1>0 && Map[topleft_x_absolute+PLAYER_X_RELATIVE][topleft_y_absolute+PLAYER_Y_RELATIVE-1].object.canPlayerEnter){
                Map[topleft_x_absolute+PLAYER_X_RELATIVE][topleft_y_absolute+PLAYER_Y_RELATIVE].current = 
                Map[topleft_x_absolute+PLAYER_X_RELATIVE][topleft_y_absolute+PLAYER_Y_RELATIVE].object;
                topleft_y_absolute--;
                Map[topleft_x_absolute+PLAYER_X_RELATIVE][topleft_y_absolute+PLAYER_Y_RELATIVE].current = Objects[0];
            }
            break;
        case RIGHT:
            if(topleft_x_absolute+COLS<MAP_SIZE_X && Map[topleft_x_absolute+PLAYER_X_RELATIVE+1][topleft_y_absolute+PLAYER_Y_RELATIVE].object.canPlayerEnter) {
                Map[topleft_x_absolute+PLAYER_X_RELATIVE][topleft_y_absolute+PLAYER_Y_RELATIVE].current = 
                Map[topleft_x_absolute+PLAYER_X_RELATIVE][topleft_y_absolute+PLAYER_Y_RELATIVE].object;
                topleft_x_absolute++;
                Map[topleft_x_absolute+PLAYER_X_RELATIVE][topleft_y_absolute+PLAYER_Y_RELATIVE].current = Objects[0];
            }
            break;
        case DOWN:
            if(topleft_y_absolute+ROWS<MAP_SIZE_Y && Map[topleft_x_absolute+PLAYER_X_RELATIVE][topleft_y_absolute+PLAYER_Y_RELATIVE+1].object.canPlayerEnter){
                Map[topleft_x_absolute+PLAYER_X_RELATIVE][topleft_y_absolute+PLAYER_Y_RELATIVE].current = 
                Map[topleft_x_absolute+PLAYER_X_RELATIVE][topleft_y_absolute+PLAYER_Y_RELATIVE].object;
                topleft_y_absolute++;
                Map[topleft_x_absolute+PLAYER_X_RELATIVE][topleft_y_absolute+PLAYER_Y_RELATIVE].current = Objects[0];
            }
            break;
    }
    UpdateBoard();
}