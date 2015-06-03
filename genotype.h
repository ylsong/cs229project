//
//  genotype.h
//  cs229project
//
//  Created by Yuanlang Song on 5/31/15.
//  Copyright (c) 2015 Yuanlang Song. All rights reserved.
//

#ifndef __cs229project__genotype__
#define __cs229project__genotype__

#ifndef genotype_h
#define genotype_h

#include <iostream>
#include <string>
#include "haplotype.h"
#include "haploset.h"
#include "genoset.h"

using namespace std;

class Genoset;

class Genotype {
    string geno;
    unsigned int num_ambiguous_sites;
    bool resolved;
    Haplotype * resolved_by[2];
public:
    Genotype(string s);
    string get_geno();
    char get_geno_at(size_t i);
    size_t get_geno_len();
    unsigned int get_num_ambiguous_sites();
    bool get_resolved();
    void set_resolved(bool b);
    bool is_same_unambiguous_sites(Haplotype* ht);
    void resolve(Haplotype * ht, Haploset * hs, Genoset * gs);
    void set_resolved_by(Haplotype * ht1, Haplotype * ht2);
    void print();
};

#endif
#endif /* defined(__cs229project__genotype__) */
