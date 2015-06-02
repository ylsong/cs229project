//
//  genoset.h
//  cs229project
//
//  Created by Yuanlang Song on 5/31/15.
//  Copyright (c) 2015 Yuanlang Song. All rights reserved.
//

#ifndef __cs229project__genoset__
#define __cs229project__genoset__

#include <iostream>
#include <stdlib.h>
#include "genotype.h"
#include <vector>

class Genoset {
    vector<Genotype*> genos;
public:
    size_t get_genos_len();
    Genotype * get_genos_at(size_t i);
    void shuffle();
    void add_geno(string s);
    void print();
    void delete_genos();
};
#endif /* defined(__cs229project__genoset__) */
