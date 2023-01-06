#include "Circle.h"

Circle::Circle() : Circle(NOTHING, EMPTY)  {

}

Circle::Circle(int num) {
    if (num > 99 || num < 0) {
        throw std::runtime_error("Invalid number initializator for class Circle!");
    }
    type = static_cast<Type>(num / 10);
    function = static_cast<Function>(num % 10);
}

Circle::Circle(Type type, Function special) : type(type), function(special) {

}

Type Circle::getType() const {
    return type;
}

Function Circle::getFunction() const {
    return function;
}

Figure* Circle::getFigure() const {
    return figure;
}

void Circle::setFigure(Figure* newFigure) {
    if (this->type == NOTHING) {
        return;
    }
    this->figure = newFigure;
    if (figure != nullptr) {
        this->figure->setCircle(x, y);
    }
}

bool Circle::hasFigure() const {
    return figure != nullptr;
}

void Circle::setNext(Circle* circle) {
    if (this->type == NOTHING) {
        return;
    }
    if (circle->getFunction() == Function::END) {
        this->toHome = circle;
    } else {
        this->next = circle;
    }
}

Circle* Circle::getNext(int player) {
    if (this->toHome != nullptr) {
        int home = this->toHome->getPlayer();
        if (player == home) {
            return this->toHome;
        }
    }
    return this->next;
}

int Circle::getPlayer() {
    return this->type - 1;
}

void Circle::setPosition(int x, int y) {
    this->x = x;
    this->y = y;
}

int Circle::getX() const {
    return x;
}

int Circle::getY() const {
    return y;
}

string Circle::getLine(int index) {
    string s = "     ";
    if (this->type == NOTHING) {
        return s;
    }
    int direction = 0;
    if (next != nullptr) {
        if (x > next->getX()) {
            direction = 1; // up ^
        } else if (x < next->getX()) {
            direction = 3; // down v
        } else {
            if (y > next->getY()) {
                direction = 4; // left <
            } else {
                direction = 2; // right >
            }
        }
    }
    int homeDirection = 0;
    if (toHome != nullptr) {
        if (x > toHome->getX()) {
            homeDirection = 1; // up ^
        } else if (x < toHome->getX()) {
            homeDirection = 3; // down v
        } else {
            if (y > toHome->getY()) {
                homeDirection = 4; // left <
            } else {
                homeDirection = 2; // right >
            }
        }
    }

    switch (index) {
        case 1: // line one
            switch (this->type) {
                case NUETRAL:
                    s[0] = '/';
                    s[3] = '\\';
                    break;
                default:
                    s[0] = static_cast<char>(this->type - 1 + 48);
                    switch (this->function) {
                        case EMPTY:
                            return "    ";
                        case HOME:
                            s[3] = 'h';
                            break;
                        case START:
                            s[3] = 's';
                            break;
                        case END:
                            s[3] = 'e';
                            break;
                    }
                    break;
            }
            if (direction == 1 || homeDirection == 1) {
                s[1] = '^';
                s[2] = '^';
            } else {
                s[1] = '-';
                s[2] = '-';
            }
            break;
        case 2:

            if (this->hasFigure()) {
                s[1] = static_cast<char>(this->figure->getPlayer() + 48);
                s[2] = static_cast<char>(this->figure->getId() + 48);
            }
            if (direction == 2 || homeDirection == 2) {
                s[3] = '>';
            } else {
                s[3] = '|';
            }
            if (direction == 4 || homeDirection == 4) {
                s[0] = '<';
            } else {
                s[0] = '|';
            }
            break;
        case 3:
            s[0] = '\\';
            s[3] = '/';
            if (direction == 3 || homeDirection == 3) {
                s[1] = 'v';
                s[2] = 'v';
            } else {
                s[1] = '_';
                s[2] = '_';
            }
            break;
        default:
            return s;
    }
    return s;
}

string Circle::toWeb() {
    return to_string(type) ;
}




