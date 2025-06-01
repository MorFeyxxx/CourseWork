#ifndef MARKANDASSESSSYS_H
#define MARKANDASSESSSYS_H

#include "../ComponentBase/ComponentBase.h"
#include "../AssessmentSystem/AssessmentSystem.h"
#include "../MarkStatus.h"
#include <string>
#include <memory>
#include <regex>

class MarkAndAssessSys {
protected:
    MarkStatus mark;
    std::shared_ptr<AssessmentSystem> assessment_system;

public:
    MarkAndAssessSys(const std::shared_ptr<AssessmentSystem> system, MarkStatus mark_);

    virtual void set_mark(int new_mark) = 0;
    MarkStatus get_mark() const;
};

#endif //MARKANDASSESSSYS_H
