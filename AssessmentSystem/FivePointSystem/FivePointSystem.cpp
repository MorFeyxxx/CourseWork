#include "FivePointSystem.h"
#include "cmath"

FivePointSystem::FivePointSystem() : AssessmentSystem("Пятибальная система", 2, 5) {}

std::pair<bool, int> FivePointSystemevaluate(const std::vector<int>& marks) {
    if (marks.empty()) {
        return {false, 0};
    }

    int sum = 0;
    for (int mark : marks) {
        sum += mark;
    }

    double raw_score = static_cast<double>(sum) / marks.size();
    int score = static_cast<int>(std::round(raw_score));

    bool possible = false;
    if(score > 2) {
        possible = true;
    }

    return {possible, score};
}