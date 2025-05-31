#include "DataBase.h"

std::unique_ptr<Database> Database::instance = nullptr;

Database& Database::get_instance() {
    if (!instance) {
        instance = std::unique_ptr<Database>(new Database());
    }
    return *instance;
}

void Database::set_data(const std::shared_ptr<ComponentBase> new_data) {
    db_ptr = new_data;
}

void Database::save(const std::string& path) {
    db = db_ptr->to_json();
    std::ofstream file(path);
    file << db.dump(4);
}

void Database::load(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Файл не найден: " + path);
    }

    file.seekg(0, std::ios::end);
    if (file.tellg() == 0) {
        throw std::runtime_error("Файл пустой: " + path);
    }
    file.seekg(0, std::ios::beg);

    file >> db;
    db_ptr = University::from_json(db);
}

std::shared_ptr<ComponentBase> Database::data() {
    return db_ptr;
}