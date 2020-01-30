#include "common.h"

void EquipItem(int index_in_inventory){
    Game->EquippedItem = &Game->Inventory[index_in_inventory];
        gtk_widget_set_name(GTK_WIDGET(Game->GtkGameState->ItemLabels[index_in_inventory]), "activeLabel");
    for(int i=0;i<INVENTORY_SIZE;i++){
        if(i!=index_in_inventory)
            gtk_widget_set_name(GTK_WIDGET(Game->GtkGameState->ItemLabels[i]), "unactiveLabel");
    }
}

void OnKeyPress(GtkWidget *widget, GdkEventKey *event){
    switch(event->keyval){
    case 'w':
        UpdateScreen(UP);
        break;
    case 'a':
        UpdateScreen(LEFT);
        break;
    case 's':
        UpdateScreen(DOWN);
        break;
    case 'd':
        UpdateScreen(RIGHT);
        break;
    case 65361: //LeftArrow
        Attack(LEFT);
        break;
    case 65363: //RightArrow
        Attack(RIGHT);
        break;
    case 65362: //UpArrow
        Attack(UP);
        break;
    case 65364: //DownArrow
        Attack(DOWN);
        break;

    case '1':
        if(Game->Inventory[Game->GameOptions->AllItems[(int)AXEITEM_ID].position_in_inventory].id!=(int)AXEITEM_ID){
            CraftItem((int)AXEITEM_ID);
        }
        else {
            EquipItem(Game->GameOptions->AllItems[(int)AXEITEM_ID].position_in_inventory);
        }
        break;
    case '2':
        if(Game->Inventory[Game->GameOptions->AllItems[(int)PICKAXEITEM_ID].position_in_inventory].id!=(int)PICKAXEITEM_ID){
            CraftItem((int)PICKAXEITEM_ID);
        }
        else EquipItem(Game->GameOptions->AllItems[(int)PICKAXEITEM_ID].position_in_inventory);
        break;
    case '3':
        if(Game->Inventory[Game->GameOptions->AllItems[(int)SHOVELITEM_ID].position_in_inventory].id!=(int)SHOVELITEM_ID){
            CraftItem((int)SHOVELITEM_ID);
        }
        else EquipItem(Game->GameOptions->AllItems[(int)SHOVELITEM_ID].position_in_inventory);
        break;
    case '4':
        UsePotion();
        break;
    }
}

void Reset(){
    for(int i=0;i<COLS;i++){
        for(int j=0;j<ROWS;j++)
            free(Game->Board[i][j]);
        free(Game->Board[i]);
    }
    free(Game->Board);
    free(Game->GtkGameState->ItemLabels);
    for(int i=0;i<MAP_SIZE_X;i++)
        free(Game->GameOptions->Map[i]);
    free(Game->GameOptions->Map);
    for(int i=0;i<INVENTORY_SIZE;i++)
        free(Game->Inventory[i].position);
    free(Game->Inventory);
    free(Game->GameOptions->Objects);
    free(Game->GameOptions->AllItems);
    free(Game->GameOptions);
    if(GTK_IS_BIN(Game->GtkGameState->window)) {
        GtkWidget *child = gtk_bin_get_child(GTK_BIN(Game->GtkGameState->window));
        gtk_widget_destroy(child);
    }
    gtk_widget_hide(Game->GtkGameState->window);
    //gtk_widget_destroy(Game->GtkGameState->window);
    free(Game->GtkGameState);
    free(Game);
    Init();
}

void CleanUp(){
    for(int i=0;i<COLS;i++){
        for(int j=0;j<ROWS;j++)
            free(Game->Board[i][j]);
        free(Game->Board[i]);
    }
    //gtk_window_close(GTK_WINDOW(Game->GtkGameState->window));
    free(Game->Board);
    free(Game->GtkGameState->ItemLabels);
    for(int i=0;i<MAP_SIZE_X;i++)
        free(Game->GameOptions->Map[i]);
    free(Game->GameOptions->Map);
    for(int i=0;i<INVENTORY_SIZE;i++)
        free(Game->Inventory[i].position);
    free(Game->Inventory);
    free(Game->GameOptions->Objects);
    free(Game->GameOptions->AllItems);
    free(Game->GameOptions);
    free(Game->GtkGameState);
    free(Game);
    gtk_main_quit();
    exit(1);
}

void Help(){
    GtkWidget *helpWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(helpWindow),"Help");
    //gtk_window_set_resizable(GTK_WINDOW(helpWindow),FALSE);
    gtk_widget_show(helpWindow);
}