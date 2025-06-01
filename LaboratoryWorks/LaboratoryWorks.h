#ifndef LABORATORYWORKS_H
#define LABORATORYWORKS_H

#include "../AssessmentSystem/AssessmentSystem.h"
#include "../ComponentBase/ComponentBase.h"
#include <vector>
#include <memory>
#include <iostream>

class LaboratoryWorks : public ComponentBase {
protected:
    std::shared_ptr<AssessmentSystem> assessment_system;
    std::vector<int> marks;

public:
    LaboratoryWorks(const std::shared_ptr<AssessmentSystem> system, size_t count);

    void add_lab();
    void remove_lab();

    std::shared_ptr<AssessmentSystem> get_system() const;

    void set_mark(int index, int mark);
    std::pair<bool, int> calculate_final_mark() const;

    void print(int indent) const override;

    json to_json() const override;
    static std::shared_ptr<LaboratoryWorks> from_json(const json& j, std::shared_ptr<AssessmentSystem> system);
};

#endif //LABORATORYWORKS_H
