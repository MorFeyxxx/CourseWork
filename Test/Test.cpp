#include "Test.h"

Test::Test(const std::shared_ptr<AssessmentSystem> system, MarkStatus mark_ = MarkStatus::None): ComponentBase("", "Test"),
    MarkAndAssessSys(system, mark_) {}

void Test::set_mark(int new_mark) {
    if(assessment_system->validate_mark(new_mark)) {
        mark = new_mark ? MarkStatus::Pass : MarkStatus::Fail;
    }
}

void Test::print(int indent = 0) const{
    std::cout << std::string(indent, ' ') << "Зачет: ";

    switch (mark) {
        case MarkStatus::Pass:
            std::cout << "Получен" << std::endl;
        break;
        case MarkStatus::Fail:
            std::cout << "Не получен" << std::endl;
        break;
        case MarkStatus::None:
            std::cout << "Отсутствует" << std::endl;
        break;
    }
}

json Test::to_json() const {
    json j;
    j["type"] = type;
    j["name"] = name;

    switch (mark) {
        case MarkStatus::Pass: j["mark"] = 1; break;
        case MarkStatus::Fail: j["mark"] = 0; break;
        case MarkStatus::None: j["mark"] = -1; break;
    }

    return j;
}

std::shared_ptr<Test> Test::from_json(const json& j) {
    auto system = std::make_shared<PassFailSystem>();

    auto test = std::make_shared<Test>(system);

    if (j.contains("name")) {
        test->change_name(j["name"].get<std::string>());
    }

    if (j.contains("mark")) {
        int m = j["mark"].get<int>();
        test->set_mark(m);
    }

    return test;
}