#include "init.h"


int main(int argc, char* argv[]){
    srand(time(NULL));
    gtk_init(&argc,&argv);
    Init();
    gtk_main();
}