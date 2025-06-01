#include "AppManager.h"

void AppManager::run() {
        Database& db = Database::get_instance();
        db.load(path);

        curr_ptr = db.data();

        while (true) {
            std::cout << std::endl;
            curr_ptr->print_children(0);

            bool changed = false;

            if(curr_ptr->get_type() != "Discipline") {
                std::cout << "\n1. Перейти в ...\n2. Добавить объект\n3. Удалить объект\n4. Вернуться\n5. Выход" << std::endl;
                int choice;
                std::cout << "\nВыбор операции: ";
                if(!correct_input(choice)) {
                    continue;
                }

                switch (choice) {
                    case 1: go_over(); break;
                    case 2: append(); changed = true; break;
                    case 3: remove(); changed = true; break;
                    case 4:
                        if(curr_ptr->get_type() != "University") {
                            curr_ptr = curr_ptr->get_parent();
                        } else {
                            std::cout << "Вернуться нельзя!" << std::endl;
                        }
                        break;
                    case 5: return;
                    default: std::cout << "====== Неверный ввод! ======" << std::endl;
                }
            } else {
                bool exit = false;

                discipline_management(db, exit);

                if(exit) {
                    break;
                }
            }

            if(changed) {
                db.save(path);
            }
        }
    }

void AppManager::discipline_management(Database& db, bool& exit) {
    while (true) {
        std::cout << std::endl;
        curr_ptr->print(0);

        std::cout << "\n1. Изменить оценку\n2. Удалить объект\n3. Вернуться\n4. Выход" << std::endl;
        int choice;
        std::cout << "\nВыбор операции: ";
        if (!correct_input(choice)) {
            continue;
        }

        switch (choice) {
            case 1: change_mark(); db.save(path); break;
            case 2: remove(); db.save(path); break;
            case 3: curr_ptr = curr_ptr->get_parent(); return;
            case 4: exit = true; return;
            default: std::cout << "====== Неверный ввод! ======" << std::endl;
        }
    }
}

void AppManager::go_over() {
    std::cout << "Введите название куда переходим: ";
    std::string choise;
    std::getline(std::cin, choise);

    if (choise.empty()) {
        std::cout << "Пустой ввод, попробуйте снова." << std::endl;
        return;
    }

    for(auto &child: curr_ptr->get_children()) {
        if(choise == child->get_name()) {
            curr_ptr = child;
            return;
        }
    }

    std::cout << "Такого варианта нет!" << std::endl;
}
void AppManager::append() {
    std::string name;

    std::string type = curr_ptr->get_type();
    if(type == "University") {
        std::cout << "Введите название для института: ";
        std::getline(std::cin, name);
        if(!already_there(name)) {
            auto inst = std::make_shared<Institute>(name);
            curr_ptr->add(inst);
        }
    }
    if(type == "Institute") {
        std::cout << "Введите название для кафедры: ";
        std::getline(std::cin, name);
        if(!already_there(name)) {
            auto depart = std::make_shared<Department>(name);
            curr_ptr->add(depart);
        }
    }
    if(type == "Department") {
        std::cout << "Введите название для группы: ";
        std::getline(std::cin, name);
        if(!already_there(name)) {
            auto group = std::make_shared<Group>(name);
            curr_ptr->add(group);
        }
    }
    if(type == "Group") {
        std::cout << "Введите имя для студента: ";
        std::getline(std::cin, name);
        if(!already_there(name)) {
            auto st = std::make_shared<Student>(name);
            curr_ptr->add(st);
            add_discs_of_group(st);
        }
    }
    if(type == "Student") {
        std::cout << "Введите название для дисциплины: ";
        std::getline(std::cin, name);
        if(!already_there(name)) {
            auto disc = create_disc(name);
            curr_ptr->add(disc);
        }
    }
}
std::shared_ptr<Discipline> AppManager::create_disc(std::string &name) {
    DisciplineConfig config;
    std::cout << "Настройка дисциплины:" << std::endl;

    std::cout << "Будут лабораторные работы? Да(1)/Нет(0): ";
    config.has_labs = correct_input_yes_no();
    if(config.has_labs) {
        std::cout << "Какая система оценивания? FivePoint/TEST: ";
        std::string assess;
        correct_input_assess_sys(assess);
        if(assess == "TEST") {
            config.lab_system = std::make_shared<PassFailSystem>();
        }

        std::cout << "Введите количество лабораторных: ";
        config.count_labs = correct_input_count();
    }

    std::cout << "\nБудут РГЗ? Да(1)/Нет(0): ";
    config.has_cgt = correct_input_yes_no();
    if(config.has_cgt) {
        std::cout << "Какая система оценивания? FivePoint/TEST: ";
        std::string assess;
        correct_input_assess_sys(assess);
        if(assess == "FivePoint") {
            config.cgt_system = std::make_shared<FivePointSystem>();
        }

        std::cout << "Введите количество РГЗ: ";
        config.count_cgt = correct_input_count();
    }

    std::cout << "\nБудет курсовой проект? Да(1)/Нет(0): ";
    config.has_cp = correct_input_yes_no();
    if(config.has_cp) {
        config.mark_cp = MarkStatus::Fail;
    }

    std::cout << "\nБудет зачет? Да(1)/Нет(0): ";
    config.has_test = correct_input_yes_no();
    if(config.has_test) {
        config.mark_test = MarkStatus::Fail;
    }

    std::cout << "\nБудет экзамен? Да(1)/Нет(0): ";
    config.has_exam = correct_input_yes_no();
    if(config.has_exam) {
        config.mark_exam = MarkStatus::Fail;
    }

    auto disc = std::make_shared<Discipline>(name, config);

    return disc;
}
bool AppManager::already_there(std::string name) {
    for(auto &child: curr_ptr->get_children()) {
        if(name == child->get_name()) {
            std::cout << "Такой элемент уже существует существует!" << std::endl;
            return true;
        }
    }

    return false;
}

void AppManager::change_mark() {
    std::cout << "Выберите элемент дисциплины(LB/CGT/CP/TEST/EXAM): ";
    std::string choice;
    std::getline(std::cin, choice);

    if((choice == "LB") || choice == "CGT") {
        int index;
        int mark;
        if(choice == "LB") {
            std::cout << "Введите номер ЛБ: ";
        } else {
            std::cout << "Введите номер РГЗ: ";
        }

        std::cin >> index;
        std::cout << "Введите оценку: ";
        std::cin >> mark;

        if(choice == "LB") {
            curr_ptr->change_mark_lab(index, mark);
        } else {
            curr_ptr->change_mark_cgt(index, mark);
        }
    } else {
        if(choice == "CP" || choice == "TEST" || choice == "EXAM") {
            int mark;
            std::cout << "Введите оценку: ";
            std::cin >> mark;

            if(choice == "CP") {
                curr_ptr->change_mark_cp(mark);
            }
            if(choice == "TEST") {
                curr_ptr->change_mark_test(mark);
            }
            if (choice == "EXAM") {
                curr_ptr->change_mark_exam(mark);
            }
        } else {
            std::cout << "Такого элемента дисциплины нет!" << std::endl;
        }
    }
}

bool AppManager::correct_input(int& input) {
    if (!(std::cin >> input)) {
        std::cout << "Ошибка ввода. Попробуйте снова.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;
    }
    std::cin.ignore(10000, '\n');
    return true;
}
bool AppManager::correct_input_yes_no() {
    std::string answer;

    while (true) {
        std::getline(std::cin, answer);

        if(answer == "Yes") {
            return true;
        }
        if (answer == "No") {
            return false;
        }

        std::cout << "Ошибка ввода. Попробуйте снова: ";
    }
}
void AppManager::correct_input_assess_sys(std::string& assess) {
    while (true) {
        std::getline(std::cin, assess);

        if(assess == "FivePoint" || assess == "TEST") {
            return;
        }

        std::cout << "Ошибка ввода. Попробуйте снова: ";
    }
}
size_t AppManager::correct_input_count() {
    size_t count;
    while (true) {
        if (std::cin >> count) {
            std::cin.ignore(10000, '\n');
            return count;
        }

        std::cout << "Ошибка ввода. Попробуйте снова: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

void AppManager::remove() {
    std::cout << "Введите название для удаления: ";
    std::string name;
    std::getline(std::cin, name);

    int choice;
    for(auto &child: curr_ptr->get_children()) {
        if(name == child->get_name()) {
            std::cout << "Вы уверены, что хотите удалить " << name << "? yes(1)/no(0): ";
            if(correct_input(choice) && choice == 1) {
                curr_ptr->remove(child);
            }

            return;
        }
    }

    std::cout << "Элемента с таким именем не найдено" << std::endl;
}

void AppManager::add_discs_of_group(std::shared_ptr<ComponentBase> st) {
    std::string name = st->get_parent()->get_name();
    name = shorten_group(name);

    if(name == "KB-23") {
        add_disc(st, DiscOfKB2Course());
    }
}

std::string AppManager::shorten_group(const std::string& group_name) {
    auto dash_pos = group_name.find('-');
    if (dash_pos == std::string::npos) {
        return group_name;
    }

    if (group_name.size() > dash_pos + 1) {
        return group_name.substr(0, group_name.size() - 1);
    }

    return group_name;
}
void AppManager::add_disc(std::shared_ptr<ComponentBase> st, std::vector<DisciplineConfig> discs) {
    for(auto con_disc: discs) {
        auto disc = std::make_shared<Discipline>(con_disc.name, con_disc);
        st->add(disc);
    }
}