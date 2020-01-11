#include "common.h"

void OnKeyPress(GtkWidget *widget, GdkEventKey *event, gpointer user_data){
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
    }
}