cmake_minimum_required(VERSION 3.28)
project(CourseWork)

set(CMAKE_CXX_STANDARD 17)

add_executable(CourseWork main.cpp
        json.hpp
        ComponentBase/ComponentBase.h
        ComponentBase/ComponentBase.cpp
        Database/Database.h
        Database/Database.cpp
        University/University.h
        University/University.cpp
        Institute/Institute.h
        Institute/Institute.cpp
        Department/Department.h
        Department/Department.cpp
        Group/Group.h
        Group/Group.cpp
        Student/Student.h
        Student/Student.cpp
        AssessmentSystem/AssessmentSystem.h
        AssessmentSystem/AssessmentSystem.cpp
        AssessmentSystem/FivePointSystem/FivePointSystem.h
        AssessmentSystem/FivePointSystem/FivePointSystem.cpp
        AssessmentSystem/PassFailSystem/PassFailSystem.h
        AssessmentSystem/PassFailSystem/PassFailSystem.cpp
        MarkAndAssessSys/MarkAndAssessSys.h
        MarkAndAssessSys/MarkAndAssessSys.cpp
        MarkStatus.h
        MarkStatus.h
        Test/Test.h
        Test/Test.cpp
        Exam/Exam.h
        Exam/Exam.cpp
        CourseProject/CourseProject.h
        CourseProject/CourseProject.cpp
        LaboratoryWorks/LaboratoryWorks.h
        LaboratoryWorks/LaboratoryWorks.cpp
        CalcGraphTask/CalcGraphTask.h
        CalcGraphTask/CalcGraphTask.cpp
        Discipline/DisciplineConfig.h)
