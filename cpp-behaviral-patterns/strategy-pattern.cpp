// strategy-pattern.cpp
// Example for strategy pattern
//

#include <iostream>

class GreetingStrategy {
public:
    virtual void greet(const std::string & name) = 0;
};

class NormalGreetingStrategy : public GreetingStrategy {
public:
    void greet(const std::string & name) {
        std::cout << "Hi " << name << ", how are you?\n";
    }
};

class FormalGreetingStrategy : public GreetingStrategy {
public:
    void greet(const std::string & name) {
        std::cout << "Good morning " << name << ", how do you do?\n";
    }
};

class InformalGreetingStrategy : public GreetingStrategy {
public:
    void greet(const std::string & name) {
        std::cout << "Hey " << name << ", what's up?\n";
    }
};

class Person {
    GreetingStrategy *greetingStrategy = nullptr;
public:
    Person(GreetingStrategy *greetingStrategy) : greetingStrategy(greetingStrategy) {}
    ~Person() {
        delete greetingStrategy;
    }
    void greet(const std::string &name) {
        greetingStrategy->greet(name);
    }
};

int main() {
    Person businessPerson(new FormalGreetingStrategy());
    Person normalPerson(new NormalGreetingStrategy());
    Person coolPerson(new InformalGreetingStrategy());
    Person politician(new FormalGreetingStrategy());
    std::cout << "The businessperson says: ";
    businessPerson.greet("Sashwin");
    std::cout << "The normal person says: ";
    normalPerson.greet("Anand");
    std::cout << "The cool person says: ";
    coolPerson.greet("Anand");
    std::cout << "The politician says: ";
    politician.greet("Anand");
    return 0;
}
