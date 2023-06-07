// ASCII GFX example
// (c) 2020 by Stefan Roettger

#include "gfx.h"
#include "gridfont.h"
#include "sound.h"

static float max_x = 0, max_y = 0; // screen size

int intro()
{
   // init ASCII gfx
   init_gfx();
   init_color();

   // init sound
   sound_init();

   // print screen size
   // * LINES and COLS are predefined macros
   move(0, 0); // position cursor at origin
   //printw("screen size is %dx%d\n", COLS, LINES);
   hline(ACS_HLINE, (COLS*0.9));

   // get screen size
   // * a preceding & as used by the call-by-ref convention is not required
   // * since getmaxyx is a preprocessor macro
   getmaxyx(stdscr, max_y, max_x); // & not required

   // print centered text with 5x3 grid font
   const char text[] = "ASSSTEROIDS";
   int tx = max_x/2;
   int ty = (max_y-4)/2+1;
   init_grid_font();
   draw_grid_text(ty - get_grid_char_lines()/2, tx - strlen(text)*get_grid_char_cols()/2, text);

   // print help text
   const char help[] = "PRESS Q TO START";
   use_attr_bold(); // enable bold attribute
   use_attr_blink(); // enable blink attribute
   use_color(2); // index 2 equals red
   mvprintw((max_y*0.6), (max_x*0.45) , help);
   use_color(); // default equals white
   use_attr_normal(); // disable all attributes

   // draw horizontal line
   mvhline((max_y*0.85), 0, ACS_HLINE, (max_x*0.95));
   mvhline((max_y*0.75), (max_x*0.2) , ACS_HLINE, max_x);
   mvhline((max_y*0.95), 0, ACS_HLINE, (max_x*0.4));
   mvhline((max_y*0.95), (max_x*0.5), ACS_HLINE, max_x);
   mvhline((max_y*0.7), 0, ACS_HLINE, (max_x*0.3));
   mvhline((max_y*0.15), (max_x*0.1) , ACS_HLINE, max_x);
   mvhline((max_y*0.05), 0, ACS_HLINE, (max_x*0.5));
   mvhline((max_y*0.05), (max_x*0.6), ACS_HLINE, max_x);
   mvhline((max_y*0.2), 0, ACS_HLINE, (max_x*0.4));
   mvhline((max_y*0.3), (max_x*0.7) , ACS_HLINE, max_x);
   
   
   
   //draw Stars
   mvaddch((max_y*0.1),(max_x*0.15),'*');
   mvaddch((max_y*0.23),(max_x*0.9),'+');
   mvaddch((max_y*0.16),(max_x*0.45),'*');
   mvaddch((max_y*0.18),(max_x*0.1),'+');
   mvaddch((max_y*0.9),(max_x*0.2),'*');
   mvaddch((max_y*0.82),(max_x*0.15),'+');
   mvaddch((max_y*0.9),(max_x*0.85),'*');
   mvaddch((max_y*0.72),(max_x*0.9),'+');
   
   // terminal bell
   beep();

   // play WAV sound
   sound_play("titlemusic.wav",0.1);

   // refresh screen
   refresh();

   // check for pressed keys
   while (tolower(getch()) != 'q') msleep(1);

   // exit sound
   sound_exit();

   // exit ASCII gfx
   exit_gfx();

   return(0);
}
