#include "common.h"

void OnKeyPress(GtkWidget *widget, GdkEventKey *event, gpointer user_data){
    switch(event->keyval){
    case 119:
        UpdateScreen(UP);
        break;
    case 97:
        UpdateScreen(LEFT);
        break;
    case 115:
        UpdateScreen(DOWN);
        break;
    case 100:
        UpdateScreen(RIGHT);
        break;
    }
}