//
// Created by guizo on 21/07/2022.
//

#ifndef FALLINGSAND_CELL_H
#define FALLINGSAND_CELL_H

#include <array>

enum class CellType{
    EMPTYCELL,
    SOLID,
    WATER,
    SAND,
    OIL,
    FIRE,
    SMOKE
};

enum class CellProp{
    STATIC,
    MOVE_DOWN,
    MOVE_DOWN_SIDE,
    MOVE_DOWN_DIAGONAL,
    GAS,
    FIRE,
    SMOKE

};

class Cell {
public:
    Cell();
    Cell(CellType _type);
    ~Cell();
    void RenderCell(int x, int y);
    void SetCell(CellType type_);

    CellType GetType() { return this->type; }
    CellProp GetProp() { return this->prop; }

    int GetHeat() const{ return this->heat;}
    void SetHeat(int heat_){ this->heat = heat_;}

    float GetDensity() const { return this->density; }
    void SetDensity(float density_);

    bool IsFlammable() const{ return this->flammable; }
    bool IsIgnited() const { return this->isIgnited; }


    bool hasMoved;
    int lifeTime;

private:
    CellType type;
    CellProp prop;
    int r, g, b, a;
    int heat;
    float density;
    bool flammable, isIgnited;
};


#endif //FALLINGSAND_CELL_H
