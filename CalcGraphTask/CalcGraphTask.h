#ifndef CALCGRAPHTASK_H
#define CALCGRAPHTASK_H

#include "../AssessmentSystem/AssessmentSystem.h"
#include "../ComponentBase/ComponentBase.h"
#include <vector>
#include <memory>
#include <iostream>

class CalcGraphTask: public ComponentBase {
protected:
    std::shared_ptr<AssessmentSystem> assessment_system;
    std::vector<int> marks;

public:
    CalcGraphTask(const std::shared_ptr<AssessmentSystem> system, size_t count);

    void add_cgt();
    void remove_cgt();

    std::shared_ptr<AssessmentSystem> get_system() const;

    void set_mark(int index, int mark);
    std::pair<bool, int> calculate_final_mark() const;

    void print(int indent) const override;

    json to_json() const override;
    static std::shared_ptr<CalcGraphTask> from_json(const json& j, std::shared_ptr<AssessmentSystem> system);
};

#endif //CALCGRAPHTASK_H
