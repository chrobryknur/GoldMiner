#include "common.h"

void EquipItem(int index_in_inventory){
    EquippedItem = &Inventory[index_in_inventory];
        gtk_widget_set_name(GTK_WIDGET(ItemLabels[index_in_inventory]), "activeLabel");
    for(int i=0;i<INVENTORY_SIZE;i++){
        if(i!=index_in_inventory)
            gtk_widget_set_name(GTK_WIDGET(ItemLabels[i]), "unactiveLabel");
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
        if(Inventory[0].id!=8){
            CraftItem(8); //craft axe
        }
        else {
            EquipItem(0);
        }
        break;
    case '2':
        if(Inventory[1].id!=10){
            CraftItem(10);
        }
        else EquipItem(1);
        break;
    case '3':
        if(Inventory[2].id!=13){
            CraftItem(13);
        }
        else EquipItem(2);
        break;
    case '4':
        UsePotion();
        break;
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