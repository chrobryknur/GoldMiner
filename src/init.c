#include "init.h"

void InitBoardSquare(int x, int y){
    Game->Board[x][y] = malloc(sizeof(Square*));
    Game->Board[x][y]->image = gtk_image_new();
    gtk_image_set_from_file(GTK_IMAGE(Game->Board[x][y]->image),Game->GameOptions->Map[x+Game->topleft_x_absolute][y+Game->topleft_y_absolute].current.path);
    Game->Board[x][y]->top = y*WINDOW_HEIGHT/ROWS;
    Game->Board[x][y]->left = x*WINDOW_WIDTH/COLS;
    Game->Board[x][y]->height = WINDOW_HEIGHT/ROWS;
    Game->Board[x][y]->width = WINDOW_WIDTH/COLS;
}

void InitScreen(){
    Game->GtkGameState->Grid= gtk_grid_new();
    GtkWidget* BoardGrid = gtk_grid_new();
    gtk_widget_set_name(BoardGrid, "boardGrid");
    gtk_grid_attach(GTK_GRID(Game->GtkGameState->Grid),GTK_WIDGET(BoardGrid),0,0,WINDOW_WIDTH,WINDOW_HEIGHT);
    for(int i=0;i<COLS;i++){
        Game->Board[i] = (Square**)malloc(ROWS*sizeof(Square*));
        for(int j=0;j<ROWS;j++){
            InitBoardSquare(i,j);
            gtk_grid_attach(GTK_GRID(BoardGrid),GTK_WIDGET(Game->Board[i][j]->image),Game->Board[i][j]->left,
            Game->Board[i][j]->top,Game->Board[i][j]->width,Game->Board[i][j]->height);
        }
    }


    GtkWidget* PowerGrid = gtk_grid_new();
    gtk_grid_attach(GTK_GRID(Game->GtkGameState->Grid),GTK_WIDGET(PowerGrid),0,WINDOW_HEIGHT,PROGRESSBAR_WIDTH,LOWER_MENU_HEIGHT);
    Game->GtkGameState->powerLeft = gtk_progress_bar_new();
    gtk_grid_attach(GTK_GRID(PowerGrid),GTK_WIDGET(Game->GtkGameState->powerLeft),0,
    0,PROGRESSBAR_WIDTH,LOWER_MENU_HEIGHT/2);
    gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(Game->GtkGameState->powerLeft),1);

    Game->GtkGameState->hourLabel = gtk_label_new("Score: 0");
    gtk_widget_set_name(Game->GtkGameState->hourLabel, "hourLabel");
    gtk_grid_attach(GTK_GRID(PowerGrid),GTK_WIDGET(Game->GtkGameState->hourLabel),0,LOWER_MENU_HEIGHT/2,PROGRESSBAR_WIDTH,LOWER_MENU_HEIGHT/2);


    Game->GtkGameState->InventoryGrid = gtk_grid_new();
    Game->GtkGameState->ItemLabels = malloc(INVENTORY_SIZE*sizeof(GtkWidget*));
    gtk_grid_attach(GTK_GRID(Game->GtkGameState->Grid),GTK_WIDGET(Game->GtkGameState->InventoryGrid),PROGRESSBAR_WIDTH,WINDOW_HEIGHT,INVENTORY_WIDTH,LOWER_MENU_HEIGHT);
    for(int i=0;i<INVENTORY_SIZE;i++){
        gtk_grid_attach(GTK_GRID(Game->GtkGameState->InventoryGrid),  GTK_WIDGET(Game->Inventory[i].position->image), Game->Inventory[i].position->left,
        Game->Inventory[i].position->top, Game->Inventory[i].position->width, Game->Inventory[i].position->height);
        if(strcmp(Game->Inventory[i].name,"Empty"))
            Game->GtkGameState->ItemLabels[i] = gtk_label_new(Game->Inventory[i].name);
        else Game->GtkGameState->ItemLabels[i] = gtk_label_new("");
        gtk_grid_attach(GTK_GRID(Game->GtkGameState->InventoryGrid),GTK_WIDGET(Game->GtkGameState->ItemLabels[i]),Game->Inventory[i].position->left,Game->Inventory[i].position->top+48,48,24);
    }

    GtkWidget* buttonsGrid = gtk_grid_new();
    GtkWidget* Buttons[3];
    Buttons[0] = gtk_button_new_with_label("Help");
    Buttons[1] = gtk_button_new_with_label("Reset");
    Buttons[2] = gtk_button_new_with_label("Exit");    
    g_signal_connect (G_OBJECT (Buttons[0]), "clicked", G_CALLBACK (Help), NULL);
    g_signal_connect (G_OBJECT (Buttons[2]), "clicked", G_CALLBACK (CleanUp), NULL);
    gtk_grid_attach(GTK_GRID(Game->GtkGameState->Grid),GTK_WIDGET(buttonsGrid),PROGRESSBAR_WIDTH+INVENTORY_WIDTH,WINDOW_HEIGHT,WINDOW_WIDTH-PROGRESSBAR_WIDTH-INVENTORY_WIDTH,LOWER_MENU_HEIGHT);
    for(int i=0;i<3;i++){
        gtk_grid_attach(GTK_GRID(buttonsGrid),GTK_WIDGET(Buttons[i]),i*96,0,96,LOWER_MENU_HEIGHT);
    }
}

GameObject RandomObject(){
    int x = g_random_int()%400;
    if(x<2) return Game->GameOptions->Objects[3];
    if(x<5) return Game->GameOptions->Objects[2];
    if(x<10) return Game->GameOptions->Objects[4];
    if(x<15) return Game->GameOptions->Objects[5];
    if(x<17) return Game->GameOptions->Objects[7];
    if(x<18) return Game->GameOptions->Objects[8];
    if(x<19) return Game->GameOptions->Objects[9];
    if(x<20) return Game->GameOptions->Objects[10];
    if(x<21) return Game->GameOptions->Objects[11];
    return Game->GameOptions->Objects[1];
}

int DistFromCenter(int x, int y){
    return sqrt(x*x + y*y);
}

void InitMap(){
    Game->GameOptions->Map = malloc(MAP_SIZE_X*sizeof(MapSquare*));
    for(int i=0;i<MAP_SIZE_X;i++){
        Game->GameOptions->Map[i] = malloc(MAP_SIZE_Y*sizeof(MapSquare));
        for(int j=0;j<MAP_SIZE_Y;j++){
            if(i == Game->topleft_x_absolute + COLS/2-1 && j == Game->topleft_y_absolute+ROWS/2 -1){
                Game->GameOptions->Map[i][j].current = Game->GameOptions->Objects[(int)PLAYEROBJECT_ID];
                Game->GameOptions->Map[i][j].object = Game->GameOptions->Objects[(int)GRASS1OBJECT_ID];
            }
            else if(DistFromCenter(i-MAP_SIZE_X/2,j-MAP_SIZE_Y/2)>MAP_SIZE_X/2 - 30){
                Game->GameOptions->Map[i][j].current = Game->GameOptions->Map[i][j].object =  Game->GameOptions->Objects[(int)WAVEOBJECT_ID];
            }
            else{
                Game->GameOptions->Map[i][j].current = Game->GameOptions->Map[i][j].object = RandomObject();
            }
        }
    }
}

Item CreateItem(char *name, char *path, int id, int quantity, bool wearable,int position_in_inventory){
    Item a;
    a.name = name;
    a.path = path;
    a.id = id;
    a.quantity = quantity;
    a.wearable = wearable;
    a.position_in_inventory = position_in_inventory;
    return a;
}

void InitItems(){
    Game->GameOptions->AllItems[0] = CreateItem("Empty","./Images/noitem.png",NO_ITEM_ID,0,false,0);
    Game->GameOptions->AllItems[1] = CreateItem("Grass","./Images/grassitem.png",GRASSITEM_ID,1,false,9);
    Game->GameOptions->AllItems[2] = CreateItem("Rocks","./Images/smallrockitem.png",ROCKITEM_ID,1,false,8);
    Game->GameOptions->AllItems[3] = CreateItem("Stick","./Images/stickitem.png",STICKITEM_ID,1,false,7);
    Game->GameOptions->AllItems[4] = CreateItem("Wood Log","./Images/woodlog.png",WOODLOGITEM_ID,1,false,6);
    Game->GameOptions->AllItems[5] = CreateItem("Gold Nugget","./Images/goldnugget.png",GOLDITEM_ID,1,false,4);
    Game->GameOptions->AllItems[6] = CreateItem("Dirt","./Images/dirt.png",DIRTITEM_ID,1,false,5);
    Game->GameOptions->AllItems[7] = CreateItem("Potion","./Images/potion.png",POTIONITEM_ID,1,false,3);
    Game->GameOptions->AllItems[8] = CreateItem("Axe","./Images/axe.png",AXEITEM_ID,1,true,0);
    Game->GameOptions->AllItems[9] = CreateItem("Axe","./Images/axeempty.png",NO_AXEITEM_ID,0,false,0);
    Game->GameOptions->AllItems[10] = CreateItem("Pickaxe","./Images/pickaxe.png",PICKAXEITEM_ID,1,true,1);
    Game->GameOptions->AllItems[11] = CreateItem("Pickaxe","./Images/pickaxeempty.png",NO_PICKAXEITEM_ID,1,false,1);
    Game->GameOptions->AllItems[12] = CreateItem("Shovel","./Images/shovelempty.png",NO_SHOVELITEM_ID,1,false,2);
    Game->GameOptions->AllItems[13] = CreateItem("Shovel","./Images/shovel.png",SHOVELITEM_ID,1,true,2);
    
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
    Game->GameOptions->Objects[0] = CreateObject("PLAYER","./Images/player.png",(int)PLAYEROBJECT_ID,true,true,true,(int)NO_ITEM_ID,0);
    Game->GameOptions->Objects[1] = CreateObject("GRASS","./Images/grasscp.png",(int)GRASS1OBJECT_ID,true,true,false,(int)NO_ITEM_ID,0);
    Game->GameOptions->Objects[2] = CreateObject("TREE","./Images/tree.png",(int)TREEOBJECT_ID,false,true,false,(int)AXEITEM_ID,10);
    Game->GameOptions->Objects[3] = CreateObject("LAKE","./Images/lake.png",(int)LAKEOBJECT_ID,false,false,false,(int)NO_ITEM_ID,0);
    Game->GameOptions->Objects[4] = CreateObject("GRASS2","./Images/grass2.png",(int)GRASS2OBJECT_ID,false,true,false,(int)NO_ITEM_ID,3);
    Game->GameOptions->Objects[5] = CreateObject("ROCK","./Images/rock.png",(int)ROCKOBJECT_ID,false,true,false,(int)PICKAXEITEM_ID,10);
    Game->GameOptions->Objects[6] = CreateObject("WAVE","./Images/wave.png",(int)WAVEOBJECT_ID,false,false,false,(int)NO_ITEM_ID,0);
    Game->GameOptions->Objects[7] = CreateObject("STONE OF POWER","./Images/stone.png",(int)STONEOFPOWEROBJECT_ID,false,true,false,(int)NO_ITEM_ID,1);
    Game->GameOptions->Objects[8] = CreateObject("SMALL ROCK","./Images/smallrock.png",(int)SMALLROCKOBJECT_ID,false,true,false,(int)NO_ITEM_ID,1);
    Game->GameOptions->Objects[9] = CreateObject("STICK","./Images/stick.png",(int)STICKOBJECT_ID,false,true,false,(int)NO_ITEM_ID,1);
    Game->GameOptions->Objects[10] = CreateObject("GOLD ORE","./Images/goldore.png",(int)GOLDOREOBJECT_ID,false,true,false,(int)PICKAXEITEM_ID,20);
    Game->GameOptions->Objects[11] = CreateObject("SOIL","./Images/soil.png",(int)SOILOBJECT_ID,false,true,false,(int)SHOVELITEM_ID,5);
}

void InitInventory(){
    Game->EquippedItem = &Game->GameOptions->AllItems[0];
    Game->Inventory = malloc(INVENTORY_SIZE*sizeof(Item));
    Game->Inventory[0]=Game->GameOptions->AllItems[NO_AXEITEM_ID];
    Game->Inventory[1]=Game->GameOptions->AllItems[NO_PICKAXEITEM_ID];
    Game->Inventory[2]=Game->GameOptions->AllItems[NO_SHOVELITEM_ID];
    for(int i=0;i<INVENTORY_SIZE;i++){
        if(i>2)
        Game->Inventory[i] = Game->GameOptions->AllItems[NO_ITEM_ID];
        Game->Inventory[i].position = malloc(sizeof(Square));
        Game->Inventory[i].position->image = gtk_image_new();
        gtk_image_set_from_file(GTK_IMAGE(Game->Inventory[i].position->image),Game->Inventory[i].path);
        Game->Inventory[i].position->top = 0;
        Game->Inventory[i].position->left = i*INVENTORY_PNG_SIZE;
        Game->Inventory[i].position->width = INVENTORY_PNG_SIZE;
        Game->Inventory[i].position->height  = INVENTORY_PNG_SIZE;
    }
}

void InitStatic(){
    Game->GameOptions = malloc(sizeof(GameStaticOptions));
    Game->GameOptions->Objects = malloc(GAME_OBJECTS_NUM*sizeof(GameObject));
    InitGameObjects();
    Game->GameOptions->AllItems=malloc(ALL_ITEMS_NUM*sizeof(Item));
    InitItems();
}

void InitDynamic(){
    Game->topleft_x_absolute = MAP_SIZE_X/2 - COLS/2;
    Game->topleft_y_absolute = MAP_SIZE_Y/2 - ROWS/2;
    Game->Power = 100.0;
    Game->Score = 0;
    Game->EquippedItem = NULL;
    InitMap();
    InitInventory();
    Game->Board = (Square***) malloc(COLS*sizeof(Square**));
}

void InitGtk(){
    Game->GtkGameState = malloc(sizeof(GtkState));
    Game->GtkGameState->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    Game->GtkGameState->cssProvider = gtk_css_provider_new();
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(Game->GtkGameState->cssProvider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    gtk_window_set_default_size(GTK_WINDOW(Game->GtkGameState->window),WINDOW_WIDTH,WINDOW_HEIGHT);
    gtk_window_set_resizable(GTK_WINDOW(Game->GtkGameState->window),FALSE);
    gtk_window_set_title(GTK_WINDOW(Game->GtkGameState->window),"Game");
    InitScreen();
    gtk_container_add(GTK_CONTAINER(Game->GtkGameState->window),GTK_WIDGET(Game->GtkGameState->Grid));
    g_signal_connect (G_OBJECT (Game->GtkGameState->window), "key_press_event", G_CALLBACK (OnKeyPress), NULL);
    g_signal_connect (G_OBJECT (Game->GtkGameState->window), "destroy",G_CALLBACK(CleanUp), NULL);
    gtk_css_provider_load_from_path(Game->GtkGameState->cssProvider,"./Style/gtk.css",NULL);
    gtk_widget_show_all(Game->GtkGameState->window);
    g_timeout_add(1000,UpdatePower,NULL);
}

void Init(){
    Game = malloc(sizeof(GameState));
    InitStatic();
    InitDynamic();
    InitGtk();
    gtk_main();

}