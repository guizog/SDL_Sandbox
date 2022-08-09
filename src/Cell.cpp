//
// Created by guizo on 21/07/2022.
//

#include "Cell.h"
#include <SDL.h>

extern SDL_Renderer* renderer;

 Cell::Cell() {
    type = CellType::EMPTYCELL;
    prop = CellProp::STATIC;
    hasMoved = flammable = isIgnited = false;
    timesMoved = 0;
    r = g = b = 0; a = 255;
    density = 0.0f;
    heat = 0;
}

Cell::Cell(CellType _type) {
    type = _type;
    if(type == CellType::EMPTYCELL || type == CellType::SOLID)
        prop = CellProp::STATIC;
    else if(type == CellType::WATER) {
        prop = CellProp::MOVE_DOWN_SIDE;
        density = 1.0f;
        flammable = false;
        isIgnited = false;
        heat = 0;
    }
    else if(type == CellType::SAND) {
        prop = CellProp::MOVE_DOWN_DIAGONAL;
        density = 1.3f;
        flammable = false;
        isIgnited = false;
        heat = 0;
    }
    else if(type == CellType::OIL){
        prop = CellProp::MOVE_DOWN_SIDE;
        density = 0.8f;
        flammable = true;
        isIgnited = false;
        heat = 0;
    }
}

void Cell::RenderCell(int x, int y) {

     SDL_FRect rect;
     rect.h = rect.w = 640.0f/50.0f;
     rect.x = x * (640.0f/50.0f);
     rect.y = y * (640.0f/50.0f);

     SDL_SetRenderDrawColor( renderer, r, g, b, a );

     SDL_RenderDrawRectF( renderer, &rect );
     SDL_RenderFillRectF(renderer, &rect);
}

Cell::~Cell() {

}

void Cell::SetCell(CellType type_) {
    if(type_ == CellType::SOLID){
        type = type_;
        prop = CellProp::STATIC;
        density = 10.0f;
        flammable = false;
        isIgnited = false;
        heat = 0;

        r = 200; g = 200; b = 200; a = 255;
    }
    else if(type_ == CellType::WATER){
        type = type_;
        prop = CellProp::MOVE_DOWN_SIDE;
        density = 1.0f;
        flammable = false;
        isIgnited = false;
        heat = 0;

        r = 0; g = 0; b = 255; a = 255;
    }
    else if(type_ == CellType::SAND){
        type = type_;
        prop = CellProp::MOVE_DOWN_DIAGONAL;
        density = 1.3f;
        flammable = false;
        isIgnited = false;
        heat = 0;

        r = 235; g = 200; b = 175; a = 255;
    }
    else if(type_ == CellType::EMPTYCELL){
        type = type_;
        prop = CellProp::STATIC;
    }
    else if(type_ == CellType::OIL){
        type = type_;
        prop = CellProp::MOVE_DOWN_SIDE;
        density = 0.8f;
        flammable = true;
        isIgnited = false;
        heat = 0;

        r = 55, g = 58, b = 54, a = 255;
    }
    else if(type_ == CellType::FIRE){
        type = type_;
        prop = CellProp::FIRE;
        density = 1.0f;
        flammable = false;
        isIgnited = false;
        heat = 100;

        r = 255, g = 0, b = 0, a = 255;
    }

}

void Cell::SetDensity(float density_) {
    if(density_ >= 0 && density_ <= 10.0f)
        this->density = density_;
    else
        this->density = (density_ > 10.0f) ? 10.0f : 0.0f;
}


