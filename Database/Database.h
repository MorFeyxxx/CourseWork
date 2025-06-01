#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <fstream>
#include <memory>
#include "../json.hpp"
#include "../University/University.h"

using json = nlohmann::ordered_json;

class Database {
    json db;
    std::shared_ptr<University> db_ptr;
    static std::unique_ptr<Database> instance;

    Database() = default;

public:
    Database(const Database&) = delete;
    Database& operator=(const Database&) = delete;

    static Database& get_instance();

    void set_data(const std::shared_ptr<University> new_data);

    void save(const std::string& path);
    void load(const std::string& path);

    std::shared_ptr<ComponentBase> data();
};

#endif //DATABASE_H
