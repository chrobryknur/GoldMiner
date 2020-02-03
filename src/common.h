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
#define GAME_OBJECTS_NUM 12
#define PLAYER_X_RELATIVE COLS/2-1
#define PLAYER_Y_RELATIVE ROWS/2-1
#define PLAYER_X_ABSOLUTE PLAYER_X_RELATIVE + Game->topleft_x_absolute
#define PLAYER_Y_ABSOLUTE PLAYER_Y_RELATIVE + Game->topleft_y_absolute
#define INVENTORY_SIZE 10
#define ALL_ITEMS_NUM 14
 
typedef struct GameObject{
    char *name;
    char *path;
    int id;
    bool canPlayerEnter;
    bool isInteractive;
    bool isPlayer;
    int healthPoints;
    int vulnerableToID;
    double probabilityOfSpawning;
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

typedef enum ItemIDs{
    NO_ITEM_ID = 0,
    GRASSITEM_ID = 1,
    ROCKITEM_ID = 2,
    STICKITEM_ID = 3,
    WOODLOGITEM_ID = 4,
    GOLDITEM_ID = 5,
    DIRTITEM_ID = 6,
    POTIONITEM_ID = 7,
    AXEITEM_ID = 8,
    NO_AXEITEM_ID = 9,
    PICKAXEITEM_ID = 10,
    NO_PICKAXEITEM_ID = 11,
    NO_SHOVELITEM_ID = 12,
    SHOVELITEM_ID = 13
}ItemIds;

typedef enum GameObjectIDs{
    PLAYEROBJECT_ID = 0,
    WAVEOBJECT_ID = 1,
    GOLDOREOBJECT_ID = 2,
    STONEOFPOWEROBJECT_ID = 3,
    SOILOBJECT_ID = 4,
    ROCKOBJECT_ID = 5,
    TREEOBJECT_ID = 6,
    LAKEOBJECT_ID = 7,
    GRASS2OBJECT_ID = 8,
    SMALLROCKOBJECT_ID = 9,
    STICKOBJECT_ID = 10,
    GRASS1OBJECT_ID = 11
}GameObjectIDs;

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
    int position_in_inventory;
    bool wearable;
    GtkWidget *label;
}Item;

typedef struct GtkState{
    GtkWidget *window;
    GtkWidget *scoreWindow;
    GtkWidget *powerLeft;
    GtkWidget *scoreLabel;
    GtkCssProvider *cssProvider;
    GtkWidget *InventoryGrid;
    GtkWidget **ItemLabels;
    GtkWidget *Grid;
}GtkState;

typedef struct GameStaticOptions{
    MapSquare **Map;
    GameObject *Objects;
    Item *AllItems;
}GameStaticOptions;

typedef struct GameState{
    Square ***Board;
    Item *Inventory;
    Item *EquippedItem;
    int Score;
    float Power;
    int topleft_x_absolute;
    int topleft_y_absolute;
    GameStaticOptions *GameOptions;
    GtkState *GtkGameState;
}GameState;

GameState *Game;

void OnKeyPress(GtkWidget *widget, GdkEventKey *event);
void UpdateScreen(enum Direction dir);
void Attack(Direction dir);
void UsePotion();
void CraftItem(int id);
int UpdatePower();
void CleanUp();
void Reset();
void Init();
void Help();
void EndGame();