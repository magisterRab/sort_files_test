#include <iostream>
#include <variant>
#include <vector>
#include <algorithm>
#include <array>

class File {
public:

    File(const std::string &name)
        : name(name)
    {}

    const std::string& getName() const {
        return name;
    }

    const std::string getPrintedName() const {
        return "File_" + getName();
    }

private:

    std::string name;
};

class Folder {
public:

    Folder(const std::string &name)
        : name(name)
    {}

    const std::string& getName() const {
        return name;
    }

    const std::string getPrintedName() const {
        return "Folder_" + getName();
    }

private:

    std::string name;
};

class Symlink {
public:

    Symlink(const std::string &name)
        : name(name)
    {}

    const std::string& getName() const {
        return name;
    }

    const std::string getPrintedName() const {
        return "Symlink_" + getName();
    }

private:

    std::string name;
};

using Element = std::variant<Folder, File, Symlink>;

bool operator<(const Folder &first, const Folder &second) {
    return first.getName() < second.getName();
}

bool operator<(const Folder &first, const File &second) {
    return true;
}

bool operator<(const Folder &first, const Symlink &second) {
    return true;
}

bool operator<(const File &first, const Folder &second) {
    return false;
}

bool operator<(const File &first, const File &second) {
    return first.getName() < second.getName();
}

bool operator<(const File &first, const Symlink &second) {
    return true;
}

bool operator<(const Symlink &first, const Folder &second) {
    return false;
}

bool operator<(const Symlink &first, const File &second) {
    return false;
}

bool operator<(const Symlink &first, const Symlink &second) {
    return first.getName() < second.getName();
}

bool comparator(const Element &first, const Element &second) {
    const bool result = std::visit([&](const auto &contentFirst){
        return std::visit([&](const auto &contentSecond){
            return contentFirst < contentSecond;
        }, second);
    }, first);
    return result;
}

int main (int argc, char *const */*argv*/) {
    std::vector<Element> files = {Folder("1"), File("3"), File("2"), Folder("4"), Symlink("1"), Symlink("5"), Symlink("1")};

    std::sort(files.begin(), files.end(), comparator);

    for (const Element &element: files) {
        std::visit([](const auto &elem) {
            std::cout << elem.getPrintedName() << " ";
        }, element);
    }
        
    std::cout << std::endl;
    
    return 0;
}
