//
// Created by guizo on 21/07/2022.
//

#include "SandWorld.h"
#include <random>

extern SDL_Renderer* renderer;

bool InBounds(int x, int y){
        return (x >= 0 && x < 50 && y >= 0 && y < 50);
}

int RNG(int min, int max){
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(min,max);
    return dist(rng);
}

SandWorld::SandWorld() {
    running = true;
    currType = CellType::WATER;
}

SandWorld::~SandWorld() {

}

void SandWorld::DrawMatrix() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    for(int x = 0; x < 50; x++){
        for(int y = 0; y < 50; y++){
            if(matrix[y][x].GetType() != CellType::EMPTYCELL){
                matrix[y][x].RenderCell(x, y);
                matrix[y][x].hasMoved = false;
            }
        }
    }
    SDL_RenderPresent(renderer);
}

void SandWorld::Step() {
    for(int x = 0; x < 50; x++){
        for( int y = 0; y < 50; y++){
            if(matrix[y][x].GetType() != CellType::EMPTYCELL && !matrix[y][x].hasMoved)
                MoveCell(matrix[y][x], x, y);
        }
    }
}

//-----------------------------------------------------------------

void SandWorld::HandleEvents() {
    SDL_Event event;
    while(SDL_PollEvent(&event) != 0) {
        switch (event.type) {
            case SDL_KEYDOWN:
                GetKeyboard(event.key);
                break;
            case SDL_MOUSEBUTTONDOWN:
                CreateCell(event.button);
                break;
            case SDL_QUIT:
                running = false;
                break;
            default:
                break;
        }
    }
}

void SandWorld::GetKeyboard(SDL_KeyboardEvent &k) {
    switch( k.keysym.sym ){
        case SDLK_q:
            currType = CellType::WATER;
            std::cout << "Current cell set to: WATER" << std::endl;
            break;
        case SDLK_w:
            currType = CellType::SAND;
            std::cout << "Current cell set to: SAND" << std::endl;
            break;
        case SDLK_e:
            currType = CellType::SOLID;
            std::cout << "Current cell set to: SOLID" << std::endl;
            break;
        case SDLK_r:
            currType = CellType::OIL;
            std::cout << "Current cell set to: OIL" << std::endl;
            break;
        case SDLK_f:
            currType = CellType::FIRE;
            std::cout << "Current cell set to: FIRE" << std::endl;
            break;
        default:
            break;
    }
}

//-----------------------------------------------------------------

void SandWorld::CreateCell(SDL_MouseButtonEvent& b) {
    //1 - left    3 - right
    int x = b.x / 12.8f;
    int y = b.y / 12.8f;
    if (b.button == 1) {
        matrix[y][x].SetCell(currType);
    }
    else if (b.button == 3) {
        matrix[y][x].SetCell(CellType::EMPTYCELL);
    }
}

void SandWorld::MoveCell(Cell& cell, int x, int y){
    Cell temp;
    if(cell.GetType() == CellType::SOLID || cell.GetType() == CellType::EMPTYCELL)
        return;
    if(cell.GetHeat() < 0 && cell.GetType() == CellType::FIRE)
        cell.SetCell(CellType::EMPTYCELL);
    if(cell.GetProp() == CellProp::GAS || cell.GetProp() == CellProp::FIRE){
        MoveGas(cell, x, y);
    }
    else{
        MoveCellDown(cell, x, y);
    }

}


void SandWorld::MoveCellDown(Cell &cell, int x, int y) {
    Cell temp;
    if(InBounds(x, y+1)){
        Cell *down = &(matrix[y+1][x]);
        if(down->GetType() == CellType::EMPTYCELL || down->GetDensity() < cell.GetDensity()){
            temp = *down;
            *down = cell;
            matrix[y][x] = temp;
            down->hasMoved = true;
        }
    }
    if(cell.GetProp() == CellProp::MOVE_DOWN_SIDE){
        MoveCellSide(cell, x, y);
    }
    else if(cell.GetProp() == CellProp::MOVE_DOWN_DIAGONAL){
        MoveCellDiagonal(cell, x, y);
    }
}

void SandWorld::MoveCellSide(Cell &cell, int x, int y) {
    Cell temp;
    bool right = false;
    bool left = false;
    if(InBounds(x+1, y))
        right = matrix[y][x+1].GetType() == CellType::EMPTYCELL || (matrix[y][x+1].GetDensity() < cell.GetDensity());
    if(InBounds(x-1, y))
        left = matrix[y][x-1].GetType() == CellType::EMPTYCELL || (matrix[y][x-1].GetDensity() < cell.GetDensity());


    if(right && left){
        right = RNG(0, 10) >= 5;
        left = !right;
    }
    if(right){
        temp = matrix[y][x+1];
        matrix[y][x+1] = cell;
        matrix[y][x] = temp;
        matrix[y][x+1].hasMoved = true;
    }
    else if(left){
        temp = matrix[y][x-1];
        matrix[y][x-1] = cell;
        matrix[y][x] = temp;
        matrix[y][x-1].hasMoved = true;
    }
}

void SandWorld::MoveCellDiagonal(Cell &cell, int x, int y) {
    Cell temp;
    bool right =false;
    bool left = false;
    if(InBounds(x+1, y+1))
        right = matrix[y+1][x+1].GetType() == CellType::EMPTYCELL || (matrix[y+1][x+1].GetDensity() < cell.GetDensity());
    if(InBounds(x-1, y + 1))
        left = matrix[y+1][x-1].GetType() == CellType::EMPTYCELL || (matrix[y+1][x-1].GetDensity() < cell.GetDensity());


    if(right && left){
        right = RNG(0, 10) >= 5;
        left = !right;
    }
    if(right && !(matrix[y][x+1].GetType() == CellType::SOLID && matrix[y+1][x].GetType() == CellType::SOLID)){
        temp = matrix[y+1][x+1];
        matrix[y+1][x+1] = cell;
        matrix[y][x] = temp;
        matrix[y+1][x+1].hasMoved = true;
    }
    else if(left && !(matrix[y][x-1].GetType() == CellType::SOLID && matrix[y+1][x].GetType() == CellType::SOLID)) {
        temp = matrix[y+1][x-1];
        matrix[y + 1][x - 1] = cell;
        matrix[y][x] = temp;
        matrix[y + 1][x - 1].hasMoved = true;
    }
}

void SandWorld::MoveGas(Cell &cell, int x, int y) {
    Cell temp;
    if(cell.GetProp() == CellProp::FIRE) {
        cell.SetHeat(cell.GetHeat() - 25);
        bool pos[3] {false, false, false};//left, up, right
        if(InBounds(x+1, y-1))
            pos[2] = matrix[y-1][x+1].GetType() == CellType::EMPTYCELL || matrix[y-1][x+1].IsFlammable();
        if(InBounds(x-1, y-1))
            pos[0] = matrix[y-1][x-1].GetType() == CellType::EMPTYCELL || matrix[y-1][x-1].IsFlammable();
        if(InBounds(x, y-1))
            pos[1] = matrix[y-1][x].GetType() == CellType::EMPTYCELL || matrix[y-1][x].IsFlammable();

        //r/programminghorror
        unsigned int n = RNG(0, 2);
        if(pos[n] && n == 0){
            if(matrix[y-1][x-1].IsFlammable()){
                matrix[y - 1][x - 1] = cell;
                matrix[y][x].SetCell(CellType::EMPTYCELL);
                matrix[y - 1][x - 1].hasMoved = true;
            }
            else {
                temp = matrix[y - 1][x - 1];
                matrix[y - 1][x - 1] = cell;
                matrix[y][x] = temp;
                matrix[y - 1][x - 1].hasMoved = true;
            }
        }
        else if(pos[n] && n == 1){
            if(matrix[y-1][x].IsFlammable()){
                matrix[y - 1][x] = cell;
                matrix[y][x] .SetCell(CellType::EMPTYCELL);
                matrix[y - 1][x].hasMoved = true;
            }
            else {
                temp = matrix[y - 1][x];
                matrix[y - 1][x] = cell;
                matrix[y][x] = temp;
                matrix[y - 1][x].hasMoved = true;
            }
        }
        else if(pos[n] && n == 2){
            if(matrix[y-1][x+1].IsFlammable()){
                matrix[y - 1][x + 1] = cell;
                matrix[y][x].SetCell(CellType::EMPTYCELL);
                matrix[y +- 1][x + 1].hasMoved = true;
            }
            else {
                temp = matrix[y - 1][x + 1];
                matrix[y - 1][x + 1] = cell;
                matrix[y][x] = temp;
                matrix[y + -1][x + 1].hasMoved = true;
            }
        }
    }
}

