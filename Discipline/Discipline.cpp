#include "Discipline.h"

Discipline::Discipline(const std::string& name, const DisciplineConfig& config) : ComponentBase(name, "Discipline") {
    if (config.has_labs && config.lab_system) {
        labs = LaboratoryWorks(config.lab_system, config.count_labs);
    }
    if (config.has_cgt && config.cgt_system) {
        cgt = CalcGraphTask(config.cgt_system, config.count_cgt);
    }
    if (config.has_cp) {
        cp = CourseProject(std::make_shared<FivePointSystem>(), config.mark_cp);
    }
    if (config.has_test) {
        info_test = Test(std::make_shared<PassFailSystem>(), config.mark_test);
    }
    if (config.has_exam) {
        info_exam = Exam(std::make_shared<FivePointSystem>(), config.mark_exam);
    }
}

void Discipline::print(int indent = 0) const {
    std::string pad(indent, ' ');
    std::cout << pad << "Дисциплина: " << name << std::endl;

    if (labs) {
        labs->print(indent + 2);
        if(labs->get_system()->get_description() == "Пятибальная система") {
            std::cout << std::string(indent+4, ' ') << "Текущая оценка за лабораторные: " \
                << labs->calculate_final_mark().second << std::endl;;
        }
    }
    if (cgt) {
        cgt->print(indent + 2);
        if(cgt->get_system()->get_description() == "Пятибальная система") {
            std::cout << std::string(indent+4, ' ') << "Текущая оценка за РГЗ: " \
                << cgt->calculate_final_mark().second << std::endl;;
        }
    }

    bool can_be_test_exam = false;
    if(labs && cgt) {
        if(labs->calculate_final_mark().first && cgt->calculate_final_mark().first) {
            can_be_test_exam = true;
        }
    } else if(labs) {
        if(labs->calculate_final_mark().first) {
            can_be_test_exam = true;
        }
    } else if(cgt) {
        if(cgt->calculate_final_mark().first) {
            can_be_test_exam = true;
        }
    } else {
        can_be_test_exam = true;
    }

    if (cp) {
        cp->print(indent + 2);
    }
    if (info_test) {
        if(can_be_test_exam) {
            std::cout << std::string(indent+2, ' ') << "Зачет: Возможен" << std::endl;
        } else {
            std::cout << std::string(indent+2, ' ') << "Зачет: Не возможен" << std::endl;
        }
        info_test->print(indent + 4);
    }
    if (info_exam) {
        if(can_be_test_exam) {
            std::cout << std::string(indent+2, ' ') << "Экзамен: Возможен" << std::endl;
        } else {
            std::cout << std::string(indent+2, ' ') << "Экзамен: Не возможен" << std::endl;
        }
        info_exam->print(indent + 4);
    }
}
void Discipline::change_mark_lab(int index, int mark) {
    if(labs && index > 0) {
        labs->set_mark(index, mark);
    } else {
        std::cout << "Лабораторных работ по дисциплине нет!" << std::endl;
    }
}
void Discipline::change_mark_cgt(int index, int mark) {
    if(cgt && index > 0) {
        cgt->set_mark(index, mark);
    } else {
        std::cout << "РГЗ по дисциплине нет!" << std::endl;
    }
}
void Discipline::change_mark_cp(int mark) {
    if(cp) {
        cp->set_mark(mark);
    } else {
        std::cout << "Курсового проекта по дисциплине нет!" << std::endl;
    }
}
void Discipline::change_mark_test(int mark) {
    if (info_test) {
        info_test->set_mark(mark);
    } else {
        std::cout << "Зачета по дисциплине нет!" << std::endl;
    }
}
void Discipline::change_mark_exam(int mark) {
    if(info_exam) {
        info_exam->set_mark(mark);
    } else {
        std::cout << "Экзамена по дисциплине нет!" << std::endl;
    }
}

json Discipline::to_json() const {
    json j;
    j["type"] = type;
    j["name"] = name;

    if (labs) {
        j["labs"] = labs->to_json();
    }
    if (cgt) {
        j["cgt"] = cgt->to_json();
    }
    if (cp) {
        j["cp"] = cp->to_json();
    }
    if (info_test) {
        j["test"] = info_test->to_json();
    }
    if (info_exam) {
        j["exam"] = info_exam->to_json();
    }

    return j;
}
std::shared_ptr<Discipline> Discipline::from_json(const json& j) {
    DisciplineConfig config;

    if (j.contains("labs")) {
        config.has_labs = true;

        if (j["labs"].contains("system") && j["labs"]["system"] == "Зачтено/Не зачтено") {
            config.lab_system = std::make_shared<PassFailSystem>();
        } else {
            config.lab_system = std::make_shared<FivePointSystem>();
        }
    }

    if (j.contains("cgt")) {
        config.has_cgt = true;

        if (j["cgt"].contains("system") && j["cgt"]["system"] == "Зачтено/Не зачтено") {
            config.cgt_system = std::make_shared<PassFailSystem>();
        } else {
            config.cgt_system = std::make_shared<FivePointSystem>();
        }
    }

    if (j.contains("cp")) {
        config.has_cp = true;
    }
    if (j.contains("test")) {
        config.has_test = true;
    }
    if (j.contains("exam")) {
        config.has_exam = true;
    }

    auto discipline = std::make_shared<Discipline>(j.at("name").get<std::string>(), config);

    if (discipline->labs && j.contains("labs")) {
        *(discipline->labs) = *LaboratoryWorks::from_json(j.at("labs"), discipline->labs->get_system());
    }
    if (discipline->cgt && j.contains("cgt")) {
        *(discipline->cgt) = *CalcGraphTask::from_json(j.at("cgt"), discipline->cgt->get_system());
    }
    if (discipline->cp && j.contains("cp")) {
        *(discipline->cp) = *CourseProject::from_json(j.at("cp"));
    }
    if (discipline->info_test && j.contains("test")) {
        *(discipline->info_test) = *Test::from_json(j.at("test"));
    }
    if (discipline->info_exam && j.contains("exam")) {
        *(discipline->info_exam) = *Exam::from_json(j.at("exam"));
    }

    return discipline;
}