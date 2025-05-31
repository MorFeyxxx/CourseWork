#include "DateAndAssessSys.h"

DateAndAssessSys::DateAndAssessSys(const std::shared_ptr<AssessmentSystem> system):
    assessment_system(system), date("01/01/0000") {}

void DateAndAssessSys::change_date(std::string new_date) {
    validate_date(new_date);

    date = new_date;
}

std::string DateAndAssessSys::get_date() const {
    return date;
}

bool DateAndAssessSys::is_leap_year(int year) const {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

bool DateAndAssessSys::is_valid_date(const std::string& date_str) const {
    std::regex pattern(R"((\d{2})/(\d{2})/(\d{4}))");
    std::smatch match;

    if (!std::regex_match(date_str, match, pattern)) {
        return false;
    }

    int day = std::stoi(match[1]);
    int month = std::stoi(match[2]);
    int year = std::stoi(match[3]);

    if (month < 1 || month > 12 || day < 1) {
        return false;
    }

    int days_in_month[] = {31, (is_leap_year(year) ? 29 : 28), 31, 30, 31, 30,
                          31, 31, 30, 31, 30, 31};

    if (day > days_in_month[month - 1]) {
        return false;
    }

    return true;
}

void DateAndAssessSys::validate_date(const std::string& date_str) const {
    if(!is_valid_date(date_str)) {
        throw std::out_of_range("Дата " + date_str + " не корректна");
    }
}