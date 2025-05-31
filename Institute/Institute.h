#ifndef INSTITUTE_H
#define INSTITUTE_H

#include "../ComponentBase/ComponentBase.h"

class Institute: public ComponentBase {
public:
    explicit Institute(const std::string& name);

    void print(int indent) const override;

    json to_json() const override;
    static std::shared_ptr<Institute> from_json(const json& j);
};

#endif //INSTITUTE_H
