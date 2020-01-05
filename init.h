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

struct MapSquare;
struct GameObject;
enum Direction;
struct Square;

void Init();
void InitMap();
void OnKeyPress(GtkWidget *widget, GdkEventKey *event, gpointer user_data);
void UpdateBoard();
void UpdateScreen(enum Direction dir);
