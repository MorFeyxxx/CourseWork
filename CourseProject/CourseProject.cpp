#include "CourseProject.h"

CourseProject::CourseProject(const std::shared_ptr<AssessmentSystem> system, MarkStatus mark_ = MarkStatus::None):
    ComponentBase("", "CourseProject"),assessment_system(system), mark(mark_) {}

void CourseProject::set_mark(int new_mark) {
    if(new_mark == 0) {
        mark = MarkStatus::Fail;
        return;
    }

    if(assessment_system->validate_mark(new_mark)) {
        switch (new_mark) {
            case 2:
                mark = MarkStatus::NotSatisfactory;
                break;
            case 3:
                mark = MarkStatus::Satisfactory;
                break;
            case 4:
                mark = MarkStatus::Well;
                break;
            case 5:
                mark = MarkStatus::Great;
                break;
            default:
                mark = MarkStatus::None;
                break;
        }
    }
}
MarkStatus CourseProject::get_mark() const{
    return mark;
}

void CourseProject::print(int indent = 0) const {
    std::cout << std::string(indent, ' ') << "Курсовой проект: ";

    switch (mark) {
        case MarkStatus::Great:
            std::cout << "Отлично" << std::endl;
            break;
        case MarkStatus::Well:
            std::cout << "Хорошо" << std::endl;
            break;
        case MarkStatus::Satisfactory:
            std::cout << "Удовлетворительно" << std::endl;
            break;
        case MarkStatus::NotSatisfactory:
            std::cout << "Не удовлетворительно" << std::endl;
            break;
        case MarkStatus::Fail:
            std::cout << "Не сдан" << std::endl;
            break;
        case MarkStatus::None:
            std::cout << "Отсутствует" << std::endl;
            break;
    }
}

json CourseProject::to_json() const {
    json j;
    j["type"] = type;
    j["name"] = name;

    switch (mark) {
        case MarkStatus::Great: j["mark"] = 5; break;
        case MarkStatus::Well: j["mark"] = 4; break;
        case MarkStatus::Satisfactory: j["mark"] = 3; break;
        case MarkStatus::NotSatisfactory: j["mark"] = 2; break;
        case MarkStatus::Fail: j["mark"] = 0; break;
        case MarkStatus::None: j["mark"] = -1; break;
    }

    return j;
}
std::shared_ptr<CourseProject> CourseProject::from_json(const json& j) {
    std::shared_ptr<AssessmentSystem> system;

    auto cp = std::make_shared<CourseProject>(system);

    if (j.contains("name")) {
        cp->change_name(j["name"].get<std::string>());
    }

    if (j.contains("mark")) {
        int m = j["mark"].get<int>();
        cp->set_mark(m);
    }

    return cp;
}