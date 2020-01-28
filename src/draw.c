#include "draw.h"


void UpdateInventory(int inventoryid,int itemid){
    
    if(Game->Inventory[inventoryid].id != Game->GameOptions->AllItems[itemid].id){
        Square *position;
        position = Game->Inventory[inventoryid].position;
        Game->Inventory[inventoryid] = Game->GameOptions->AllItems[itemid];
        Game->Inventory[inventoryid].position = position;
        gtk_image_set_from_file(GTK_IMAGE(Game->Inventory[inventoryid].position->image),Game->Inventory[inventoryid].path);
    }
    else Game->Inventory[inventoryid].quantity++;
    
    if(itemid && itemid != AXEITEM_ID && itemid !=PICKAXEITEM_ID && itemid !=SHOVELITEM_ID){
        char text[100];
        sprintf(text,"%d",Game->Inventory[inventoryid].quantity);
        gtk_label_set_text(GTK_LABEL(Game->GtkGameState->ItemLabels[inventoryid]),text);
    }
    else if(itemid) gtk_label_set_text(GTK_LABEL(Game->GtkGameState->ItemLabels[inventoryid]),Game->GameOptions->AllItems[itemid].name);
    else  gtk_label_set_text(GTK_LABEL(Game->GtkGameState->ItemLabels[inventoryid]),"");

    for(int i=3;i<INVENTORY_SIZE;i++){
        if(Game->Inventory[i].quantity){
            char text[100];
            sprintf(text,"%d",Game->Inventory[i].quantity);
            gtk_label_set_text(GTK_LABEL(Game->GtkGameState->ItemLabels[i]),text);
        }
    }
}

void UpdateBoard(){
    for(int i=0;i<COLS;i++){
        for(int j=0;j<ROWS;j++){
            gtk_image_set_from_file(GTK_IMAGE(Game->Board[i][j]->image),
            Game->GameOptions->Map[i+Game->topleft_x_absolute][j+Game->topleft_y_absolute].current.path);
        }
    }
}

void UpdateScreen(enum Direction dir){
    switch(dir){
        case LEFT:
            if(Game->topleft_y_absolute-1>0 && Game->GameOptions->Map[PLAYER_X_ABSOLUTE-1][PLAYER_Y_ABSOLUTE].object.canPlayerEnter){
                Game->GameOptions->Map[PLAYER_X_ABSOLUTE][PLAYER_Y_ABSOLUTE].current = 
                Game->GameOptions->Map[PLAYER_X_ABSOLUTE][PLAYER_Y_ABSOLUTE].object;
                Game->topleft_x_absolute--;
                Game->GameOptions->Map[PLAYER_X_ABSOLUTE][PLAYER_Y_ABSOLUTE].current = Game->GameOptions->Objects[(int)PLAYEROBJECT_ID];
            }
            break;
        case UP:
            if(Game->topleft_y_absolute-1>0 && Game->GameOptions->Map[PLAYER_X_ABSOLUTE][PLAYER_Y_ABSOLUTE-1].object.canPlayerEnter){
                Game->GameOptions->Map[PLAYER_X_ABSOLUTE][PLAYER_Y_ABSOLUTE].current = 
                Game->GameOptions->Map[PLAYER_X_ABSOLUTE][PLAYER_Y_ABSOLUTE].object;
                Game->topleft_y_absolute--;
                Game->GameOptions->Map[PLAYER_X_ABSOLUTE][PLAYER_Y_ABSOLUTE].current = Game->GameOptions->Objects[(int)PLAYEROBJECT_ID];
            }
            break;
        case RIGHT:
            if(Game->topleft_x_absolute+COLS<MAP_SIZE_X && Game->GameOptions->Map[PLAYER_X_ABSOLUTE+1][PLAYER_Y_ABSOLUTE].object.canPlayerEnter) {
                Game->GameOptions->Map[PLAYER_X_ABSOLUTE][PLAYER_Y_ABSOLUTE].current = 
                Game->GameOptions->Map[PLAYER_X_ABSOLUTE][PLAYER_Y_ABSOLUTE].object;
                Game->topleft_x_absolute++;
                Game->GameOptions->Map[PLAYER_X_ABSOLUTE][PLAYER_Y_ABSOLUTE].current = Game->GameOptions->Objects[(int)PLAYEROBJECT_ID];
            }
            break;
        case DOWN:
            if(Game->topleft_y_absolute+ROWS<MAP_SIZE_Y && Game->GameOptions->Map[PLAYER_X_ABSOLUTE][PLAYER_Y_ABSOLUTE+1].object.canPlayerEnter){
                Game->GameOptions->Map[PLAYER_X_ABSOLUTE][PLAYER_Y_ABSOLUTE].current = 
                Game->GameOptions->Map[PLAYER_X_ABSOLUTE][PLAYER_Y_ABSOLUTE].object;
                Game->topleft_y_absolute++;
                Game->GameOptions->Map[PLAYER_X_ABSOLUTE][PLAYER_Y_ABSOLUTE].current = Game->GameOptions->Objects[(int)PLAYEROBJECT_ID];
            }
            break;
    }
    UpdateBoard();
}


int UpdatePower(){
    if(Game->Power>0){
        gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(Game->GtkGameState->powerLeft),Game->Power/100);
        Game->Power -=0.5;
        return 1;
    }
    //else CleanUp();
    return 0;
}

void Craft(int item1,int item2, int item3, int wheretoput, int whattoput){
    int item1pos = Game->GameOptions->AllItems[item1].position_in_inventory;
    int item2pos = Game->GameOptions->AllItems[item2].position_in_inventory;
    int item3pos = Game->GameOptions->AllItems[item3].position_in_inventory;
    
    if(Game->Inventory[item1pos].quantity && Game->Inventory[item2pos].quantity && Game->Inventory[item3pos].quantity){
        if(!(Game->Inventory[item1pos].quantity-1)){
            Game->Inventory[item1pos].quantity--;
            UpdateInventory(item1pos,NO_ITEM_ID);
        }
        else Game->Inventory[item1pos].quantity--;

        if(!(Game->Inventory[item2pos].quantity-1)){
            Game->Inventory[item2pos].quantity--;
            UpdateInventory(item2pos,NO_ITEM_ID);
        }
        else Game->Inventory[item2pos].quantity--;

        if(!(Game->Inventory[item3pos].quantity-1)){
            Game->Inventory[item3pos].quantity--;
            UpdateInventory(item3pos,NO_ITEM_ID);
        }
        else Game->Inventory[item3pos].quantity--;
        UpdateInventory(wheretoput,whattoput);
    }
}

void CraftItem(int id){
    switch (id)
    {
    case AXEITEM_ID:
        Craft(STICKITEM_ID,ROCKITEM_ID,GRASSITEM_ID,
        Game->GameOptions->AllItems[AXEITEM_ID].position_in_inventory,
        AXEITEM_ID);
        break;
    case PICKAXEITEM_ID:
        Craft(WOODLOGITEM_ID,ROCKITEM_ID,GRASSITEM_ID,
        Game->GameOptions->AllItems[PICKAXEITEM_ID].position_in_inventory,
        PICKAXEITEM_ID);
        break;
    case SHOVELITEM_ID:
        Craft(STICKITEM_ID,WOODLOGITEM_ID,ROCKITEM_ID,
        Game->GameOptions->AllItems[SHOVELITEM_ID].position_in_inventory,
        SHOVELITEM_ID);
        break;
    }
}

void DropItem(GameObject object){
    int itemid;
    switch(object.id){
        case GRASS2OBJECT_ID:  
            itemid = GRASSITEM_ID;
            break;
        case STONEOFPOWEROBJECT_ID:
            itemid = POTIONITEM_ID;
            break;
        case ROCKOBJECT_ID:
            itemid = ROCKITEM_ID;
            break;
        case TREEOBJECT_ID:             
            itemid = WOODLOGITEM_ID;
            break;
        case SMALLROCKOBJECT_ID: 
            itemid = ROCKITEM_ID;
            break;
        case STICKOBJECT_ID:
            itemid = STICKITEM_ID;
            break;
        case GOLDOREOBJECT_ID:
            itemid = GOLDITEM_ID;
            break;
        case SOILOBJECT_ID:
            itemid = DIRTITEM_ID;
            break;
        }
    UpdateInventory(Game->GameOptions->AllItems[itemid].position_in_inventory ,itemid);
}

void InteractWithObject(MapSquare *pointer){
    if(pointer->object.isInteractive &&
    (pointer->object.vulnerableToID == Game->EquippedItem->id ||
    !pointer->object.vulnerableToID)){
        pointer->object.healthPoints--;
        if(!pointer->object.healthPoints){
            DropItem(pointer->object);
            pointer->object = Game->GameOptions->Objects[GRASS1OBJECT_ID];
            pointer->current = Game->GameOptions->Objects[GRASS1OBJECT_ID];
        }
    }

}

void Attack(Direction dir){
    MapSquare* pointer;
    switch(dir){
        case LEFT:
            pointer = &Game->GameOptions->Map[PLAYER_X_ABSOLUTE-1][PLAYER_Y_ABSOLUTE];
            break;
        case RIGHT:
            pointer = &Game->GameOptions->Map[PLAYER_X_ABSOLUTE+1][PLAYER_Y_ABSOLUTE];
            break;
        case UP:
            pointer = &Game->GameOptions->Map[PLAYER_X_ABSOLUTE][PLAYER_Y_ABSOLUTE-1];
            break;
        case DOWN:
            pointer = &Game->GameOptions->Map[PLAYER_X_ABSOLUTE][PLAYER_Y_ABSOLUTE+1];
            break;
    }
    InteractWithObject(pointer);
    UpdateBoard();
}

void UsePotion(){
    int potion_in_inv = Game->GameOptions->AllItems[POTIONITEM_ID].position_in_inventory;
    if(Game->Inventory[potion_in_inv].quantity){
        Game->Inventory[potion_in_inv].quantity--;
        char text[100];
        sprintf(text,"%d",Game->Inventory[potion_in_inv].quantity);
        gtk_label_set_text(GTK_LABEL(Game->GtkGameState->ItemLabels[potion_in_inv]),text);
        if(!Game->Inventory[potion_in_inv].quantity){
            UpdateInventory(potion_in_inv,NO_ITEM_ID);
        }
        if(Game->Power+10<=100.0)
            Game->Power+=10;
        else Game->Power = 100.0;
        UpdatePower();
    }
}
