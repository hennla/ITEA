#include "model.h"

Model::Model()
{
    my_field_    = new Field;
    enemy_field_ = new Field;
    state_ = PLACING_SHIPS;
}

Model::~Model() {
    delete my_field_;
    delete enemy_field_;
}

State Model::getState() const {
    return state_;
}

void Model::setState( State state )
{
    state_ = state;
}

Cell Model::getMyCell( int x, int y ) const {
    return my_field_->getCell(x, y);
}

void Model::setMyCell( int x, int y, Cell cell ) {
    my_field_->setCell(x, y, cell);
}

Cell Model::getEnemyCell( int x, int y ) const {
    return enemy_field_->getCell(x, y);
}

void Model::setEnemyCell( int x, int y, Cell cell ) {
    enemy_field_->setCell(x, y, cell);
}

void Model::clearEnemyField() {
    my_field_->clear();
}

void Model::clearMyField() {
    enemy_field_->clear();
}

void Model::initNears(nears& nears_, int x, int y) const {
    nears_.xLeft = (x - 1 < 0) ? x : x - 1;
    nears_.xRight = (x + 1 < FIELD_LENGTH - 1) ? x + 1 : FIELD_LENGTH - 1;
    nears_.yUp = (y - 1 < 0) ? y : y - 1;
    nears_.yDown = (y + 1 < FIELD_LENGTH - 1) ? y + 1 : FIELD_LENGTH - 1;
    if ((nears_.yUp != y && getMyCell(x, nears_.yUp) == CL_SHIP) || (nears_.yDown !=y && getMyCell(x, nears_.yDown) == CL_SHIP)) {
        nears_.direct = 2;
    }
}

int Model::calcDecks(nears& nears_, int x, int y, bool offset) const {
    int decks = 0;

    if (nears_.direct == 1) {
        int leftBorder = x;
        if (offset) {
            if (getMyCell(nears_.xLeft, y) == CL_SHIP) {
                leftBorder = nears_.xLeft;
                while (getMyCell(leftBorder, y) == CL_SHIP) {
                    leftBorder--;
                }
                leftBorder++;
            } else {
                leftBorder = nears_.xRight;
            }
        }
        while (getMyCell(leftBorder, y) == CL_SHIP) {
            leftBorder++;
            decks++;
        }
    } else {
        int upBorder = y;
        if (offset) {
            if (getMyCell(x, nears_.yUp) == CL_SHIP) {
                upBorder = nears_.yUp;
                while (getMyCell(x, upBorder) == CL_SHIP) {
                    upBorder--;
                }
                upBorder++;
            } else {
                upBorder = nears_.yDown;
            }
        }
        while (getMyCell(x, upBorder) == CL_SHIP) {
            upBorder++;
            decks++;
        }
    }

    return decks;
}

bool Model::isShip(int decks, int x, int y) const {
    nears nears_;
    initNears(nears_, x, y);
    if (nears_.xLeft != x && getMyCell(nears_.xLeft, y) ==CL_SHIP) {
        return false;
    }
    if (nears_.yUp != y && getMyCell(x, nears_.yUp) ==CL_SHIP) {
        return false;
    }
    if (getMyCell(x, y) == CL_CLEAR) {
        return false;
    }

    if (calcDecks(nears_, x, y, false) != decks) {
        return false;
    }
    return true;;
}

bool Model::validatePoint(int x, int y) const {
    nears nears_;
    initNears(nears_, x, y);

    if (nears_.direct == 1) {
        if ((nears_.yUp != y) && ((getMyCell(x, nears_.yUp) == CL_SHIP) ||
                (getMyCell(nears_.xLeft, nears_.yUp) == CL_SHIP) ||
                (getMyCell(nears_.xRight, nears_.yUp) == CL_SHIP))) {
            return false;
        }
        if ((nears_.yDown != y) && ((getMyCell(x, nears_.yDown) == CL_SHIP) ||
                (getMyCell(nears_.xLeft, nears_.yDown) == CL_SHIP) ||
                (getMyCell(nears_.xRight, nears_.yDown) == CL_SHIP))) {
            return false;
        }
    } else {
        if ((nears_.xLeft != x) && ((getMyCell(nears_.xLeft, y) == CL_SHIP) ||
                (getMyCell(nears_.xLeft, nears_.yUp) == CL_SHIP) ||
                (getMyCell(nears_.xLeft, nears_.yDown) == CL_SHIP))) {
            return false;
        }
        if ((nears_.xRight != x) && ((getMyCell(nears_.xRight, y) == CL_SHIP) ||
                (getMyCell(nears_.xRight, nears_.yUp) == CL_SHIP) ||
                (getMyCell(nears_.xRight, nears_.yDown) == CL_SHIP))) {
            return false;
        }
    }

    if (calcDecks(nears_, x, y, true) >= 4) {
        return false;
    }
    return true;
}

int Model::shipCount(int decks) const
{
    int shipCount = 0;

    for(int x = 0; x < 10; x++) {
        for(int y = 0; y < 10; y++) {
            if(isShip(decks, x, y)) {
                shipCount++;
            }
        }
    }
    return shipCount;
}

bool Model::validateMyField() const
{
    return (
        shipCount(1) == 4 &&
        shipCount(2) == 3 &&
        shipCount(3) == 2 &&
        shipCount(4) == 1
    );
}

void Model::setLogin(const QString& login_) {
    login = login_;
}

void Model::setUserId(const quint16 userId_) {
    userId = userId_;
}

QString Model::getLogin() const {
    return login;
}

quint16 Model::getUserId() const {
    return userId;
}

void Model::setEnemyUserId(const quint16 enemyUserId_) {
    enemyUserId = enemyUserId_;
}

quint16 Model::getEnemyUserId() const {
    return enemyUserId;
}

void Model::setEnemyLogin(const QString enemyLogin_) {
    enemyLogin = enemyLogin_;
}

QString Model::getEnemyLogin() const {
    return enemyLogin;
}

void Model::disconnect() {
   userId = 0;
   enemyUserId = 0;
   enemyLogin = "";
}

bool Model::isAlive() {
    for (int x = 0; x < FIELD_LENGTH; x++) {
        for (int y = 0; y < FIELD_LENGTH; y++) {
            if (my_field_->getCell(x, y) == CL_SHIP) {
                return true;
            }
        }
    }
    return false;
}

bool Model::isShipKilled(int x, int y) {
    int i = x - 1;
    int aliveDecks = 0;
    while (my_field_->getCell(i, y) != CL_DOT &&
           my_field_->getCell(i, y) != CL_CLEAR) {
        if (my_field_->getCell(i, y) == CL_SHIP)
            aliveDecks++;
        i--;
    }
    i = x + 1;
    while (my_field_->getCell(i, y) != CL_DOT &&
           my_field_->getCell(i, y) != CL_CLEAR) {
        if (my_field_->getCell(i, y) == CL_SHIP)
            aliveDecks++;
        i++;
    }

    i = y - 1;
    while (my_field_->getCell(x, i) != CL_DOT &&
           my_field_->getCell(x, i) != CL_CLEAR) {
        if (my_field_->getCell(x, i) == CL_SHIP)
            aliveDecks++;
        i--;
    }

    i = y + 1;
    while (my_field_->getCell(x, i) != CL_DOT &&
           my_field_->getCell(x, i) != CL_CLEAR) {
        if (my_field_->getCell(x, i) == CL_SHIP)
            aliveDecks++;
        i++;
    }
    return aliveDecks == 0;
}

void Model::markKilledShip(int x, int y, bool isEnemy) {
    nears nears_;
    initNears(nears_, x, y);
    if (isEnemy) {
        setEnemyCell(x, y, CL_KILL);
    } else {
        setMyCell(x, y, CL_KILL);
    }
    Cell cell;
    for (int dx = nears_.xLeft; dx <= nears_.xRight; dx++) {
        for (int dy = nears_.yUp; dy <= nears_.yDown; dy++) {
            if (isEnemy) {
                cell = getEnemyCell(dx, dy);
            } else {
                cell = getMyCell(dx, dy);
            }
            if ((dx == x && dy == y) || cell == CL_DOT) {
                continue;
            }
            if (cell == CL_CLEAR) {
                if (isEnemy) {
                    setEnemyCell(dx, dy, CL_DOT);
                } else {
                    setMyCell(dx, dy, CL_DOT);
                }
            } else if (cell == CL_DAMAGE) {
                if (isEnemy) {
                    setEnemyCell(dx, dy, CL_KILL);
                } else {
                    setMyCell(dx, dy, CL_KILL);
                }
                markKilledShip(dx, dy, isEnemy);
            }
        }
    }
}
