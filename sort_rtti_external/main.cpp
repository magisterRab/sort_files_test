#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <map>
#include <typeindex>
#include <functional>
using namespace std::placeholders;

class Base {
public:

    virtual const std::string& getName() const = 0;

    virtual const std::string getPrintedName() const = 0;

    virtual ~Base() = default;

};

class File: public Base {
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

private:

    std::string name;
};

class Folder: public Base {
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

private:

    std::string name;
};

bool comparator(const std::unordered_map<std::type_index, std::pair<std::string, int>> &priorities, const std::unique_ptr<Base> &first, const std::unique_ptr<Base> &second) {
    const int priorityFirst = priorities.at(typeid(*first.get())).second;
    const int prioritySecond = priorities.at(typeid(*second.get())).second;
    if (priorityFirst != prioritySecond) {
        return priorityFirst > prioritySecond;
    } else {
        return first->getName() < second->getName();
    }
}

int main (int argc, char *const */*argv*/) {
    std::unordered_map<std::type_index, std::pair<std::string, int>> priorities;
    priorities.emplace(std::piecewise_construct, std::forward_as_tuple(typeid(Folder)), std::forward_as_tuple("Folder", 2));
    priorities.emplace(std::piecewise_construct, std::forward_as_tuple(typeid(File)), std::forward_as_tuple("File", 1));

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
