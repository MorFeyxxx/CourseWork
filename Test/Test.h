#ifndef TEST_H
#define TEST_H

#include "../AssessmentSystem/AssessmentSystem.h"
#include "../ComponentBase/ComponentBase.h"
#include "../DateAndAssessSys/DateAndAssessSys.h"
#include "../AssessmentSystem/PassFailSystem/PassFailSystem.h"
#include "../MarkStatus.h"
#include <string>
#include <memory>

class Test: public ComponentBase, public DateAndAssessSys {
    MarkStatus mark;

public:
    Test(const std::shared_ptr<AssessmentSystem> system, MarkStatus mark_);

    void set_mark(int new_mark);
    MarkStatus get_mark() const;

    void print(int indent) const override;

    json to_json() const override;
    static std::shared_ptr<Test> from_json(const json& j);
};

#endif //TEST_H
