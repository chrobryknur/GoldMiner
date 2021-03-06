#include "common.h"

void EquipItem(int index_in_inventory){
    Game->EquippedItem = &Game->Inventory[index_in_inventory];
        gtk_widget_set_name(GTK_WIDGET(Game->GtkGameState->ItemLabels[index_in_inventory]), "activeLabel");
    for(int i=0;i<INVENTORY_SIZE;i++){
        if(i!=index_in_inventory)
            gtk_widget_set_name(GTK_WIDGET(Game->GtkGameState->ItemLabels[i]), "unactiveLabel");
    }
}

void OnKeyPress(GtkWidget *widget, GdkEventKey *event){
    switch(event->keyval){
    case 'w':
        UpdateScreen(UP);
        break;
    case 'a':
        UpdateScreen(LEFT);
        break;
    case 's':
        UpdateScreen(DOWN);
        break;
    case 'd':
        UpdateScreen(RIGHT);
        break;
    case 65361: //LeftArrow
        Attack(LEFT);
        break;
    case 65363: //RightArrow
        Attack(RIGHT);
        break;
    case 65362: //UpArrow
        Attack(UP);
        break;
    case 65364: //DownArrow
        Attack(DOWN);
        break;

    case '1':
        if(Game->Inventory[Game->GameOptions->AllItems[(int)AXEITEM_ID].position_in_inventory].id!=(int)AXEITEM_ID){
            CraftItem((int)AXEITEM_ID);
        }
        else {
            EquipItem(Game->GameOptions->AllItems[(int)AXEITEM_ID].position_in_inventory);
        }
        break;
    case '2':
        if(Game->Inventory[Game->GameOptions->AllItems[(int)PICKAXEITEM_ID].position_in_inventory].id!=(int)PICKAXEITEM_ID){
            CraftItem((int)PICKAXEITEM_ID);
        }
        else EquipItem(Game->GameOptions->AllItems[(int)PICKAXEITEM_ID].position_in_inventory);
        break;
    case '3':
        if(Game->Inventory[Game->GameOptions->AllItems[(int)SHOVELITEM_ID].position_in_inventory].id!=(int)SHOVELITEM_ID){
            CraftItem((int)SHOVELITEM_ID);
        }
        else EquipItem(Game->GameOptions->AllItems[(int)SHOVELITEM_ID].position_in_inventory);
        break;
    case '4':
        UsePotion();
        break;
    }
}

void EndGame(){
    if(Game->Power>0){
        Game->Power=-1;
        return;
    }
    Game->GtkGameState->scoreWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(Game->GtkGameState->scoreWindow),"You lost all of your power!");
    gtk_window_set_default_size(GTK_WINDOW(Game->GtkGameState->scoreWindow),150,30);
    gtk_window_set_resizable(GTK_WINDOW(Game->GtkGameState->scoreWindow),FALSE);
    GtkWidget*  grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(Game->GtkGameState->scoreWindow),GTK_WIDGET(grid));
    char str[30];
    char scoreNumToString[5];
    sprintf(scoreNumToString,"%d",Game->Score);
    strcpy(str,"You have collected ");
    strcat(str,scoreNumToString);
    strcat(str," gold.");
    GtkWidget* scoreLabel = gtk_label_new(str);
    GtkWidget* resetButton = gtk_button_new_with_label("Reset");
    GtkWidget* quitButton = gtk_button_new_with_label("Exit");
    g_signal_connect (G_OBJECT (resetButton), "clicked", G_CALLBACK (Reset),NULL);
    g_signal_connect (G_OBJECT (quitButton), "clicked", G_CALLBACK (CleanUp), NULL);
    g_signal_connect (G_OBJECT (Game->GtkGameState->scoreWindow), "destroy", G_CALLBACK(gtk_main_quit),NULL);
    gtk_grid_attach(GTK_GRID(grid),GTK_WIDGET(scoreLabel),0,10,200,50);
    gtk_grid_attach(GTK_GRID(grid),GTK_WIDGET(resetButton),0,100,100,50);
    gtk_grid_attach(GTK_GRID(grid),GTK_WIDGET(quitButton),100,100,100,50);
    gtk_widget_set_name(Game->GtkGameState->scoreWindow, "scoreWindow");
    gtk_window_set_position(GTK_WINDOW(Game->GtkGameState->scoreWindow),GTK_WIN_POS_CENTER);
    gtk_widget_hide(Game->GtkGameState->window);
    gtk_widget_show_all(Game->GtkGameState->scoreWindow);
}

void Reset(){
    if(Game->GtkGameState->scoreWindow)
        gtk_window_close(GTK_WINDOW(Game->GtkGameState->scoreWindow));
    for(int i=0;i<COLS;i++){
        for(int j=0;j<ROWS;j++)
            free(Game->Board[i][j]);
        free(Game->Board[i]);
    }
    free(Game->Board);
    free(Game->GtkGameState->ItemLabels);
    for(int i=0;i<MAP_SIZE_X;i++)
        free(Game->GameOptions->Map[i]);
    free(Game->GameOptions->Map);
    for(int i=0;i<INVENTORY_SIZE;i++)
        free(Game->Inventory[i].position);
    free(Game->Inventory);
    free(Game->GameOptions->Objects);
    free(Game->GameOptions->AllItems);
    free(Game->GameOptions);
    if(GTK_IS_BIN(Game->GtkGameState->window)) {
        GtkWidget *child = gtk_bin_get_child(GTK_BIN(Game->GtkGameState->window));
        gtk_widget_destroy(child);
    }
    gtk_widget_hide(Game->GtkGameState->window);
    free(Game->GtkGameState);
    free(Game);
    Init();
}

void CleanUp(){
    for(int i=0;i<COLS;i++){
        for(int j=0;j<ROWS;j++)
            free(Game->Board[i][j]);
        free(Game->Board[i]);
    }
    free(Game->Board);
    free(Game->GtkGameState->ItemLabels);
    for(int i=0;i<MAP_SIZE_X;i++)
        free(Game->GameOptions->Map[i]);
    free(Game->GameOptions->Map);
    for(int i=0;i<INVENTORY_SIZE;i++)
        free(Game->Inventory[i].position);
    free(Game->Inventory);
    free(Game->GameOptions->Objects);
    free(Game->GameOptions->AllItems);
    free(Game->GameOptions);
    free(Game->GtkGameState);
    free(Game);
    gtk_main_quit();
    exit(1);
}

void Help(){
    GtkWidget *helpWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(helpWindow),"Help");
    gtk_window_set_resizable(GTK_WINDOW(helpWindow),FALSE);
    gtk_widget_set_name(helpWindow,"helpWindow");
    char *str = "Walking: WASD\nAttack: Arrowkeys\nCrafting/equipping items:\n1 - Axe (stick, stone, grass)\n2 - Pickaxe (wood log, stone, grass)\n3 - Shovel (stick, wood log, stone)\n4 - Use Potion\n\nYour goal is to collect as much gold  as possible.\nIn order to do that you have to use the implemented crafting system.\nSome objects may not be vulnerable to the currently equipped item.\n\nKeep an eye on the Power Bar!\nIf it drops to zero the game will end.\nTo refill the power you need to find a Stone of Power\nand drink potion that drops from it.\n\nEverytime you attack an object you lose a small amount of power.\nKeep in mind that some objects are hardy,\nso you have to hit them multiple times.";
    GtkWidget *helpLabel = gtk_label_new(str);
    gtk_container_add(GTK_CONTAINER(helpWindow),GTK_WIDGET(helpLabel));
    gtk_widget_show_all(helpWindow);
}
