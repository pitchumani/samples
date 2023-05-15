/* iterator-pattern.cpp
   want to iterate through different data structures
   without worrying about their underlying organization

   example: a tree structure

                                        +------------------------+                
                                        | DepthFirstTreeIterator |
                                        +------------------------+<_______________________ 
            +---------------------------| +next()                |                       |
            |                           | +isFinished()          |                 +-----------------------------+ 
            |                           +------------------------+                 | TreeCollection              |
            v                                                                      +-----------------------------+
   +--------------------+               +--------------------------+               | + getBreadthFirstIterator() |
   | iterator interface |               | BreadthFirstTreeIterator |               | + getDepthFirstIterator()   |
   +--------------------+               +--------------------------+               +-----------------------------+
   | +next()            |<--------------| +next()                  |<_____________________|
   | +isFinished()      |               | +isFinished()            |
   +--------------------+               +--------------------------+
            ^
            |                           +---------------+ 
            |                           | ListIterator  |
            |                           +---------------+
            +---------------------------| +next()       |
                                        | +isFinished() |
                                        +---------------+








*/

#include<iostream>
#include<vector>

class NumbersIterator {
public:
    virtual ~NumbersIterator() {}
    virtual int next() = 0;
    virtual bool isFinished() = 0;
};

class ForwardIterator : public NumbersIterator {
    int currentPosition;
    std::vector<int> &numbers;
public:
    ForwardIterator(std::vector<int> &numbers) :
        currentPosition(0), numbers(numbers) {}
    
    int next() override {
        int current = numbers.at(currentPosition);
        currentPosition++;
        return current;
    }
    bool isFinished() {
        return currentPosition >= numbers.size();
    }
};

class BackwardIterator : public NumbersIterator {
    int currentPosition;
    std::vector<int> &numbers;
public:
    BackwardIterator(std::vector<int> &numbers) :
        currentPosition(0), numbers(numbers) {}
    
    int next() override {
        int current = numbers.at(numbers.size() - currentPosition - 1);
        currentPosition++;
        return current;
    }
    bool isFinished() {
        return currentPosition >= numbers.size();
    }
};

class NumberCollection {
    std::vector<int> numbers;
public:
    NumberCollection(const std::vector<int> &numbers) : numbers(numbers) {}
    NumbersIterator *getForwardIterator() {
        return new ForwardIterator(numbers);
    }
    NumbersIterator *getBackwardIterator() {
        return new BackwardIterator(numbers);
    }
};

int main() {
    std::vector<int> numbers = { 1, 1, 2, 3, 5, 8, 13, 21, 34 };
    NumberCollection fibNums(numbers);
    
    NumbersIterator *fi = fibNums.getForwardIterator();
    std::cout << "Iterating forward:\n";
    while(fi->isFinished() == false) {
        std::cout << fi->next() << " ";
    }
    std::cout << "\n\n";
    
    NumbersIterator *bi = fibNums.getBackwardIterator();
    std::cout << "Iterating backward:\n";
    while(bi->isFinished() == false) {
        std::cout << bi->next() << " ";
    }
    std::cout << "\n\n";
    return 0;
}

