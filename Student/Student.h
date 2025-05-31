#ifndef STUDENT_H
#define STUDENT_H

#include "../ComponentBase/ComponentBase.h"

class Student: public ComponentBase {
public:
    explicit Student(const std::string& name);

    void print(int indent) const override;

    json to_json() const override;
    static std::shared_ptr<Student> from_json(const json& j);
};

#endif //STUDENT_H
