//
// template + visitor 
//

#include <iostream>
#include <vector>

class Visitor {
public:
    virtual void handlePerson(const std::string &name, int age) = 0;
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

class GreetingCardTemplate : public Visitor {
    std::string from;
protected:
    virtual std::string intro(const std::string &to) {
        return "Dear " + to + ",\n";
    }
    virtual std::string occasion() {
        return "Just writing to say hi! Hope all is well with you.\n";
    }
    virtual std::string closing(const std::string &from) {
        return "\nSincerely,\n" + from + "\n";
    }
public:
    GreetingCardTemplate(const std::string &from) : from(from) {}
    ~GreetingCardTemplate();
    void generateCardFor(Person *person) {
        person->accept(this);
    }
    void handlePerson(const std::string &name, int age) {
        std::cout << "\nSending this card to " << name << ":\n\n"
                  << intro(name) << occasion() + closing(from);
    }
};

class BirthdayCardTemplate : public GreetingCardTemplate {
protected:
    std::string occasion() override {
        return "Happy birthday!! Hope you have a wonderful day and lot of cake.";
    }

public:
    BirthdayCardTemplate(const std::string &from) : GreetingCardTemplate(from) {}
};

class PongalCardTemplate : public GreetingCardTemplate {
protected:
    std::string intro(const std::string &to) override {
        return to + "!!!\n";
    }
    std::string occasion() override {
        return "Happy Pongal!! Wish you and your family a wonderful day.";
    }

public:
    PongalCardTemplate(const std::string &from) : GreetingCardTemplate(from) {}
};

class GreetingCardGenerator {
    GreetingCardTemplate *temp;
    std::vector<Person*> people;
public:
    void addPerson(Person *person) { people.push_back(person); }
    void setTemplate(GreetingCardTemplate *newTemp) { temp = newTemp; }
    void sendGreetingCards() {
        for (auto &person : people) {
            temp->generateCardFor(person);
        }
    }
};
    
int main() {
    Person *person1 = new Person("John", 39);
    Person *person2 = new Person("Ashwad", 9);
    Person *person3 = new Person("Sashwin", 10);

    GreetingCardGenerator *generator = new GreetingCardGenerator;
    generator->addPerson(person1);
    generator->addPerson(person2);
    generator->addPerson(person3);

    generator->setTemplate(new BirthdayCardTemplate("Bob"));
    generator->sendGreetingCards();

    generator->setTemplate(new PongalCardTemplate("Stuart"));
    generator->sendGreetingCards();

    delete person1;
    delete person2;
    delete person3;
    
    return 0;
}

