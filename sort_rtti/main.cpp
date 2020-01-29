#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>

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

bool comparator(const std::unique_ptr<Base> &first, const std::unique_ptr<Base> &second) {
    if (dynamic_cast<Folder*>(first.get()) != nullptr && dynamic_cast<Folder*>(second.get()) != nullptr) {
        return first->getName() < second->getName();
    } else if (dynamic_cast<Folder*>(first.get()) != nullptr && dynamic_cast<File*>(second.get()) != nullptr) {
        return true;
    } else if (dynamic_cast<File*>(first.get()) != nullptr && dynamic_cast<Folder*>(second.get()) != nullptr) {
        return false;
    } else {
        return first->getName() < second->getName();
    }
}

int main (int argc, char *const */*argv*/) {
    std::vector<std::unique_ptr<Base>> files;
    files.emplace_back(std::make_unique<Folder>("1"));
    files.emplace_back(std::make_unique<File>("3"));
    files.emplace_back(std::make_unique<File>("2"));
    files.emplace_back(std::make_unique<Folder>("4"));

    std::sort(files.begin(), files.end(), comparator);

    for (const std::unique_ptr<Base> &element: files) {
        std::cout << element->getPrintedName() << " ";
    }
        
    std::cout << std::endl;
    
    return 0;
}
