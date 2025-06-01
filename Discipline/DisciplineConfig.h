#ifndef DISCIPLINECONFIG_H
#define DISCIPLINECONFIG_H

#include "../AssessmentSystem/FivePointSystem/FivePointSystem.h"
#include "../AssessmentSystem/PassFailSystem/PassFailSystem.h"
#include "../MarkStatus.h"
#include <memory>

struct DisciplineConfig {
    std::string name = "";
    bool has_labs = false;
    std::shared_ptr<AssessmentSystem> lab_system = std::make_shared<FivePointSystem>();
    size_t count_labs = 0;

    bool has_cgt = false;
    std::shared_ptr<AssessmentSystem> cgt_system = std::make_shared<PassFailSystem>();
    size_t count_cgt = 0;

    bool has_cp = false;
    MarkStatus mark_cp = MarkStatus::None;
    bool has_test = false;
    MarkStatus mark_test = MarkStatus::None;
    bool has_exam = false;
    MarkStatus mark_exam = MarkStatus::None;
};

#endif //DISCIPLINECONFIG_H
