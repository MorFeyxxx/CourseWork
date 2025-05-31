#ifndef DATEANDASSESSSYS_H
#define DATEANDASSESSSYS_H

#include "../AssessmentSystem/AssessmentSystem.h"
#include <string>
#include <memory>
#include <regex>

class DateAndAssessSys {
protected:
    std::string date;
    std::shared_ptr<AssessmentSystem> assessment_system;

public:
    DateAndAssessSys(const std::shared_ptr<AssessmentSystem> system);

    void change_date(std::string new_date);

    std::string get_date() const;

    bool is_leap_year(int year) const;

    bool is_valid_date(const std::string& date_str) const;

    void validate_date(const std::string& date_str) const;
};

#endif //DATEANDASSESSSYS_H
