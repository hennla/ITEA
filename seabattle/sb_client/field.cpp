#include "field.h"

Field::Field() {
    clear();
}

Field::~Field() = default;

Cell Field::getCell(int x, int y) const {
    if (x >= FIELD_LENGTH || y >= FIELD_LENGTH || x < 0 || y < 0) {
        return CL_CLEAR;
    }
    int n = y * FIELD_LENGTH + x;
    if (n > field.size()) {
        return CL_CLEAR;
    }
    return field[n];
}

void Field::setCell(int x, int y, Cell cell) {
    if (x >= FIELD_LENGTH || y >= FIELD_LENGTH || x < 0 || y < 0) {
        return;
    }
    int n = y * FIELD_LENGTH + x;
    if (n > field.size()) {
        return;
    }
    field[n] = cell;
}

void Field::clear() {
    field.resize(FIELD_LENGTH * FIELD_LENGTH);
    std::fill(field.begin(), field.end(), CL_CLEAR);
}
