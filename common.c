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
    case 'j': //UpArrow
        Attack(UP);
        break;
    case 'k': //DownArrow
        Attack(DOWN);
        break;
    }
}
void CleanUp(){
    free(AllItems);
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