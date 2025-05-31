#ifndef GROUP_H
#define GROUP_H

#include "../ComponentBase/ComponentBase.h"

class Group: public ComponentBase {
public:
    explicit Group(const std::string& name);

    void print(int indent) const override;

    json to_json() const override;
    static std::shared_ptr<Group> from_json(const json& j);
};

#endif //GROUP_H
