#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>

class Base {
public:

    virtual int getPriority() const = 0;

    virtual const std::string& getName() const = 0;

    virtual const std::string getPrintedName() const = 0;

    virtual ~Base() = default;

};

class File: public Base {
public:

    static int PRIORITY;

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

    int getPriority() const override {
        return PRIORITY;
    }

private:

    std::string name;
};

int File::PRIORITY = 0;

class Folder: public Base {
public:

    static int PRIORITY;

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

    int getPriority() const override {
        return PRIORITY;
    }

private:

    std::string name;
};

int Folder::PRIORITY = 0;

bool comparator(const std::unique_ptr<Base> &first, const std::unique_ptr<Base> &second) {
    const int priorityFirst = first->getPriority();
    const int prioritySecond = second->getPriority();
    if (priorityFirst != prioritySecond) {
        return priorityFirst > prioritySecond;
    } else {
        return first->getName() < second->getName();
    }
}

int main (int argc, char *const */*argv*/) {
    std::vector<std::pair<std::string, std::reference_wrapper<int>>> priorities{{"Folder", std::ref(Folder::PRIORITY)}, {"File", std::ref(File::PRIORITY)}};

    for (const auto &[type, ptr]: priorities) {
        if (type == "Folder") {
            ptr.get() = 2;
        } else if (type == "File") {
            ptr.get() = 1;
        }
    }

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
