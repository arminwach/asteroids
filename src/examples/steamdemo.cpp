// Steam locomotive demo
// (c) 2022 by Stefan Roettger

#include "gfx.h"
#include "scrollarea.h"
#include "math2d.h"

// the size of the game area
static int ax = 300, ay = 50;

// random integer value in the range [from, to]
int rand_range(int from, int to)
{
   int r = to - from;
   int v = rand() % (r + 1);
   return(v + from);
}

// render the rails for the steam loco
void render_rails()
{
   render_line(1, ay-3, ax-2, ay-3);

   for (int i=0; i<ax; i+=8)
      set_cell(i, ay-2, '#');
}

// 2D steam particle type
struct SteamType
{
   Vec2 p, v;
   float r;
};

// round-robin steam particle queue
static const int steam_max = 30;
static SteamType steam[steam_max];
static int steam_first = 0, steam_num = 0;

// add one steam particle to the round-robin queue
void add_steam_cloud(Vec2 p, Vec2 v, float r)
{
   int act;

   // check if the queue has space left
   if (steam_num < steam_max)
   {
      // locate the particle at the queue tail
      act = (steam_first + steam_num) % steam_max;
      steam_num++;
   }
   else
   {
      // locate the particle at the removed head
      act = steam_first;
      steam_first = (steam_first + 1) % steam_max;
   }

   // add particle at given location
   SteamType s = {p, v, r};
   steam[act] = s;
}

// render the steam particles
void render_steam()
{
   int act = steam_first;
   for (int i=0; i<steam_num; i++)
   {
      // get actual particle as reference
      SteamType *s = &steam[act];

      // render referenced particle
      int ch = -1;
      if (i < steam_num/4) ch = '.';
      render_circle(s->p.x, s->p.y, s->r, ch);

      // update particle position, velocity and radius
      s->p = add2(s->p, s->v);
      s->v = mul2s(s->v, 0.95);
      s->r += 0.1;

      act = (act + 1) % steam_max;
   }
}

int main(void)
{
   // init ASCII gfx
   init_gfx();

   // game area setup
   set_area_size(ax, ay);
   set_window_size(COLS, LINES);

   // render locomotive into game area
   fill_cell_area(ax/2-20, ay/2-5, 30, 10);
   fill_cell_area(ax/2+7, ay/2-10, 13, 15);
   fill_cell_area(ax/2+12, ay/2-9, 7, 4, ' ');
   fill_cell_area(ax/2-17, ay/2-9, 4, 4);
   render_ellipse(ax/2-10, ay/2+6, 4, 3, '*');
   render_ellipse(ax/2+10, ay/2+6, 4, 3, '*');
   render_ellipse(ax/2, ay/2+6, 4, 3, '*');

   // get locomotive data from game area
   int sx = 40, sy = 20;
   int *data = get_cell_area(ax/2-20, ay/2-10, sx, sy, ' ');
   enable_sprite(1, sx, sy);
   set_sprite_data(1, sx, sy, data);
   clear_area();

   // game loop
   int ch;
   do
   {
      // animate locomotive position
      static int px = ax/2, py = ay - sy/2-3;
      static int vx = -1, vy = 0;
      static bool stopped = false;
      if (px <= sx/2+1 || px >= ax-1 - sx/2-1) vx = -vx;
      px += vx;
      py += vy;

      // create steam cloud particles
      static int count = 0;
      if (count++%8 == 0)
      {
         float rx = 0.1*rand_range(-3, 3);
         Vec2 p = vec2(px - sx/2 + 5, py - sy/2 - 1);
         Vec2 v = vec2(0.5*vx + rx, -1);
         add_steam_cloud(p, v, 1);
      }

      // render locomotive with steam clouds
      clear_area();
      render_rails();
      center_sprite_position(1, px, py);
      render_steam();

      // scroll game area
      center_window(px, py);

      // refresh screen
      refresh();

      // wait until next frame
      msleep(50); // 50 ms = 20 fps

      // get pressed key
      ch = tolower(getch());

      // check pressed key
      if (ch == ' ')
      {
         stopped = !stopped;
         if (stopped) vx = 0;
         else vx = -1;
      }
   }
   while (ch != 'q');

   // release allocated memory
   release_area();

   // exit ASCII gfx
   exit_gfx();

   return(0);
}
