#include <iostream>
#include <variant>
#include <vector>
#include <algorithm>
#include <array>
#include <functional>
using namespace std::placeholders;

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

struct ElementPriorityBase {
    virtual std::string printedType() const = 0;

    virtual void setPriority(int p) = 0;
};

template<class T>
struct ElementPriority: public ElementPriorityBase {
    int priority = 0;

    std::string printedType() const override {
        if constexpr (std::is_same_v<T, File>) {
            return "File";
        } else if constexpr (std::is_same_v<T, Folder>) {
            return "Folder";
        } else if constexpr (std::is_same_v<T, Symlink>) {
            return "Symlink";
        }
    }

    void setPriority(int p) override {
        priority = p;
    }
};

template<typename T>
struct Empty {};

template<typename... Ts>
auto makeElementPriorityTupleFromElementVariant(Empty<std::variant<Ts...>>) -> std::tuple<ElementPriority<Ts>...> {
    return std::make_tuple(ElementPriority<Ts>()...);
}

using ElementPriorityTuple = decltype(makeElementPriorityTupleFromElementVariant(std::declval<Empty<Element>>()));

template<typename tuple_t>
std::vector<std::pair<std::string, std::reference_wrapper<ElementPriorityBase>>> makeElementPriorityBaseArray(tuple_t& tuple) {
    constexpr auto get_array = [](auto&... e){
        return std::vector<std::pair<std::string, std::reference_wrapper<ElementPriorityBase>>>{std::make_pair(e.printedType(), std::ref(static_cast<ElementPriorityBase&>(e)))...};
    };
    return std::apply(get_array, tuple);
}

template<class T>
int priority(const ElementPriorityTuple &array, const T &element) {
    return std::get<ElementPriority<T>>(array).priority;
}

bool comparator(const ElementPriorityTuple &array, const Element &first, const Element &second) {
    const bool result = std::visit([&](const auto &contentFirst){
        return std::visit([&](const auto &contentSecond){
            const int priorityFirst = priority(array, contentFirst);
            const int prioritySecond = priority(array, contentSecond);
            if (priorityFirst != prioritySecond) {
                return priorityFirst > prioritySecond;
            } else {
                return contentFirst.getName() < contentSecond.getName();
            }
        }, second);
    }, first);
    return result;
}

int main (int argc, char *const */*argv*/) {
    ElementPriorityTuple tuple = makeElementPriorityTupleFromElementVariant(Empty<Element>());

    const std::vector<std::pair<std::string, std::reference_wrapper<ElementPriorityBase>>> arrayToFill = makeElementPriorityBaseArray(tuple);

    for (const auto &[typeStr, element]: arrayToFill) {
        if (typeStr == "Folder") {
            element.get().setPriority(3);
        } else if (typeStr == "File") {
            element.get().setPriority(2);
        } else if (typeStr == "Symlink") {
            element.get().setPriority(1);
        }
    }

    std::vector<Element> files = {Folder("1"), File("3"), File("2"), Folder("4"), Symlink("1"), Symlink("5"), Symlink("1")};

    std::sort(files.begin(), files.end(), std::bind(comparator, std::ref(tuple), _1, _2));

    for (const Element &element: files) {
        std::visit([](const auto &elem) {
            std::cout << elem.getPrintedName() << " ";
        }, element);
    }
        
    std::cout << std::endl;
    
    return 0;
}
