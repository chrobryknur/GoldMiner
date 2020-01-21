#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <stdbool.h>
#include <gdk/gdkkeysyms.h>
#include <assert.h>
#include <math.h>

#define ROWS 16
#define COLS 32
#define PNG_SIZE 32
#define INVENTORY_PNG_SIZE 48
#define WINDOW_HEIGHT ROWS*PNG_SIZE
#define WINDOW_WIDTH  COLS*PNG_SIZE
#define MAP_SIZE_X 512
#define MAP_SIZE_Y 512
#define GAME_OBJECTS 12
#define PLAYER_X_RELATIVE COLS/2-1
#define PLAYER_Y_RELATIVE ROWS/2-1
#define PLAYER_X_ABSOLUTE PLAYER_X_RELATIVE + topleft_x_absolute
#define PLAYER_Y_ABSOLUTE PLAYER_Y_RELATIVE + topleft_y_absolute
#define INVENTORY_SIZE 10
#define ALL_ITEMS_NUM 15

int topleft_x_absolute;
int topleft_y_absolute;

typedef struct GameObject{
    char *name;
    char *path;
    int id;
    bool canPlayerEnter;
    bool isInteractive;
    bool isPlayer;
    int healthPoints;
    int vulnerableToID;
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

typedef struct Item{
    Square *position;
    char *name;
    char *path;
    int id;
    int quantity;
    bool wearable;
}Item;

MapSquare Map[MAP_SIZE_X][MAP_SIZE_Y];
GameObject Objects[GAME_OBJECTS];
Square ***Board;
Item *Inventory;
Item *EquippedItem;
Item *AllItems;
float Power;
GtkWidget *powerLeft;
GtkWidget *hourLabel;

void OnKeyPress(GtkWidget *widget, GdkEventKey *event);
void Attack(Direction dir);
void UpdateInventory(int inventoryid, int itemid);
void UpdateScreen(Direction dir);
void UsePotion();
void CraftItem(int id);
int UpdatePower();
void CleanUp();
void Help();