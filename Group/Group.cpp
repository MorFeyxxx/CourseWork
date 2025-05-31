#include "Group.h"
#include "../Student/Student.h"

Group::Group(const std::string& name) : ComponentBase(name, "Group") {}

void Group::print(int indent = 0) const {
    std::cout << std::string(indent, ' ') << "Группа: " << name << "\n";
    for (const auto& child : children) {
        child->print(indent + 2);
        std::cout << std::endl;
    }
}

json Group::to_json() const {
    json j;
    j["type"] = type;
    j["name"] = name;
    j["children"] = json::array();
    for (const auto& child : children) {
        j["children"].push_back(child->to_json());
    }
    return j;
}

std::shared_ptr<Group> Group::from_json(const json& j) {
    std::string name = j.at("name").get<std::string>();

    auto component = std::make_shared<Group>(name);

    if (j.contains("children")) {
        for (const auto& child_json : j.at("children")) {
            auto child = Student::from_json(child_json);
            component->add(child);
        }
    }

    return component;
}