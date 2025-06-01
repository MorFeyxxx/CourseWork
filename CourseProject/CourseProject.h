#ifndef COURSEPROJECT_H
#define COURSEPROJECT_H

#include "../AssessmentSystem/AssessmentSystem.h"
#include "../ComponentBase/ComponentBase.h"
#include "../MarkStatus.h"
#include "../MarkAndAssessSys/MarkAndAssessSys.h"

class CourseProject: public ComponentBase, public MarkAndAssessSys {
public:
    CourseProject(const std::shared_ptr<AssessmentSystem> system, MarkStatus mark_);

    void set_mark(int new_mark) override;

    void print(int indent) const override;

    json to_json() const override;
    static std::shared_ptr<CourseProject> from_json(const json& j);
};

#endif //COURSEPROJECT_H
