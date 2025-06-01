#ifndef COURSEPROJECT_H
#define COURSEPROJECT_H

#include "../AssessmentSystem/AssessmentSystem.h"
#include "../ComponentBase/ComponentBase.h"
#include "../MarkStatus.h"

class CourseProject: public ComponentBase {
    MarkStatus mark;
    std::shared_ptr<AssessmentSystem> assessment_system;

public:
    CourseProject(const std::shared_ptr<AssessmentSystem> system, MarkStatus mark_);

    void set_mark(int new_mark);
    MarkStatus get_mark() const;

    void print(int indent) const override;

    json to_json() const override;
    static std::shared_ptr<CourseProject> from_json(const json& j);
};

#endif //COURSEPROJECT_H
