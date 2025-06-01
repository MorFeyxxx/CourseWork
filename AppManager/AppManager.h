#ifndef APPMANAGER_H
#define APPMANAGER_H

#include <iostream>
#include "string"
#include <fstream>
#include <windows.h>
#include "../json.hpp"
#include "../DataBase/DataBase.h"
#include "../University/University.h"
#include "../Institute/Institute.h"
#include "../Department/Department.h"
#include "../Group/Group.h"
#include "../Student/Student.h"
#include "../Discipline/DisciplinesOf2Course/DiscsOfGroup2Course.h"

std::string path = "DataBase of BGTU.json";

class AppManager {
    std::shared_ptr<ComponentBase> curr_ptr;
public:
    void run();

private:
    void discipline_management(Database& db, bool& exit);

    void go_over();
    void append();
    void remove();

    std::shared_ptr<Discipline> create_disc(std::string &name);
    bool already_there(std::string name);

    void change_mark();

    bool correct_input(int& input);
    bool correct_input_yes_no();
    void correct_input_assess_sys(std::string& assess);
    size_t correct_input_count();

    std::string shorten_group(const std::string& group_name);

    void add_discs_of_group(std::shared_ptr<ComponentBase> st);
    void add_disc(std::shared_ptr<ComponentBase> st, std::vector<DisciplineConfig> discs);
};

#endif //APPMANAGER_H
