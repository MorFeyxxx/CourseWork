#include "Student.h"
#include "../Discipline/Discipline.h"

Student::Student(const std::string& name): ComponentBase(name, "Student") {}

void Student::print(int indent = 0) const {
    std::cout << std::string(indent, ' ') << "Студент: " << name << "\n";
    for (const auto& child : children) {
        child->print(indent + 2);
        std::cout << std::endl;
    }
}

json Student::to_json() const {
    json j;
    j["type"] = type;
    j["name"] = name;
    j["children"] = json::array();
    for (const auto& child : children) {
        j["children"].push_back(child->to_json());
    }
    return j;
}

std::shared_ptr<Student> Student::from_json(const json& j) {
    std::string name = j.at("name").get<std::string>();

    auto component = std::make_shared<Student>(name);

    if (j.contains("children")) {
        for (const auto& child_json : j.at("children")) {
            auto child = Discipline::from_json(child_json);
            component->add(child);
        }
    }

    return component;
}