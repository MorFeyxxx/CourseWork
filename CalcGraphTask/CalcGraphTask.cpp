#include "CalcGraphTask.h"

CalcGraphTask::CalcGraphTask(const std::shared_ptr<AssessmentSystem> system, size_t count = 0):
    ComponentBase("", "CalcGraphTask"), assessment_system(system), marks(count, 0) {}

void CalcGraphTask::add_cgt() {
    marks.push_back(0);
}

void CalcGraphTask::remove_cgt() {
    if (!marks.empty()) {
        marks.pop_back();
    }
}

std::shared_ptr<AssessmentSystem> CalcGraphTask::get_system() const {
    return assessment_system;
}

void CalcGraphTask::set_mark(int index, int mark) {
    if (index-1 >= marks.size()) {
        throw std::out_of_range("Нет такого расчетно-графического задания!");
    }

    if(assessment_system->validate_mark(mark)) {
        marks[index-1] = mark;
    }
}

std::pair<bool, int> CalcGraphTask::calculate_final_mark() const {
    return assessment_system->evaluate(marks);
}

void CalcGraphTask::print(int indent = 0) const {
    std::cout << std::string(indent, ' ') << "Расчетно-графические задания: "
              << " (Система: " << assessment_system->get_description() << ")\n";
    for (size_t i = 0; i < marks.size(); ++i) {
        std::cout << std::string(indent + 2, ' ') << "РГЗ " << (i + 1)
                  << ": " << marks[i] << "\n";
    }
}

json CalcGraphTask::to_json() const {
    json j;
    j["type"] = type;
    j["system"] = assessment_system->get_description();
    j["marks"] = marks;
    return j;
}

std::shared_ptr<CalcGraphTask> CalcGraphTask::from_json(const json& j, std::shared_ptr<AssessmentSystem> system) {
    auto cgt = std::make_shared<CalcGraphTask>(system, j.at("marks").size());
    cgt->marks = j.at("marks").get<std::vector<int>>();

    return cgt;
}