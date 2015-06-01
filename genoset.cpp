//
//  genoset.cpp
//  cs229project
//
//  Created by Yuanlang Song on 5/31/15.
//  Copyright (c) 2015 Yuanlang Song. All rights reserved.
//

#include "genoset.h"
#define SF_TIME 10

size_t Genoset::get_genos_len() {
    return genos.size();
}

Genotype * Genoset::get_genos_at(size_t i) {
    return genos[i];
}

void Genoset::shuffle() {
    size_t len = genos.size();
    if (len < 2) return;
    for (unsigned int i = 0; i < SF_TIME; i ++) {
        unsigned int a = rand() % len;
        unsigned int b = rand() % len;
        swap(genos[a], genos[b]);
    }
}

void Genoset::add_geno(string s) {
    Genotype * new_genotype = new Genotype(s);
    genos.push_back(new_genotype);
}

void Genoset::print() {
    cout << "Resolvation Map:" << endl;
    for (Genotype * gt : genos) {
        gt->print();
    }
}