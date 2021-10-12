#ifndef DEF_CON_H
#define DEF_CON_H

const int MY_FIELD_X = 40;
const int MY_FIELD_Y = 39;
const int ENEMY_FIELD_X = 322;
const int ENEMY_FIELD_Y = 39;
const int FIELD_WIDTH = 216;
const int FIELD_HEIGHT = 217;

const int FIELD_LENGTH = 10;

const int FOUR_DECK_SHIP_COUNT = 1;
const int THREE_DECK_SHIP_COUNT = 2;
const int TWO_DECK_SHIP_COUNT = 3;
const int ONE_DECK_SHIP_COUNT = 4;

struct nears {
    int direct = 1; // 1 - horizontal, 2 - vertical
    int xLeft = 0;
    int xRight = 0;
    int yUp = 0;
    int yDown = 0;
};


#endif // DEF_CON_H
