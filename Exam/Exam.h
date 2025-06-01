#ifndef EXAM_H
#define EXAM_H

#include "../AssessmentSystem/AssessmentSystem.h"
#include "../ComponentBase/ComponentBase.h"
#include "../MarkAndAssessSys/MarkAndAssessSys.h"
#include "../AssessmentSystem/FivePointSystem/FivePointSystem.h"
#include <string>
#include <memory>

class Exam: public ComponentBase, public MarkAndAssessSys {
public:
    Exam(const std::shared_ptr<AssessmentSystem> system, MarkStatus mark_);

    void set_mark(int new_mark) override;

    void print(int indent) const override;

    json to_json() const override;
    static std::shared_ptr<Exam> from_json(const json& j);
};

#endif //EXAM_H
