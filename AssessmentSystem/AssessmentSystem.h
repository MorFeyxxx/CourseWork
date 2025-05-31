#ifndef ASSESSMENTSYSTEM_H
#define ASSESSMENTSYSTEM_H

#include <vector>
#include <string>

class AssessmentSystem {
protected:
    int min_mark;
    int max_mark;
    std::string description;

public:
    AssessmentSystem(std::string desc, int min, int max);
    virtual ~AssessmentSystem() = default;

    bool validate_mark(int mark) const;

    virtual std::pair<bool, int> evaluate(const std::vector<int>& marks) const = 0;

    int get_min_mark() const;
    int get_max_mark() const;
    std::string get_description() const;
};

#endif //ASSESSMENTSYSTEM_H
