#include "University.h"
#include "../Institute/Institute.h"

University::University(const std::string& name) : ComponentBase(name, "University") {}

void University::print(int indent = 0) const {
    std::cout << std::string(indent, ' ') << "Университет: " << name << "\n";
    for (const auto& child : children) {
        child->print(indent + 2);
        std::cout << std::endl;
    }
}

json University::to_json() const {
    json j;
    j["type"] = type;
    j["name"] = name;
    j["children"] = json::array();
    for (const auto& child : children) {
        j["children"].push_back(child->to_json());
    }
    return j;
}

std::shared_ptr<University> University::from_json(const json& j) {
    std::string name = j.at("name").get<std::string>();

    auto component = std::make_shared<University>(name);

    if (j.contains("children")) {
        for (const auto& child_json : j.at("children")) {
            auto child = Institute::from_json(child_json);
            component->add(child);
        }
    }

    return component;
}
