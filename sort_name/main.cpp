#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>

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

bool comparator(const std::unique_ptr<Base> &first, const std::unique_ptr<Base> &second) {
    if (first->getType() == Folder::TYPE && second->getType() == Folder::TYPE) {
        return first->getName() < second->getName();
    } else if (first->getType() == Folder::TYPE && second->getType() == File::TYPE) {
        return true;
    } else if (first->getType() == File::TYPE && second->getType() == Folder::TYPE) {
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
