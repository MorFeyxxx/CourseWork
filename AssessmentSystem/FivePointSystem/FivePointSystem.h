#ifndef FIVEPOINTSYSTEM_H
#define FIVEPOINTSYSTEM_H

#include "../AssessmentSystem.h"

class FivePointSystem: public AssessmentSystem {
public:
    FivePointSystem();

    std::pair<bool, int> evaluate(const std::vector<int>& marks) const override;
};

#endif //FIVEPOINTSYSTEM_H
