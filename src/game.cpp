#include "game.h"
#include "util.h"
#include <curses.h>

struct Vector {
    int x;
    int y;
};

enum Direction {
    NORTH,
    WEST,
    SOUTH,
    EAST,
    NOMOTION
};

static Vector position;

static Direction currentDirection;

Direction evaluate_direction(char c);

void init() {
    currentDirection = NOMOTION;
    position.x = 20;
    position.y = 15;
}

void moveShip(char c){
    
    currentDirection = evaluate_direction(c);
    
    Vector directionVector = {0,0};
    
    switch(currentDirection) {
        case NOMOTION:
            directionVector.x = 0;
            directionVector.y = 0;
            break;
        case NORTH: 
            directionVector.x = 1;
            directionVector.y = 0;
            break;
        case WEST:
            directionVector.x = 0;
            directionVector.y = 1;
            break;
        case SOUTH:
            directionVector.x = -1;
            directionVector.y = 0;
            break;
        case EAST:
            directionVector.x = 0;
            directionVector.y = -1;
            break;
    }
    
    position.x += directionVector.x;
    position.y += directionVector.y;
    
    mvprintw(position.y, position.x, "*");
    
}

Direction evaluate_direction(char c) {
    switch(currentDirection) {
        case NORTH: 
            if (c == 'a') 
                return WEST;
            else if (c == 's') 
                return EAST;   
            break;
        case WEST:
            if (c == 'a') 
                return SOUTH;
            else if (c == 's') 
                return NORTH;    
            break;
        case SOUTH:
            if (c == 'a') 
                return EAST;
            else if (c == 's') 
                return WEST;        
            break;
        case EAST:
            if (c == 'a') 
                return NORTH;
            else if (c == 's') 
                return SOUTH;
            break;
        case NOMOTION:
            if (c == 'w')
                return NORTH;
            break;
            
    }
    return currentDirection;
}

void game_loop(){
    
    init();
    
    
    while(TRUE){
        clear();
        
        int c = getch();
        moveShip(c);
        
        if(c == 'q'){
            return;
        }   
        refresh();
        msleep(50);
    }

}
