/* nullobject-pattern.cpp
   When you want to rest of your program to be able to
   interact with instances of a class without worrying about
   whether or not they exist, e.g. accessing obj pointer by checking nullpointer

   For a given class, define an acceptable null value for that
   class, such that you can interact with the class without it
   having to actually exist
*/

#include <iostream>

class Logger {
public:
    virtual void log(const std::string&) = 0;
    virtual ~Logger() {}
};

class ConsoleLogger : public Logger {
public:
    void log(const std::string &msg) override {
        std::cout << "Console: " << msg << std::endl;
    }
};

class FileLogger : public Logger {
public:
    void log(const std::string &msg) override {
        std::cout << "File: " << msg << std::endl;
    }
};

class ApiLogger : public Logger {
public:
    void log(const std::string &msg) override {
        std::cout << "Api: " << msg << std::endl;
    }
};

class NullLogger : public Logger {
public:
    void log(const std::string &msg) {}
};

class SomeTask {
    Logger *logger = nullptr;
 public:
    SomeTask() { logger = new NullLogger; }
    SomeTask(Logger *logger) : logger(logger) {}
    ~SomeTask() { delete logger; }
    void execute() {
        if (logger) {
            logger->log("Did some stuff");
        }
        // code
        if (logger) {
            logger->log("Did some other stuff");
        }
    }
};

int main () {
    SomeTask task1(new ConsoleLogger);
    SomeTask task2(new FileLogger);
    SomeTask task3(new ApiLogger);
    SomeTask task4;

    task1.execute();
    task2.execute();
    task3.execute();
    task4.execute();

    return 0;
}

