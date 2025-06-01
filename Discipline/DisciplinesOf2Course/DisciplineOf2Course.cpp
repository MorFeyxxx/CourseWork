#include "DisciplinesOf2Course.h"

DisciplineConfig OOP() {
    DisciplineConfig config = {
        .name = "OOP",
        .has_labs = true,
        .lab_system = std::make_shared<FivePointSystem>(),
        .count_labs = 15,
        .has_cp = true,
        .mark_cp = MarkStatus::Fail,
        .has_exam = true,
        .mark_exam = MarkStatus::Fail
    };

    return config;
}

DisciplineConfig IO() {
    DisciplineConfig config = {
        .name = "Operations research",
        .has_labs = true,
        .lab_system = std::make_shared<FivePointSystem>(),
        .count_labs = 6,
        .has_exam = true,
        .mark_exam = MarkStatus::Fail
    };

    return config;
}

DisciplineConfig IT() {
    DisciplineConfig config = {
        .name = "Information theory",
        .has_labs = true,
        .lab_system = std::make_shared<FivePointSystem>(),
        .count_labs = 6,
        .has_test = true,
        .mark_test = MarkStatus::Fail
    };

    return config;
}

DisciplineConfig FOPTSZI() {
    DisciplineConfig config = {
        .name = "FOPTSZI",
        .has_cgt = true,
        .cgt_system = std::make_shared<FivePointSystem>(),
        .count_cgt = 3,
        .has_test = true,
        .mark_test = MarkStatus::Fail
    };

    return config;
}
