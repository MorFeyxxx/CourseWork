#include "PassFailSystem.h"

PassFailSystem::PassFailSystem() : AssessmentSystem("Зачтено/Не зачтено", 0, 1) {}

std::pair<bool, int> PassFailSystem::evaluate(const std::vector<int>& marks) const  {
    for (int mark : marks)
        if (mark != 1) {
            return {false, 0};
        }

    return {true, 1};
}