#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <map>
#include <functional>
using namespace std::placeholders;

class Base {
public:

    virtual std::string getType() const = 0;

    virtual const std::string& getName() const = 0;

    virtual const std::string getPrintedName() const = 0;

    virtual ~Base() = default;

};

class File: public Base {
public:

    static const std::string TYPE;

public:

    File(const std::string &name)
        : name(name)
    {}

    const std::string& getName() const override {
        return name;
    }

    const std::string getPrintedName() const override {
        return "File_" + getName();
    }

    std::string getType() const override {
        return TYPE;
    }

private:

    std::string name;
};

const std::string File::TYPE = "File";

class Folder: public Base {
public:

    static const std::string TYPE;

public:

    Folder(const std::string &name)
        : name(name)
    {}

    const std::string& getName() const override {
        return name;
    }

    const std::string getPrintedName() const override {
        return "Folder_" + getName();
    }

    std::string getType() const override {
        return TYPE;
    }

private:

    std::string name;
};

const std::string Folder::TYPE = "Folder";

bool comparator(const std::map<std::string, int> &priorities, const std::unique_ptr<Base> &first, const std::unique_ptr<Base> &second) {
    const int priorityFirst = priorities.at(first->getType());
    const int prioritySecond = priorities.at(second->getType());
    if (priorityFirst != prioritySecond) {
        return priorityFirst > prioritySecond;
    } else {
        return first->getName() < second->getName();
    }
}

int main (int argc, char *const */*argv*/) {
    std::map<std::string, int> priorities;
    priorities.emplace(Folder::TYPE, 2);
    priorities.emplace(File::TYPE, 1);

    std::vector<std::unique_ptr<Base>> files;
    files.emplace_back(std::make_unique<Folder>("1"));
    files.emplace_back(std::make_unique<File>("3"));
    files.emplace_back(std::make_unique<File>("2"));
    files.emplace_back(std::make_unique<Folder>("4"));

    std::sort(files.begin(), files.end(), std::bind(comparator, std::ref(priorities), _1, _2));

    for (const std::unique_ptr<Base> &element: files) {
        std::cout << element->getPrintedName() << " ";
    }
        
    std::cout << std::endl;
    
    return 0;
}
