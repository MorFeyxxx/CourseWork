#ifndef DISCIPLINE_H
#define DISCIPLINE_H

#include "../ComponentBase/ComponentBase.h"
#include "../LaboratoryWorks/LaboratoryWorks.h"
#include "../Exam/Exam.h"
#include "../Test/Test.h"
#include "../CalcGraphTask/CalcGraphTask.h"
#include "../CourseProject/CourseProject.h"
#include "DisciplineConfig.h"
#include "../AssessmentSystem/FivePointSystem/FivePointSystem.h"
#include "../AssessmentSystem/PassFailSystem/PassFailSystem.h"

class Discipline : public ComponentBase {
    std::optional<LaboratoryWorks> labs;
    std::optional<CalcGraphTask> cgt;
    std::optional<CourseProject> cp;
    std::optional<Test> info_test;
    std::optional<Exam> info_exam;

public:
    Discipline(const std::string& name, const DisciplineConfig& config);

    void print(int indent) const override;

    void change_mark_lab(int index, int mark);
    void change_mark_cgt(int index, int mark);
    void change_mark_cp(int mark);
    void change_mark_test(int mark);
    void change_mark_exam(int mark);

    json to_json() const override;
    static std::shared_ptr<Discipline> from_json(const json& j);
};

#endif //DISCIPLINE_H
