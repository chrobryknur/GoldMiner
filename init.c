#include "init.h"

void InitScreen(GtkWidget* grid){
    for(int i=0;i<COLS;i++){
        Board[i] = (Square**)malloc(ROWS*sizeof(Square*));
        for(int j=0;j<ROWS;j++){
            Board[i][j] = malloc(sizeof(Square*));
            Board[i][j]->image = gtk_image_new();
            gtk_image_set_from_file(GTK_IMAGE(Board[i][j]->image),Map[i+topleft_x_absolute][j+topleft_y_absolute].current.path);
            Board[i][j]->top = j*WINDOW_HEIGHT/ROWS;
            Board[i][j]->left = i*WINDOW_WIDTH/COLS;
            Board[i][j]->height = WINDOW_HEIGHT/ROWS;
            Board[i][j]->width = WINDOW_WIDTH/COLS;
            gtk_grid_attach(GTK_GRID(grid),GTK_WIDGET(Board[i][j]->image),Board[i][j]->left,
            Board[i][j]->top,Board[i][j]->width,Board[i][j]->height);
            gtk_widget_show(Board[i][j]->image);
        }
    }
}

GameObject RandomObject(){
    int x = rand()%30;
    if(x<3) return Objects[2];
    if(x<8) return Objects[3];
    return Objects[1];
}

void InitMap(){
    for(int i=0;i<MAP_SIZE_X;i++){
        for(int j=0;j<MAP_SIZE_Y;j++){
            if(i == topleft_x_absolute + COLS/2 -1 && j == topleft_y_absolute+ROWS/2 -1){
                Map[i][j].current = Objects[0];
                Map[i][j].object = Objects[1];
            }
            else{
                Map[i][j].current = Map[i][j].object = RandomObject();
            }
        }
    }
}

void InitGameObjects(){
    Objects[0].name = "PLAYER";
    Objects[0].path = "Images/player.png";
    Objects[0].canPlayerEnter = true;
    Objects[0].isInteractive = true;
    Objects[0].isPlayer = true;

    Objects[1].name = "GRASS";
    Objects[1].path = "Images/grass.png";
    Objects[1].canPlayerEnter = true;
    Objects[1].isInteractive = true;
    Objects[1].isPlayer = false;

    Objects[2].name = "TREE";
    Objects[2].path = "Images/tree.png";
    Objects[2].canPlayerEnter = false;
    Objects[2].isInteractive = true;
    Objects[2].isPlayer = false;

    Objects[3].name = "LAKE";
    Objects[3].path = "Images/lake.png";
    Objects[3].canPlayerEnter = false;
    Objects[3].isInteractive = false;
    Objects[3].isPlayer = false;
}

void Init(){
    topleft_x_absolute = MAP_SIZE_X/2 - COLS/2;
    topleft_y_absolute = MAP_SIZE_Y/2 - ROWS/2;
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(window),WINDOW_WIDTH,WINDOW_HEIGHT);
    gtk_window_set_title(GTK_WINDOW(window),"Game");
    GtkWidget *grid = gtk_grid_new();
    Board = (Square***) malloc(COLS*sizeof(Square**));
    InitGameObjects();
    InitMap();
    InitScreen(grid);
    gtk_container_add(GTK_CONTAINER(window),GTK_WIDGET(grid));
    g_signal_connect (G_OBJECT (window), "destroy",G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect (G_OBJECT (window), "key_press_event", G_CALLBACK (OnKeyPress), NULL);
    gtk_widget_show(window);
    gtk_widget_show(grid);
    gtk_main();
}