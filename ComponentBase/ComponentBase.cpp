#include "ComponentBase.h"

ComponentBase::ComponentBase(std::string n, std::string t): name(n), type(t) {}

std::string ComponentBase::get_name() {
    return name;
}

std::string ComponentBase::get_type() {
    return type;
}

void ComponentBase::change_name(std::string new_name) {
    name = new_name;
}

void ComponentBase::add(std::shared_ptr<ComponentBase> component) {
    children.push_back(component);
    component->set_parent(shared_from_this());
}

void ComponentBase::set_parent(std::shared_ptr<ComponentBase> p) {
    parent = p;
}

std::shared_ptr<ComponentBase> ComponentBase::get_parent() const {
    return parent.lock();
}

void ComponentBase::remove(std::shared_ptr<ComponentBase> component) {
    children.erase(std::remove(children.begin(), children.end(), component), children.end());
}

const std::vector<std::shared_ptr<ComponentBase>>& ComponentBase::get_children() const {
    return children;
}

void ComponentBase::print(int indent = 0) const {
    std::cout << std::string(indent, ' ') << name << std::endl;
    for (const auto& child : children) {
        child->print(indent + 2);
    }
}

void ComponentBase::print_children(int indent = 0) {
    std::cout << std::string(indent, ' ') << name << std::endl;
    for(const auto& child: children) {
        std::cout << std::string(indent+2, ' ') << child->get_name() << std::endl;
    }
    std::cout << std::endl;
}

json ComponentBase::to_json() const {
    json j;
    j["type"] = type;
    j["name"] = name;
    j["children"] = json::array();
    for (const auto& child : children) {
        j["children"].push_back(child->to_json());
    }

    return j;
}

void ComponentBase::change_mark_lab(int index, int mark) {}
void ComponentBase::change_mark_cgt(int index, int mark) {}
void ComponentBase::change_mark_cp(int mark) {}
void ComponentBase::change_mark_test(int mark) {}
void ComponentBase::change_mark_exam(int mark) {}