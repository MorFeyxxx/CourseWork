#ifndef EXAM_H
#define EXAM_H

#include "../AssessmentSystem/AssessmentSystem.h"
#include "../ComponentBase/ComponentBase.h"
#include "../DateAndAssessSys/DateAndAssessSys.h"
#include "../AssessmentSystem/PassFailSystem/PassFailSystem.h"
#include "../MarkStatus.h"
#include <string>
#include <memory>

class Exam: public ComponentBase, public DateAndAssessSys {
    MarkStatus mark;

public:
    Exam(const std::shared_ptr<AssessmentSystem> system, MarkStatus mark_ = MarkStatus::None);

    void set_mark(int new_mark);
    MarkStatus get_mark() const;

    void print(int indent = 0) const override;

    json to_json() const override;
    static std::shared_ptr<Exam> from_json(const json& j);
};

#endif //EXAM_H
