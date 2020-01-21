#include "init.h"

void InitBoardSquare(int x, int y){
    Board[x][y] = malloc(sizeof(Square*));
    Board[x][y]->image = gtk_image_new();
    gtk_image_set_from_file(GTK_IMAGE(Board[x][y]->image),Map[x+topleft_x_absolute][y+topleft_y_absolute].current.path);
    Board[x][y]->top = y*WINDOW_HEIGHT/ROWS;
    Board[x][y]->left = x*WINDOW_WIDTH/COLS;
    Board[x][y]->height = WINDOW_HEIGHT/ROWS;
    Board[x][y]->width = WINDOW_WIDTH/COLS;
}

void InitScreen(GtkWidget* grid,GtkCssProvider *cssProvider){
    GtkWidget* BoardGrid = gtk_grid_new();
    gtk_grid_attach(GTK_GRID(grid),GTK_WIDGET(BoardGrid),0,0,WINDOW_WIDTH,WINDOW_HEIGHT);
    for(int i=0;i<COLS;i++){
        Board[i] = (Square**)malloc(ROWS*sizeof(Square*));
        for(int j=0;j<ROWS;j++){
            InitBoardSquare(i,j);
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
    g_signal_connect (G_OBJECT (Buttons[0]), "clicked", G_CALLBACK (Help), NULL);
    g_signal_connect (G_OBJECT (Buttons[2]), "clicked", G_CALLBACK (CleanUp), NULL);
    gtk_grid_attach(GTK_GRID(grid),GTK_WIDGET(buttonsGrid),PROGRESSBAR_WIDTH+INVENTORY_WIDTH,WINDOW_HEIGHT,WINDOW_WIDTH-PROGRESSBAR_WIDTH-INVENTORY_WIDTH,LOWER_MENU_HEIGHT);
    for(int i=0;i<3;i++){
        gtk_style_context_add_provider(gtk_widget_get_style_context(Buttons[i]),GTK_STYLE_PROVIDER(cssProvider),GTK_STYLE_PROVIDER_PRIORITY_USER);
        gtk_grid_attach(GTK_GRID(buttonsGrid),GTK_WIDGET(Buttons[i]),i*96,0,96,LOWER_MENU_HEIGHT);
    }
}

GameObject RandomObject(){
    int x = g_random_int()%400;
    if(x<2) return Objects[3];
    if(x<5) return Objects[2];
    if(x<10) return Objects[4];
    if(x<15) return Objects[5];
    if(x<17) return  Objects[7];
    if(x<18) return Objects[8];
    if(x<19) return Objects[9];
    if(x<20) return Objects[10];
    if(x<21) return Objects[11];
    return Objects[1];
}

int DistFromCenter(int x, int y){
    return sqrt(x*x + y*y);
}

void InitMap(){
    for(int i=0;i<MAP_SIZE_X;i++){
        for(int j=0;j<MAP_SIZE_Y;j++){
            if(i == topleft_x_absolute + COLS/2 -1 && j == topleft_y_absolute+ROWS/2 -1){
                Map[i][j].current = Objects[0];
                Map[i][j].object = Objects[1];
            }
            else if(DistFromCenter(i-MAP_SIZE_X/2,j-MAP_SIZE_Y/2)>MAP_SIZE_X/2 - 30){
                Map[i][j].current = Map[i][j].object =  Objects[6];
            }
            else{
                Map[i][j].current = Map[i][j].object = RandomObject();
            }
        }
    }
}

Item CreateItem(char *name, char *path, int id, int quantity, bool wearable){
    Item a;
    a.name = name;
    a.path = path;
    a.id = id;
    a.quantity = quantity;
    a.wearable = wearable;
    return a;
}

void InitItems(){
    AllItems = malloc(ALL_ITEMS_NUM*sizeof(Item));
    AllItems[0] = CreateItem("Empty","../Images/noitem.png",0,0,false);
    AllItems[1] = CreateItem("Grass","../Images/grassitem.png",1,1,false);
    AllItems[2] = CreateItem("Rocks","../Images/smallrockitem.png",2,1,false);
    AllItems[3] = CreateItem("Stick","../Images/stickitem.png",3,1,false);
    AllItems[4] = CreateItem("Wood Log","../Images/woodlog.png",4,1,false);
    AllItems[5] = CreateItem("Gold Nugget","../Images/goldnugget.png",5,1,false);
    AllItems[6] = CreateItem("Dirt","../Images/dirt.png",6,1,false);
    AllItems[7] = CreateItem("Potion","../Images/potion.png",7,1,false);
    AllItems[8] = CreateItem("Axe","../Images/axe.png",8,1,true);
    AllItems[9] = CreateItem("AxeShape","../Images/axeempty.png",9,0,false);
    AllItems[10] = CreateItem("Pickaxe","../Images/pickaxe.png",10,1,true);
    AllItems[11] = CreateItem("PickaxeShape","../Images/pickaxeempty.png",11,1,false);
    AllItems[12] = CreateItem("ShovelShape","../Images/shovelempty.png",12,1,false);
    AllItems[13] = CreateItem("Shovel","../Images/shovel.png",13,1,true);
    
}

GameObject CreateObject(char *name, char *path,int id, bool canPlayerEnter, bool isInteractive, bool isPlayer, int vulnerableToID,int healthPoints){
    GameObject a;
    a.name = name;
    a.id = id;
    a.path = path;
    a.canPlayerEnter = canPlayerEnter;
    a.isInteractive = isInteractive;
    a.isPlayer = isPlayer;
    a.vulnerableToID = vulnerableToID;
    a.healthPoints = healthPoints;
    return a;
}

void InitGameObjects(){
    Objects[0] = CreateObject("PLAYER","../Images/player.png",0,true,true,true,0,0);
    Objects[1] = CreateObject("GRASS","../Images/grass.png",1,true,true,false,0,0);
    Objects[2] = CreateObject("TREE","../Images/tree.png",2,false,true,false,8,10);
    Objects[3] = CreateObject("LAKE","../Images/lake.png",3,false,false,false,0,0);
    Objects[4] = CreateObject("GRASS2","../Images/grass2.png",4,false,true,false,0,3);
    Objects[5] = CreateObject("ROCK","../Images/rock.png",5,false,true,false,10,10);
    Objects[6] = CreateObject("WAVE","../Images/wave.png",6,false,false,false,0,0);
    Objects[7] = CreateObject("STONE OF POWER","../Images/stone.png",7,false,true,false,0,1);
    Objects[8] = CreateObject("SMALL ROCK","../Images/smallrock.png",8,false,true,false,0,1);
    Objects[9] = CreateObject("STICK","../Images/stick.png",9,false,true,false,0,1);
    Objects[10] = CreateObject("GOLD ORE","../Images/goldore.png",10,false,true,false,10,20);
    Objects[11] = CreateObject("SOIL","../Images/soil.png",11,false,true,false,13,5);
}

void InitInventory(GtkCssProvider *cssProvider){
    EquippedItem = &AllItems[0];
    Inventory = malloc(INVENTORY_SIZE*sizeof(Item));
    Inventory[0]=AllItems[9]; //AxeShape
    Inventory[1]=AllItems[11]; //PickaxeShape
    Inventory[2]=AllItems[12]; //ShovelShape
    for(int i=0;i<INVENTORY_SIZE;i++){
        if(i>2)
            Inventory[i] = AllItems[0];
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
    g_timeout_add(1000,UpdatePower,NULL);
    gtk_container_add(GTK_CONTAINER(window),GTK_WIDGET(grid));
    g_signal_connect (G_OBJECT (window), "key_press_event", G_CALLBACK (OnKeyPress), NULL);
    g_signal_connect (G_OBJECT (window), "destroy",G_CALLBACK(CleanUp), NULL);
    gtk_css_provider_load_from_path(cssProvider,"../Style/gtk.css",NULL);
    gtk_widget_show_all(window);
    gtk_main();
}