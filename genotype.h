//
//  genotype.h
//  cs229project
//
//  Created by Yuanlang Song on 5/31/15.
//  Copyright (c) 2015 Yuanlang Song. All rights reserved.
//

#ifndef __cs229project__genotype__
#define __cs229project__genotype__

#include <iostream>
#include <string>
#include "haplotype.h"
#include "haploset.h"

using namespace std;

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
    bool is_same_unambiguous_sites(Haplotype* ht);
    void resolve(Haplotype * ht, Haploset * hs);
    void print();
};
#endif /* defined(__cs229project__genotype__) */
