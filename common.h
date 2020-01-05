#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <stdbool.h>
#include <gdk/gdkkeysyms.h>

#define ROWS 16
#define COLS 32
#define PNG_SIZE 32
#define WINDOW_HEIGHT ROWS*PNG_SIZE
#define WINDOW_WIDTH  COLS*PNG_SIZE
#define MAP_SIZE_X 512
#define MAP_SIZE_Y 512
#define GAME_OBJECTS 4
#define PLAYER_X_RELATIVE COLS/2-1
#define PLAYER_Y_RELATIVE ROWS/2-1

int topleft_x_absolute;
int topleft_y_absolute;

typedef struct GameObject{
    char *name;
    char *path;
    bool canPlayerEnter;
    bool isInteractive;
    bool isPlayer;
}GameObject;

typedef struct MapSquare{
    GameObject current;
    GameObject object;
}MapSquare;

typedef enum Direction{
    LEFT=0,
    UP=1,
    RIGHT=2,
    DOWN=3
}Direction;

typedef struct Square{
    GtkWidget *image;
    gint left;
    gint top;
    gint width;
    gint height; 
}Square;

MapSquare Map[MAP_SIZE_X][MAP_SIZE_Y];
GameObject Objects[GAME_OBJECTS];
Square ***Board;

void OnKeyPress(GtkWidget *widget, GdkEventKey *event, gpointer user_data);
void UpdateScreen(Direction dir);