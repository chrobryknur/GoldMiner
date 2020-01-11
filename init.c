#include "init.h"

void InitScreen(GtkWidget* grid,GtkCssProvider *cssProvider){
    GtkWidget* BoardGrid = gtk_grid_new();
    gtk_grid_attach(GTK_GRID(grid),GTK_WIDGET(BoardGrid),0,0,WINDOW_WIDTH,WINDOW_HEIGHT);
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
            gtk_grid_attach(GTK_GRID(BoardGrid),GTK_WIDGET(Board[i][j]->image),Board[i][j]->left,
            Board[i][j]->top,Board[i][j]->width,Board[i][j]->height);
        }
    }

    GtkWidget* PowerGrid = gtk_grid_new();
    gtk_grid_attach(GTK_GRID(grid),GTK_WIDGET(PowerGrid),0,WINDOW_HEIGHT,PROGRESSBAR_WIDTH,LOWER_MENU_HEIGHT);
    powerLeft = gtk_progress_bar_new();
    gtk_style_context_add_provider(gtk_widget_get_style_context(powerLeft),GTK_STYLE_PROVIDER(cssProvider),GTK_STYLE_PROVIDER_PRIORITY_USER);
    gtk_grid_attach(GTK_GRID(PowerGrid),GTK_WIDGET(powerLeft),0,
    0,PROGRESSBAR_WIDTH,LOWER_MENU_HEIGHT/2);
    gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(powerLeft),1);

    hourLabel = gtk_label_new("HOUR");
    gtk_style_context_add_provider(gtk_widget_get_style_context(hourLabel),GTK_STYLE_PROVIDER(cssProvider),GTK_STYLE_PROVIDER_PRIORITY_USER);
    gtk_grid_attach(GTK_GRID(PowerGrid),GTK_WIDGET(hourLabel),0,LOWER_MENU_HEIGHT/2,PROGRESSBAR_WIDTH,LOWER_MENU_HEIGHT/2);


    GtkWidget* InventoryGrid = gtk_grid_new();
    gtk_grid_attach(GTK_GRID(grid),GTK_WIDGET(InventoryGrid),PROGRESSBAR_WIDTH,WINDOW_HEIGHT,INVENTORY_WIDTH,LOWER_MENU_HEIGHT);
    for(int i=0;i<INVENTORY_SIZE;i++){
        gtk_grid_attach(GTK_GRID(InventoryGrid),  GTK_WIDGET(Inventory[i].position->image), Inventory[i].position->left,
        Inventory[i].position->top, Inventory[i].position->width, Inventory[i].position->height);
    }

    GtkWidget* buttonsGrid = gtk_grid_new();
    GtkWidget* Buttons[3];
    Buttons[0] = gtk_button_new_with_label("Help");
    Buttons[1] = gtk_button_new_with_label("Reset");
    Buttons[2] = gtk_button_new_with_label("Exit");    
    g_signal_connect (G_OBJECT (Buttons[1]), "clicked", G_CALLBACK (Help), NULL);
    g_signal_connect (G_OBJECT (Buttons[2]), "clicked", G_CALLBACK (CleanUp), NULL);
    gtk_grid_attach(GTK_GRID(grid),GTK_WIDGET(buttonsGrid),PROGRESSBAR_WIDTH+INVENTORY_WIDTH,WINDOW_HEIGHT,WINDOW_WIDTH-PROGRESSBAR_WIDTH-INVENTORY_WIDTH,LOWER_MENU_HEIGHT);
    for(int i=0;i<3;i++){
        gtk_style_context_add_provider(gtk_widget_get_style_context(Buttons[i]),GTK_STYLE_PROVIDER(cssProvider),GTK_STYLE_PROVIDER_PRIORITY_USER);
        gtk_grid_attach(GTK_GRID(buttonsGrid),GTK_WIDGET(Buttons[i]),i*96,0,96,LOWER_MENU_HEIGHT);
    }
}

GameObject RandomObject(){
    int x = rand()%200;
    if(x<2) return Objects[3];
    if(x<5) return Objects[2];
    if(x<10) return Objects[4];
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

void InitItems(){
    AllItems = malloc(ALL_ITEMS_NUM*sizeof(Item));
    AllItems[0].id = 0;
    AllItems[0].name = "Empty";
    AllItems[0].quantity = 0;
    AllItems[0].path = "Images/noitem.png";
    AllItems[0].wearable = false;

    AllItems[1].id =  1;
    AllItems[1].name = "Fists";
    AllItems[1].quantity = 1;
    AllItems[1].path = "Images/fistt.png";
    AllItems[1].wearable = true;
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

    Objects[4].name = "GRASS2";
    Objects[4].path = "Images/grass2.png";
    Objects[4].canPlayerEnter = false;
    Objects[4].isInteractive = true;
    Objects[4].isPlayer = false;
    Objects[4].vulnerableToID = 0;
    Objects[4].healthPoints = 3;
}

void InitInventory(GtkCssProvider *cssProvider){
    EquippedItem = &AllItems[0];
    Inventory = malloc(INVENTORY_SIZE*sizeof(Item));
    for(int i=0;i<INVENTORY_SIZE;i++){
        if(i) Inventory[i] = AllItems[0];
        else Inventory[i] = AllItems[1];
        Inventory[i].position = malloc(sizeof(Square));
        Inventory[i].position->image = gtk_image_new();
        gtk_image_set_from_file(GTK_IMAGE(Inventory[i].position->image),Inventory[i].path);
        gtk_style_context_add_provider(gtk_widget_get_style_context(Inventory[i].position->image),GTK_STYLE_PROVIDER(cssProvider),GTK_STYLE_PROVIDER_PRIORITY_USER);
        Inventory[i].position->top = 0;
        Inventory[i].position->left = i*INVENTORY_PNG_SIZE;
        Inventory[i].position->width = INVENTORY_PNG_SIZE;
        Inventory[i].position->height  = INVENTORY_PNG_SIZE;
    }
}

void Init(){
    Power = 100.0;
    topleft_x_absolute = MAP_SIZE_X/2 - COLS/2;
    topleft_y_absolute = MAP_SIZE_Y/2 - ROWS/2;
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    GtkCssProvider *cssProvider =  gtk_css_provider_new();
    gtk_style_context_add_provider(gtk_widget_get_style_context(window),GTK_STYLE_PROVIDER(cssProvider),GTK_STYLE_PROVIDER_PRIORITY_USER);
    gtk_window_set_default_size(GTK_WINDOW(window),WINDOW_WIDTH,WINDOW_HEIGHT);
    gtk_window_set_resizable(GTK_WINDOW(window),FALSE);
    gtk_window_set_title(GTK_WINDOW(window),"Game");
    GtkWidget *grid = gtk_grid_new();
    Board = (Square***) malloc(COLS*sizeof(Square**));
    InitItems();
    InitInventory(cssProvider);
    InitGameObjects();
    InitMap();
    InitScreen(grid,cssProvider);
    g_timeout_add(100,UpdatePower,NULL);
    gtk_container_add(GTK_CONTAINER(window),GTK_WIDGET(grid));
    g_signal_connect (G_OBJECT (window), "key_press_event", G_CALLBACK (OnKeyPress), NULL);
    g_signal_connect (G_OBJECT (window), "destroy",G_CALLBACK(CleanUp), NULL);
    gtk_css_provider_load_from_path(cssProvider,"Style/gtk.css",NULL);
    gtk_widget_show_all(window);
    gtk_main();
}