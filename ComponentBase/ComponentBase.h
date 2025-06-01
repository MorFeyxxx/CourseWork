#ifndef COMPONENTBASE_H
#define COMPONENTBASE_H

#include <iostream>
#include <string.h>
#include <memory>
#include "../json.hpp"

using json = nlohmann::ordered_json;

class ComponentBase: public std::enable_shared_from_this<ComponentBase> {
protected:
    std::string name;
    std::string type;
    std::vector<std::shared_ptr<ComponentBase>> children;

    std::weak_ptr<ComponentBase> parent;

public:
    ComponentBase(std::string n, std::string t);

    std::string get_name();
    std::string get_type();
    void change_name(std::string new_name);

    virtual void print(int indent) const = 0;
    void print_children(int indent);

    void add(std::shared_ptr<ComponentBase> component);
    void remove(std::shared_ptr<ComponentBase> component);

    const std::vector<std::shared_ptr<ComponentBase>>& get_children() const;
    void set_parent(std::shared_ptr<ComponentBase> p);

    std::shared_ptr<ComponentBase> get_parent() const;

    virtual json to_json() const;
    virtual ~ComponentBase() = default;

    virtual void change_mark_lab(int index, int mark);
    virtual void change_mark_cgt(int index, int mark);
    virtual void change_mark_cp(int mark);
    virtual void change_mark_test(int mark);
    virtual void change_mark_exam(int mark);
};

#endif //COMPONENTBASE_H
