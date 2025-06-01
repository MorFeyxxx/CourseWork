#ifndef DISCOFKB_H
#define DISCOFKB_H

#include "DisciplinesOf2Course.h"

std::vector<DisciplineConfig> DiscOfKB2Course() {
    std::vector<DisciplineConfig> discs = {OOP(), IO(), IT(), FOPTSZI()};

    return discs;
}



#endif //DISCOFKB_H
