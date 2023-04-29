#include <iostream>
#include <vector>
#include <algorithm>

class Subscriber {
public:
    virtual void notify(const std::string &pubName, const std::string &message) = 0;
    virtual std::string getName() = 0;
};

class Publisher {
public:
    virtual void subscribe(Subscriber *sub) = 0;
    virtual void unsubscribe(Subscriber *sub) = 0;
    virtual void publish(const std::string &message) = 0;
};

class ChatGroup : public Publisher {
    std::string groupName;
    std::vector<Subscriber*> subscribers;
public:
    ChatGroup(const std::string &name) : groupName(name) {}

    void subscribe(Subscriber *sub) override {
        this->subscribers.push_back(sub);
    }
    void unsubscribe(Subscriber *sub) override {
        subscribers.erase(std::remove_if(subscribers.begin(), subscribers.end(),
                                         [sub](Subscriber *s) { return s->getName() == sub->getName(); }),
                          subscribers.end());
    }
    void publish(const std::string &message) override {
        for (auto s : subscribers) {
            s->notify(groupName, message);
        }
    }
};

class ChatUser : public Subscriber {
    std::string userName;
public:
    ChatUser(const std::string &name) : userName(name) {}

    void notify(const std::string &pubName, const std::string &msg) override {
        std::cout << userName << " received a new message from "
                  << pubName << ": " << msg << std::endl;
    }
    std::string getName() override { return userName; }
};

class Handler {
public:
    virtual ~Handler() {}
    virtual Handler *setNext(Handler *nextValidator) = 0;
    virtual std::string handle(ChatGroup *group, std::string) = 0;
};

class BaseHandler: public Handler {
protected:
    Handler *next = nullptr;
public:
    virtual ~BaseHandler() { delete next; }
    Handler *setNext(Handler *nextValidator) override {
        next = nextValidator;
        return nextValidator;
    }
    virtual std::string handle(ChatGroup *group, std::string testString) override {
        if (this->next) {
            return this->next->handle(group, testString);
        }
        return "Success!";
    }
};

class NotEmptyValidator: public BaseHandler {
public:
    NotEmptyValidator() {}
    std::string handle(ChatGroup *group, std::string testString) {
        puts("Checking if empty...");
        if (testString.empty()) {
            return "Please enter a value";
        }
        return BaseHandler::handle(group, testString);
    }
};

class LengthValidator: public BaseHandler {
    int minLength;
public:
    LengthValidator(int minLength) : minLength(minLength) {}

    std::string handle(ChatGroup *group, std::string testString) override {
        puts("Checking string length...");
        if (testString.length() < minLength) {
            return "Please enter a value longer than " +
                std::to_string(minLength);
        }
        return BaseHandler::handle(group, testString);
    }
};

class PostMessageHandler : public BaseHandler {
public:
    std::string handle(ChatGroup *group, std::string msg) {
        group->publish(msg);
        return "Message sent!";
    }
};

int main (int argc, char *argv[]) {

    ChatUser *user_Jack = new ChatUser("Jack");
    ChatUser *user_Jill = new ChatUser("Jill");
    ChatUser *user_Rose = new ChatUser("Rose");

    ChatGroup *group_cooking = new ChatGroup("Cooking");
    ChatGroup *group_gardening = new ChatGroup("Gardening");
    ChatGroup *group_reading = new ChatGroup("Reading");

    group_cooking->subscribe(user_Jack);
    group_cooking->subscribe(user_Jill);

    group_gardening->subscribe(user_Rose);
    group_gardening->subscribe(user_Jill);

    group_reading->subscribe(user_Rose);

    Handler *sendMessageChain = new BaseHandler;
    sendMessageChain
        ->setNext(new NotEmptyValidator)
        ->setNext(new LengthValidator(3))
        ->setNext(new PostMessageHandler);

    std::cout << "Sending empty message.\n" <<
        sendMessageChain->handle(group_reading, "") << "\n\n";
    std::cout << "Sending short message:\n" <<
        sendMessageChain->handle(group_cooking, "Hi there! in cooking group") << "\n\n";
    std::cout << "Sending message to gardening group:\n" <<
        sendMessageChain->handle(group_gardening, "Hello everyone! in gardening group") << "\n\n";

    delete user_Jack;
    delete user_Jill;
    delete user_Rose;
    delete group_cooking;
    delete group_gardening;
    delete group_reading;
    delete sendMessageChain;

    return 0;
}

