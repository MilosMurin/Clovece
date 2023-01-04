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

Circle::~Circle() {
    if (figure != nullptr) {
        delete figure;
        figure = nullptr;
    }
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

std::string Circle::toString() {
    std::string o;
    switch (this->type) {
        case NOTHING:
            return "   ";
        case NUETRAL:
            return "...";
        case P_ONE:
            o = "p1";
            break;
        case P_TWO:
            o = "p2";
            break;
        case P_THREE:
            o = "p3";
            break;
        case P_FOUR:
            o = "p4";
            break;
    }

    switch (this->function) {
        case EMPTY:
            return "   ";
        case HOME:
            o += "h";
            break;
        case START:
            o += "s";
            break;
        case END:
            o += "e";
            break;
    }
    return o;
}

int Circle::getPlayer() {
    return this->type - 1;
}

Circle* Circle::createCicle() {
    return new Circle(NUETRAL, EMPTY);
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

std::string Circle::getPointing() {
    string s = " . ";
    // main route
    int direction;
    if (next != nullptr) {
        if (x > next->getX()) {
            direction = 1;
        } else if (x < next->getX()) {
            direction = 3;
        } else {
            if (y > next->getY()) {
                direction = 4;
            } else {
                direction = 2;
            }
        }
        switch (direction) {
            case 1:
                s[1] = '^';
                break;
            case 2:
                s[1] = '>';
                break;
            case 3:
                s[1] = 'v';
                break;
            case 4:
                s[1] = '<';
                break;
            default:
                break;
        }
    }
    if (toHome != nullptr) {
        if (x > toHome->getX()) {
            direction = 1;
        } else if (x < toHome->getX()) {
            direction = 3;
        } else {
            if (y > toHome->getY()) {
                direction = 4;
            } else {
                direction = 2;
            }
        }
        switch (direction) {
            case 1:
                s[2] = '^';
                break;
            case 2:
                s[2] = '>';
                break;
            case 3:
                s[2] = 'v';
                break;
            case 4:
                s[2] = '<';
                break;
            default:
                break;
        }
    }
    return s;
}




