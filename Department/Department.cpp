#include "Department.h"
#include "../Group/Group.h"

Department::Department(const std::string& name) : ComponentBase(name, "Department") {}

void Department::print(int indent = 0) const {
    std::cout << std::string(indent, ' ') << "Кафедра: " << name << "\n";
    for (const auto& child : children) {
        child->print(indent + 2);
        std::cout << std::endl;
    }
}

json Department::to_json() const {
    json j;
    j["type"] = type;
    j["name"] = name;
    j["children"] = json::array();
    for (const auto& child : children) {
        j["children"].push_back(child->to_json());
    }
    return j;
}

std::shared_ptr<Department> Department::from_json(const json& j) {
    std::string type = j.at("type").get<std::string>();
    std::string name = j.at("name").get<std::string>();

    auto component = std::make_shared<Department>(name);

    if (j.contains("children")) {
        for (const auto& child_json : j.at("children")) {
            auto child = Group::from_json(child_json);
            component->add(child);
        }
    }

    return component;
}