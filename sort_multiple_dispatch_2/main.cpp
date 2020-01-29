#include <iostream>
#include <variant>
#include <vector>
#include <algorithm>
#include <array>
#include <experimental/type_traits>

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

struct ComparePriority {
    int operator()(const Folder &first, const File &second) const {
        return 1;
    }

    int operator()(const Folder &first, const Symlink &second) const {
        return 1;
    }

    int operator()(const Symlink &first, const File &second) const {
        return -1;
    }
};

bool comparator(const Element &first, const Element &second) {
    const bool result = std::visit([&](const auto &contentFirst){
        return std::visit([&](const auto &contentSecond){
            using TypeFirst = std::decay_t<decltype(contentFirst)>;
            using TypeSecond = std::decay_t<decltype(contentSecond)>;
            int compared;
            if constexpr (std::is_invocable_r_v<int, ComparePriority, TypeFirst, TypeSecond>) {
                compared = ComparePriority()(contentFirst, contentSecond);
            } else if constexpr (std::is_invocable_r_v<int, ComparePriority, TypeSecond, TypeFirst>) {
                compared = -ComparePriority()(contentSecond, contentFirst);
            } else if constexpr (std::is_same_v<TypeFirst, TypeSecond>){
                compared = 0;
            } else {
                static_assert(std::is_same_v<TypeFirst, TypeFirst>, "Error");
            }
            if (compared == 0) {
                return contentFirst.getName() < contentSecond.getName();
            } else {
                return compared == 1;
            }
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
