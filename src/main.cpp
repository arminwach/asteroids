// ASCII GFX example
// (c) 2020 by Stefan Roettger

#include "gfx.h"
#include "gridfont.h"
#include "sound.h"
#include <curses.h>
#include "intro.h"


int main()
{
    init_gfx();
    clear();
    intro();
    //game_loop();
    refresh();
    exit_gfx();
    return(0);
}
