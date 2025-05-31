#ifndef DEPARTMENT_H
#define DEPARTMENT_H

#include "../ComponentBase/ComponentBase.h"

class Department: public ComponentBase {
public:
    explicit Department(const std::string& name);

    void print(int indent) const override;

    json to_json() const override;
    static std::shared_ptr<Department> from_json(const json& j);
};

#endif //DEPARTMENT_H
