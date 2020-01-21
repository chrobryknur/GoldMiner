#include "common.h"

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
    case 'h': //LeftArrow
        Attack(LEFT);
        break;
    case 'l': //RightArrow
        Attack(RIGHT);
        break;
    case 'k': //UpArrow
        Attack(UP);
        break;
    case 'j': //DownArrow
        Attack(DOWN);
        break;
    case '2':
        UsePotion();
        break;
    case '3':
        if(Inventory[2].id!=5){
            CraftItem(5); //craft axe
        }
        else EquippedItem = &Inventory[2];
        break;
    case '4':
        if(Inventory[3].id!=8){
            CraftItem(8);
        }
        else EquippedItem = &Inventory[3];
        break;
    case '5':
        if(Inventory[4].id!=13){
            CraftItem(13);
        }
        else EquippedItem = &Inventory[4]; 
    }
}
void CleanUp(){
    free(AllItems);
    for(int i=0;i<COLS;i++){
        free(Board[i]);
    }
    free(Inventory);
    free(Board);
    gtk_main_quit();
    exit(1);
}

void Help(){
    GtkWidget *helpWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(helpWindow),"Help");
    //gtk_window_set_resizable(GTK_WINDOW(helpWindow),FALSE);
    gtk_widget_show(helpWindow);
}