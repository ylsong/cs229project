//
//  genoset.cpp
//  cs229project
//
//  Created by Yuanlang Song on 5/31/15.
//  Copyright (c) 2015 Yuanlang Song. All rights reserved.
//

#include "genoset.h"

// sort genotypes according to index
bool genoset_sort(Genotype * a, Genotype * b) {
    return a->get_index() < b->get_index();
}

Genoset::Genoset() {
    resolved_genotypes = 0;
    distinct_haplotypes = 0;
}

unsigned int Genoset::get_resolved_genotypes() {
    return resolved_genotypes;
}

void Genoset::incre_resolved_genotypes() {
    resolved_genotypes ++;
}

void Genoset::set_distinct_haplotypes(unsigned long ui) {
    distinct_haplotypes = ui;
}

unsigned long Genoset::get_distinct_haplotypes() {
    return distinct_haplotypes;
}

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
    Genotype * new_genotype = new Genotype(s, genos.size());
    genos.push_back(new_genotype);
}

void Genoset::print() {
    cout << "Resolvation Map:" << endl;
    for (Genotype * gt : genos) {
        gt->print();
    }
}

void Genoset::delete_genos() {
    for (Genotype * gt : genos) delete gt;
}

void Genoset::sort_genos() {
    sort(genos.begin(), genos.end(), genoset_sort);
}