#include "Exam.h"


Exam::Exam(const std::shared_ptr<AssessmentSystem> system, MarkStatus mark_ = MarkStatus::None): ComponentBase("", "Exam"),
    DateAndAssessSys(system), mark(mark_) {}

void Exam::set_mark(int new_mark) {
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
MarkStatus Exam::get_mark() const{
    return mark;
}

void Exam::print(int indent = 0) const{
    std::cout << std::string(indent, ' ') << "Экзамен: ";

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
            std::cout << "Не решен" << std::endl;
            break;
        case MarkStatus::None:
            std::cout << "Отсутствует" << std::endl;
            break;
    }
}

json Exam::to_json() const {
    json j;
    j["type"] = type;
    j["name"] = name;
    j["date"] = date;

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

std::shared_ptr<Exam> Exam::from_json(const json& j) {
    auto system = std::make_shared<FivePointSystem>();

    auto exam = std::make_shared<Exam>(system);

    if (j.contains("name")) {
        exam->change_name(j["name"].get<std::string>());
    }

    if (j.contains("date")) {
        exam->change_date(j["date"].get<std::string>());
    }

    if (j.contains("mark")) {
        int m = j["mark"].get<int>();
        exam->set_mark(m);
    }

    return exam;
}