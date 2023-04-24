#include "ui.h"
#include <assert.h>
#include <string.h>
#include <ncurses.h>
#include <unistd.h>

WINDOW *uiwindow = NULL;

//color map used to bright and dim the color of the line 

void set_colors();

int color_map[MAX_INTENSITY+1] = {1, 2, 2, 3, 3, 3, 3,3, 4, 4, 5,5, 5, 6};

bool init_ui(){

    //set the matric all to zero 

    for(int x=0;x< MAXX;x++){
        for(int y=0;y < MAXY;y++){
            Matrix[x][y].char_value = 0;
            Matrix[x][y].intensity = 0;

        }
    }

    uiwindow = initscr();
    if(uiwindow == NULL) return false;


    start_color();

    if(!has_colors() || !can_change_color() || COLOR_PAIR < 6 ){
        printf("[warning]: this program cant support");
        return false; 
    }

    set_colors();

    return true;
}


void cleanup_ui(){
delwin(uiwindow);
endwin();
refresh();
}

void show_matrix(){

        for(int x=0;x< MAXX;x++){
        for(int y=0;y < MAXY;y++){
             
            int intensity = Matrix[x][y].intensity;
            color_set(color_map[intensity], NULL);
            mvaddch(y, x, Matrix[x][y].char_value);

        }
    }
    refresh();

}

void set_colors(){
    for(int i=0; i < 8 ; i++){
        init_pair(i+1, i , COLOR_BLACK);
    }

    for(int i=0; i <= 5; i++){
        init_color(i, 0, i*200, 0);
    }
    
    init_color(6, 800, 1000, 800);
}