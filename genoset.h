//
//  genoset.h
//  cs229project
//
//  Created by Yuanlang Song on 5/31/15.
//  Copyright (c) 2015 Yuanlang Song. All rights reserved.
//

#ifndef __cs229project__genoset__
#define __cs229project__genoset__

#ifndef genoset_h
#define genoset_h

#include <iostream>
#include <stdlib.h>
#include "genotype.h"
#include <vector>

class Genotype;

class Genoset {
    vector<Genotype*> genos;
    unsigned int resolved_genotypes;
    unsigned long distinct_haplotypes;
public:
    Genoset();
    size_t get_genos_len();
    Genotype * get_genos_at(size_t i);
    void incre_resolved_genotypes();
    unsigned int get_resolved_genotypes();
    void set_distinct_haplotypes(unsigned long);
    unsigned long get_distinct_haplotypes();
    void shuffle();
    void add_geno(string s);
    void print();
    void delete_genos();
    void sort_genos();
};

#endif
#endif /* defined(__cs229project__genoset__) */
