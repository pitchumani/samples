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

class MessageCommand {
public:
    virtual ~MessageCommand() {}
    virtual void execute() = 0;
    virtual std::string getMessage() = 0;
};

class SendMessageCommand : public MessageCommand {
    ChatGroup *chatGroup;
    std::string message;
public:
    SendMessageCommand(ChatGroup *group, std::string msg) :
        chatGroup(group), message(msg) {
    }
    std::string getMessage() override {
        return message;
    }
    void execute() override {
        chatGroup->publish(message);
    }
};

class Handler {
public:
    virtual ~Handler() {}
    virtual Handler *setNext(Handler *nextValidator) = 0;
    virtual std::string handle(MessageCommand *command) = 0;
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
    virtual std::string handle(MessageCommand *command) override {
        if (this->next) {
            return this->next->handle(command);
        }
        return "Success!";
    }
};

class NotEmptyValidator: public BaseHandler {
public:
    NotEmptyValidator() {}
    std::string handle(MessageCommand *command) {
        puts("Checking if empty...");
        if (command->getMessage().empty()) {
            return "Please enter a value";
        }
        return BaseHandler::handle(command);
    }
};

class LengthValidator: public BaseHandler {
    int minLength;
public:
    LengthValidator(int minLength) : minLength(minLength) {}

    std::string handle(MessageCommand *command) override {
        puts("Checking string length...");
        if (command->getMessage().length() < minLength) {
            return "Please enter a value longer than " +
                std::to_string(minLength);
        }
        return BaseHandler::handle(command);
    }
};

class PostMessageHandler : public BaseHandler {
public:
    std::string handle(MessageCommand *command) {
        command->execute();
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

    SendMessageCommand *empty_msg_cmd =
        new SendMessageCommand(group_reading, "");
    SendMessageCommand *short_msg_cmd =
        new SendMessageCommand(group_reading, "Y");
    SendMessageCommand *msg_cooking_cmd =
        new SendMessageCommand(group_cooking, "Hi there! in cooking group");
    SendMessageCommand *msg_gardening_cmd =
        new SendMessageCommand(group_gardening, "Hello everyone! in gardening group");

    std::cout << "Sending empty message.\n" <<
        sendMessageChain->handle(empty_msg_cmd) << "\n\n";

    std::cout << "Sending short message:\n" <<
        sendMessageChain->handle(short_msg_cmd) << "\n\n";

    std::cout << "Sending message to cooking group:\n" <<
        sendMessageChain->handle(msg_cooking_cmd) << "\n\n";

    std::cout << "Sending message to gardening group:\n" <<
        sendMessageChain->handle(msg_gardening_cmd) << "\n\n";

    delete user_Jack;
    delete user_Jill;
    delete user_Rose;
    delete group_cooking;
    delete group_gardening;
    delete group_reading;
    delete sendMessageChain;

    delete empty_msg_cmd;
    delete short_msg_cmd;
    delete msg_cooking_cmd;
    delete msg_gardening_cmd;

    return 0;
}

