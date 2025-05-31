#include "iostream"
#include "AssessmentSystem.h"

AssessmentSystem::AssessmentSystem(std::string desc, int min, int max):
min_mark(min), max_mark(max), description(desc) {}

bool AssessmentSystem::validate_mark(int mark) const {
    if (mark < min_mark || mark > max_mark) {
        std::cout << "Оценка " << std::to_string(mark) << \
            " не входит в диапазон [" << std::to_string(min_mark) << \
                ", " << std::to_string(max_mark) << "]" << std::endl;
        return false;
    }

    return true;
}

int AssessmentSystem::get_min_mark() const {
    return min_mark;
}

int AssessmentSystem::get_max_mark() const {
    return max_mark;
}

std::string AssessmentSystem::get_description() const {
    return description;
}