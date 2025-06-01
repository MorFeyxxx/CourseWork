#include "MarkAndAssessSys.h"

MarkAndAssessSys::MarkAndAssessSys(const std::shared_ptr<AssessmentSystem> system, MarkStatus mark_):
    assessment_system(system), mark(mark_) {}

MarkStatus MarkAndAssessSys::get_mark() const {
    return mark;
}

