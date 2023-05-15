// template-method.cpp
// Example for Template Method pattern
//
// greeting card template
//

#include <iostream>

class GreetingCardTemplate {
protected:
    virtual std::string intro(const std::string &to) {
        return "Dear " + to + ",\n";
    }
    virtual std::string occasion() {
        return "Just writing to say hi! Hope all is well with you.\n";
    }
    virtual std::string closing(const std::string &from) {
        return "Sincerely,\n" + from + "\n";
    }
public:
    std::string generate(const std::string &to, const std::string &from) {
        return intro(to) + occasion() + closing(from);
    }
};

class BirthdayCardTemplate : public GreetingCardTemplate {
protected:
    std::string occasion() override {
        return "Happy birthday!! Hope you have a wonderful day and lot of cake.";
    }
};

class PongalCardTemplate : public GreetingCardTemplate {
protected:
    std::string intro(const std::string &to) override {
        return to + "!!!\n";
    }
    std::string occasion() override {
        return "Happy Pongal!! Wish you and your family a wonderful day.";
    }
};

int main() {
    GreetingCardTemplate gct;
    BirthdayCardTemplate bct;
    PongalCardTemplate pct;
    
    std::cout << "Here's a regular greeting card:\n\n"
              << gct.generate("Bob", "Jane") << std::endl;
    std::cout << "Here's a birthday card:\n\n"
              << bct.generate("Sashwin", "Meenu") << std::endl;
    std::cout << "Here's Pongal card:\n\n"
              << pct.generate("Ashwad", "Sashwin") << std::endl;    
    return 0;
}

