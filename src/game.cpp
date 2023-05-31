#include "game.h"
#include "util.h"
#include "grfx.h"
#include "direction.h"
#include <curses.h>

struct Vector {
    int x;
    int y;
};

enum Direction {
    NORTH,
    WEST,
    SOUTH,
    EAST
}

static Vector position;

void moveShip(char c){
    
    currentDirection = evaluate_direction(c);
    
    switch(currentDirection) {
        case NORTH: 
            directionVector.dx = 1;
            directionVector.dy = 0;
        case WEST:
            directionVector.dx = 0;
            directionVector.dy = 1;
        case SOUTH:
            directionVector.dx = -1;
            directionVector.dy = 0;
        case EAST:
            directionVector.dx = 0;
            directionVector.dy = -1;
    }
    
    position.x += currentDirection.x;
    position.y += currentDirection.y;
    
    mvprintw(position.y, position.x, "*");
    
}

Direction evaluate_direction(char c) {
    switch(currentDirection) {
        case NORTH: 
            if (c == 'a') 
                return WEST;
            else if (c == 's') {
                return EAST;                
        case WEST:
            if (c == 'a') 
                return SOUTH;
            else if (c == 's') {
                return NORTH;             
        case SOUTH:
            if (c == 'a') 
                return EAST;
            else if (c == 's') {
                return WEST;              
        case EAST:
            if (c == 'a') 
                return NORTH;
            else if (c == 's') {
                return SOUTH;  
    }
}

void game_loop(){
    mvprintw(y, x, "*");
    
    
    while(TRUE){
        clear();
        refresh();
        
        int c = getch();
        moveShip(c);
        
        if(c == 'q'){
            return;
        }   
        msleep(50);
    }

}
