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

void CraftItem(int id){

}

void UpdateInventory(int inventoryid,int itemid){
    Square *position;
    if(Inventory[inventoryid].id != AllItems[itemid].id){
                    position = Inventory[inventoryid].position;
                    Inventory[inventoryid] = AllItems[itemid];
                    Inventory[inventoryid].position = position;
                    gtk_image_set_from_file(GTK_IMAGE(Inventory[inventoryid].position->image),Inventory[inventoryid].path);
                }
                else Inventory[inventoryid].quantity++;
                char text[100];
                sprintf(text,"%d",Inventory[inventoryid].quantity);
                gtk_label_set_text(GTK_LABEL(hourLabel),text);
}

void DropItem(GameObject object){
                Square *position;
    switch(object.id){
        case 4:             //GRASS2
            UpdateInventory(9 ,2);
            break;
        case 7:             //STONE OF POWER
            UpdateInventory(1,6);
            break;
        case 5:             //ROCK
            break;
        case 2:             //TREE
            break;
        case 8:
            UpdateInventory(8,3);
            break;
        case 9:
            UpdateInventory(7,4);
            break;
    }
}

void InteractWithObject(MapSquare *pointer){
    if(pointer->object.isInteractive &&
    (pointer->object.vulnerableToID == EquippedItem->id ||
    !pointer->object.vulnerableToID)){
        pointer->object.healthPoints--;
        if(!pointer->object.healthPoints){
            DropItem(pointer->object);
            pointer->object = Objects[1];
            pointer->current = Objects[1];
        }
    }

}

void Attack(Direction dir){
    MapSquare* pointer;
    switch(dir){
        case LEFT:
            pointer = &Map[PLAYER_X_ABSOLUTE-1][PLAYER_Y_ABSOLUTE];
            break;
        case RIGHT:
            pointer = &Map[PLAYER_X_ABSOLUTE+1][PLAYER_Y_ABSOLUTE];
            break;
        case UP:
            pointer = &Map[PLAYER_X_ABSOLUTE][PLAYER_Y_ABSOLUTE-1];
            break;
        case DOWN:
            pointer = &Map[PLAYER_X_ABSOLUTE][PLAYER_Y_ABSOLUTE+1];
            break;
    }
    InteractWithObject(pointer);
    UpdateBoard();
}

void UsePotion(){
    if(Inventory[1].quantity){
        Inventory[1].quantity--;
        if(!Inventory[1].quantity){
            UpdateInventory(1,0);
        }
        if(Power+10<=100.0)
            Power+=10;
        else Power = 100.0;
        UpdatePower();
    }
}
