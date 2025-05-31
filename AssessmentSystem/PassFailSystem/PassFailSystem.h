#ifndef PASSFAILSYSTEM_H
#define PASSFAILSYSTEM_H

#include "../AssessmentSystem.h"

class PassFailSystem: public AssessmentSystem {
public:
    PassFailSystem();

    std::pair<bool, int> evaluate(const std::vector<int>& marks) const override;
};

#endif //PASSFAILSYSTEM_H
