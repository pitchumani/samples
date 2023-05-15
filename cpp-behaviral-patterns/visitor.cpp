// visitor.cpp
// Example for Visitor pattern
//
// When we need to add similar extraneous functionality to many different class
// Solution: Instead of adding the same extraneous methods to many different
// classes, create separate class that can visit these classes and handle that
// logic itself

/*
  Example use case
  class A {
      ...
      writeToDatabase()
      writeToJSON()
      writeToTextfile()
  }

  class B {
      ...
      writeToDatabase()
      writeToJSON()
      writeToTextfile()
  }

  class C {
      ...
      writeToDatabase()
      writeToJSON()
      writeToTextfile()
  }

  instead use below visitor pattern


                                                +------------------------+
                                                | WriteToDatabaseVisitor |
                                                +------------------------+
            +-----------------------------------|+ execute(A a)          |
            |                                   |+ execute(B b)          |
            |                                   |+ execute(C c)          |
            |                                   +------------------------+
            V
  +-------------------+                         +------------------------+ 
  | Visitor Interface |                         | WriteToJSONVisitor     |
  +-------------------+                         +------------------------+
  |+ execute(A a)     |<------------------------|+ execute(A a)          |
  |+ execute(B b)     |                         |+ execute(B b)          |
  |+ execute(C c)     |                         |+ execute(C c)          |
  +-------------------+                         +------------------------+
           ^
           |                                    +------------------------+
           |                                    | WriteToTextfileVisitor |
           |                                    +------------------------+
           +------------------------------------|+ execute(A a)          |
                                                |+ execute(B b)          |
                                                |+ execute(C c)          |
                                                +------------------------+

  +--------------------+
  | {A, B, C}          |
  +--------------------+
  |+ accept(Visitor v) |
  |...                 |
  +--------------------+

*/
#include <iostream>

class Visitor {
public:
    virtual void handlePerson(const std::string &name, int age) = 0;
    virtual void handleLandmark(const std::string &name, const std::string &cityName) = 0;
    virtual void handleCar(const std::string &name, const std::string &model) = 0;
};

class DataBaseVisitor : public Visitor {
public:
    void handlePerson(const std::string &name, int age) override {
        std::cout << "Writing person to the database: " << name << ", " << age << std::endl;
    }
    void handleLandmark(const std::string &name, const std::string &cityName) override {
        std::cout << "Writing landmark to the database: " << name << ", " << cityName << std::endl;
    }
    void handleCar(const std::string &make, const std::string &model) override {
        std::cout << "Writing car to the database: " << make << ", " << model << std::endl;
    }
};

class TextFileVisitor : public Visitor {
public:
    void handlePerson(const std::string &name, int age) override {
        std::cout << "Writing person to the textfile: " << name << ", " << age << std::endl;
    }
    void handleLandmark(const std::string &name, const std::string &cityName) override {
        std::cout << "Writing landmark to the textfile: " << name << ", " << cityName << std::endl;
    }
    void handleCar(const std::string &make, const std::string &model) override {
        std::cout << "Writing car to the textfile: " << make << ", " << model << std::endl;
    }
};


class Person {
    std::string name;
    int age;
    
public:
    Person(const std::string &name, int age) : name(name), age(age) {}
    void accept(Visitor *v) {
        v->handlePerson(name, age);
    }
};

class Landmark {
    std::string name;
    std::string cityName;

public:
    Landmark(const std::string &name, const std::string &cityName) : name(name), cityName(cityName) {}
    void accept(Visitor *v) {
        v->handleLandmark(name, cityName);
    }
};

class Car {
    std::string make;
    std::string model;
    
public:
    Car(const std::string &make, const std::string model) : make(make), model(model) {}
    void accept(Visitor *v) {
        v->handleCar(make, model);
        
    }
};

int main () {
    Person person1("John", 39);
    Landmark landmark1("LaCasa", "Bengaluru");
    Car car1("Chevrolet", "Camaro");

    DataBaseVisitor *dbv = new DataBaseVisitor;
    TextFileVisitor *tfv = new TextFileVisitor;

    person1.accept(dbv);
    landmark1.accept(dbv);
    car1.accept(dbv);
    
    person1.accept(tfv);
    landmark1.accept(tfv);
    car1.accept(tfv);

    delete dbv;
    delete tfv;
    
    return 0;
}

