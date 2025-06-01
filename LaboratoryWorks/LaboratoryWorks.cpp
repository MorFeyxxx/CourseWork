#include "LaboratoryWorks.h"

LaboratoryWorks::LaboratoryWorks(const std::shared_ptr<AssessmentSystem> system, size_t count = 0):
    ComponentBase("", "LaboratoryWorks"), assessment_system(system), marks(count, 0) {}

void LaboratoryWorks::add_lab() {
    marks.push_back(0);
}

void LaboratoryWorks::remove_lab() {
    if (!marks.empty()) {
        marks.pop_back();
    }
}

std::shared_ptr<AssessmentSystem> LaboratoryWorks::get_system() const {
    return assessment_system;
}

void LaboratoryWorks::set_mark(int index, int mark) {
    if (index-1 >= marks.size()) {
        throw std::out_of_range("Нет такой лабораторной работы!");
    }

    if(assessment_system->validate_mark(mark)) {
        marks[index-1] = mark;
    }
}

std::pair<bool, int> LaboratoryWorks::calculate_final_mark() const {
    return assessment_system->evaluate(marks);
}

void LaboratoryWorks::print(int indent = 0) const {
    std::cout << std::string(indent, ' ') << "Лабораторные работы: "
              << " (Система: " << assessment_system->get_description() << ")\n";
    for (size_t i = 0; i < marks.size(); ++i) {
        std::cout << std::string(indent + 2, ' ') << "ЛР " << (i + 1)
                  << ": " << marks[i] << "\n";
    }
}

json LaboratoryWorks::to_json() const {
    json j;
    j["type"] = type;
    j["system"] = assessment_system->get_description();
    j["marks"] = marks;
    return j;
}

std::shared_ptr<LaboratoryWorks> LaboratoryWorks::from_json(const json& j, std::shared_ptr<AssessmentSystem> system) {
    auto lab = std::make_shared<LaboratoryWorks>(system, j.at("marks").size());
    lab->marks = j.at("marks").get<std::vector<int>>();

    return lab;
}