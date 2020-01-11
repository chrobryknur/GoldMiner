#include "init.h"

void InitScreen(GtkWidget* grid,GtkCssProvider *cssProvider){
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
        }
    }
    for(int i=0;i<INVENTORY_SIZE;i++){
        gtk_grid_attach(GTK_GRID(grid),  GTK_WIDGET(Inventory[i].position->image), Inventory[i].position->left,
        Inventory[i].position->top, Inventory[i].position->width, Inventory[i].position->height);
    }
    GtkWidget *power = gtk_progress_bar_new();
    gtk_style_context_add_provider(gtk_widget_get_style_context(power),GTK_STYLE_PROVIDER(cssProvider),GTK_STYLE_PROVIDER_PRIORITY_USER);
    gtk_grid_attach(GTK_GRID(grid),GTK_WIDGET(power),1,
    WINDOW_HEIGHT,PROGRESSBAR_WIDTH,12);
    gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(power),0.5);

    GtkWidget* label = gtk_label_new("HOUR");
    gtk_style_context_add_provider(gtk_widget_get_style_context(label),GTK_STYLE_PROVIDER(cssProvider),GTK_STYLE_PROVIDER_PRIORITY_USER);
    gtk_grid_attach(GTK_GRID(grid),GTK_WIDGET(label),PROGRESSBAR_WIDTH/2,WINDOW_HEIGHT+16,1,12);
}

GameObject RandomObject(){
    int x = rand()%100;
    if(x<3) return Objects[3];
    if(x<10) return Objects[2];
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

void InitInventory(GtkCssProvider *cssProvider){
    for(int i=0;i<INVENTORY_SIZE;i++){
        Inventory[i].position = malloc(sizeof(Square));
        Inventory[i].position->image = gtk_image_new();
        if(i)
            gtk_image_set_from_file(GTK_IMAGE(Inventory[i].position->image),"Images/noitem.png");
        else
            gtk_image_set_from_file(GTK_IMAGE(Inventory[i].position->image),"Images/fistt.png");
        gtk_widget_set_name(GTK_WIDGET(Inventory[i].position->image),"inventory");
        gtk_style_context_add_provider(gtk_widget_get_style_context(Inventory[i].position->image),GTK_STYLE_PROVIDER(cssProvider),GTK_STYLE_PROVIDER_PRIORITY_USER);
        Inventory[i].position->top = WINDOW_HEIGHT;
        Inventory[i].position->left = i*INVENTORY_PNG_SIZE+PROGRESSBAR_WIDTH;
        Inventory[i].position->width = INVENTORY_PNG_SIZE;
        Inventory[i].position->height  = INVENTORY_PNG_SIZE;
        Inventory[i].name = "";
        Inventory[i].quantity = 0;
        Inventory[i].wearable = false; 
    }
}

void Init(){
    topleft_x_absolute = MAP_SIZE_X/2 - COLS/2;
    topleft_y_absolute = MAP_SIZE_Y/2 - ROWS/2;
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_name(GTK_WIDGET(window),".window");
    GtkCssProvider *cssProvider =  gtk_css_provider_new();
    gtk_style_context_add_provider(gtk_widget_get_style_context(window),GTK_STYLE_PROVIDER(cssProvider),GTK_STYLE_PROVIDER_PRIORITY_USER);
    gtk_window_set_default_size(GTK_WINDOW(window),WINDOW_WIDTH,WINDOW_HEIGHT);
    gtk_window_set_resizable(GTK_WINDOW(window),FALSE);
    gtk_window_set_title(GTK_WINDOW(window),"Game");
    GtkWidget *grid = gtk_grid_new();
    Board = (Square***) malloc(COLS*sizeof(Square**));
    InitInventory(cssProvider);
    InitGameObjects();
    InitMap();
    InitScreen(grid,cssProvider);
    gtk_container_add(GTK_CONTAINER(window),GTK_WIDGET(grid));
    g_signal_connect (G_OBJECT (window), "key_press_event", G_CALLBACK (OnKeyPress), NULL);
    g_signal_connect (G_OBJECT (window), "destroy",G_CALLBACK(gtk_main_quit), NULL);
    gtk_css_provider_load_from_path(cssProvider,"Style/gtk.css",NULL);
    gtk_widget_show_all(window);
    gtk_main();
}