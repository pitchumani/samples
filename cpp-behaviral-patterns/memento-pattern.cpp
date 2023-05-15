/* memento-pattern.cpp
   When we want to freeze or save objects in such a way that
   they can't be modified by any other part of our program
   until they're unfrozen.

   solution: allow certain objects to save themselves in such
   a way that they can't be modified - at least until they say so.

   example: canvas with shapes - undo functionality


   -----------------                -----------------
   Memento interface                CanvasHistory
   ----------------- <_____________ -----------------
   + getName()                      - mememtos[]
   + getTime()                      -----------------
   -----------------
         ^
         |
   ------------------
   CanvasStateMemento
   ------------------
   - shapes[]
   ------------------
          ^
          |
   ------------------
   CanvasState
   ------------------
   - shapes[]
   ------------------
   + addShape(shape)
   + createMemento()
   + restoreState(CanvasStateMemento csm)
   --------------------------------------


*/
#include<iostream>
#include<vector>

class Canvas;

class CanvasMemento {
    friend class Canvas;
    const std::vector<std::string> shapes;
public:
    CanvasMemento(std::vector<std::string> shapes) : shapes(shapes) {}
};

class Canvas {
    std::vector<std::string> shapes;
    std::vector<CanvasMemento*> oldStates;
public:
    ~Canvas() {
        for (auto p : oldStates) {
            delete p;
        }
    }
    void addShape(const std::string &newShape) {
        oldStates.push_back(new CanvasMemento(shapes));
        shapes.push_back(newShape);
    }
    void clearAll() {
        shapes.clear();
    }
    std::vector<std::string> getShapes() {
        return shapes;
    }
    void undo() {
        CanvasMemento *previousState = oldStates.back();
        oldStates.pop_back();
        shapes = previousState->shapes;
        delete previousState;
    }
};


int main() {
    Canvas *canvas = new Canvas;
    
    canvas->addShape("rhombus");
    canvas->addShape("triangle");
    canvas->addShape("square");
    canvas->addShape("circle");
    
    for (auto shape : canvas->getShapes()) {
        std::cout << shape << ", ";
    };
    
    std::cout << "\n";
    
    canvas->undo();
    
    for (auto shape : canvas->getShapes()) {
        std::cout << shape << ", ";
    };
    
    std::cout << "\n";
    
    canvas->addShape("rhombus");
    canvas->addShape("triangle");
    canvas->addShape("square");
    canvas->addShape("circle");
    canvas->undo();
    
    for (auto shape : canvas->getShapes()) {
        std::cout << shape << ", ";
    };
    
    std::cout << "\n";
 
    delete canvas;

    return 0;
}

