#include "Institute.h"
#include "../Department/Department.h"

Institute::Institute(const std::string& name) : ComponentBase(name, "Institute") {}

void Institute::print(int indent = 0) const {
    std::cout << std::string(indent, ' ') << "Институт: " << name << "\n";
    for (const auto& child : children) {
        child->print(indent + 2);
        std::cout << std::endl;
    }
}

json Institute::to_json() const {
    json j;
    j["type"] = type;
    j["name"] = name;
    j["children"] = json::array();
    for (const auto& child : children) {
        j["children"].push_back(child->to_json());
    }
    return j;
}

std::shared_ptr<Institute> Institute::from_json(const json& j) {
    std::string name = j.at("name").get<std::string>();

    auto component = std::make_shared<Institute>(name);

    if (j.contains("children")) {
        for (const auto& child_json : j.at("children")) {
            auto child = Department::from_json(child_json);
            component->add(child);
        }
    }

    return component;
}