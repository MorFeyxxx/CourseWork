#ifndef UNIVERSITY_H
#define UNIVERSITY_H

#include "../ComponentBase/ComponentBase.h"

class University: public ComponentBase {
public:
    explicit University(const std::string& name);

    void print(int indent) const override;

    json to_json() const override;
    static std::shared_ptr<University> from_json(const json& j);
};

#endif //UNIVERSITY_H
