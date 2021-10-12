#ifndef FIELD_H
#define FIELD_H

#include <QVector>
#include "def_con.h"

enum Cell {
    CL_CLEAR,
    CL_SHIP,
    CL_DOT,
    CL_DAMAGE,
    CL_KILL
};

class Field
{
public:
    Field();
    ~Field();
    Cell getCell(int x, int y) const;
    void setCell(int x, int y, Cell cell);
    void clear();
private:
   QVector<Cell> field;

};

#endif // FIELD_H
