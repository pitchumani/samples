// combining memento and iterator pattern into this program

#include<iostream>
#include<vector>

class Canvas;
class ReplayCanvas;

class CanvasMemento {
    friend class Canvas;
    friend class ReplayCanvas;
    const std::vector<std::string> shapes;
public:
    CanvasMemento(std::vector<std::string> shapes) : shapes(shapes) {}
};

class CanvasIterator {
public:
    virtual ~CanvasIterator() {}
    virtual CanvasMemento *next() = 0;
    virtual bool isFinished() = 0;
};

class ForwardIterator : CanvasIterator {
    int currentPosition;
    std::vector<CanvasMemento*> &history;
public:
    ForwardIterator(std::vector<CanvasMemento*> &history) :
        currentPosition(0), history(history) {}
    
    CanvasMemento* next() override {
        CanvasMemento* current = history.at(currentPosition);
        currentPosition++;
        return current;
    }
    bool isFinished() {
        return currentPosition >= history.size();
    }
};

class History {
public:
    virtual void addState(CanvasMemento *newState) = 0;
    virtual CanvasMemento *undo() = 0;
};

class CanvasHistory : public History {
    std::vector<CanvasMemento*> oldStates;
public:
    ~CanvasHistory() {
        for (auto &p : oldStates) {
            delete p;
        }
    }
    void addState(CanvasMemento *newState) override {
        oldStates.push_back(newState);
    }
    CanvasMemento *undo() override {
        oldStates.pop_back();
        CanvasMemento *prevState = oldStates.back();
        return prevState;
    }
    ForwardIterator *getForwardIterator() {
        return new ForwardIterator(oldStates);
    }
};

class NullHistory : public History {
public:
    NullHistory() {}
};

class Canvas {
    std::vector<std::string> shapes;
    History *history = nullptr;
public:
    Canvas(History *history) : history(history) {}
    void addShape(const std::string &newShape) {
        shapes.push_back(newShape);
        history->addState(new CanvasMemento(shapes));
    }
    void undo() {
        CanvasMemento *previousState = history->undo();
        shapes = previousState->shapes;
    }
    void clearAll() {
        shapes.clear();
        history->addState(new CanvasMemento(shapes));
    }
    std::vector<std::string> getShapes() {
        return shapes;
    }
};

class ReplayCanvas {
    std::vector<std::string> shapes;
    ForwardIterator *historyIterator;
public:
    ReplayCanvas(CanvasHistory *history) {
        historyIterator = history->getForwardIterator();
    }
    void replay() {
        while(!historyIterator->isFinished()) {
            CanvasMemento *nextState = historyIterator->next();
            shapes = nextState->shapes;
            std::cout << "The shapes are now: ";
            for (auto &shape : shapes) {
                std::cout << shape << ", ";
            }
            std::cout << "\n";
        }
    }
};

int main() {
    CanvasHistory *history = new CanvasHistory;
    Canvas *canvas = new Canvas(history);
    
    canvas->addShape("rhombus");
    canvas->addShape("triangle");
    canvas->addShape("square");
    canvas->addShape("circle");
    
    std::cout << "Watching Replay:\n";
    ReplayCanvas *replayCanvas = new ReplayCanvas(history);
    replayCanvas->replay();
 
    return 0;
}

