//
//  main.cpp
//  cs229project
//
//  Created by Yuanlang Song on 5/31/15.
//  Copyright (c) 2015 Yuanlang Song. All rights reserved.
//

#include <iostream>
#include "haploset.h"
#include "haplotype.h"
#include "genotype.h"
#include "genoset.h"

void clark_algorithm(Haploset * hs, Genoset * gs) {
    for (size_t i = 0; i < gs->get_genos_len(); i ++) {
        Genotype * gt = gs->get_genos_at(i);
        if (gt->get_num_ambiguous_sites() == 0) {
            Haplotype * new_haplotype = new Haplotype(gt->get_geno());
            hs->haploset_pushback(new_haplotype);
        } else if (gt->get_num_ambiguous_sites() == 1) {
            string new_haplo1 = gt->get_geno();
            string new_haplo2 = gt->get_geno();
            for (size_t j = 0; j < gt->get_geno_len(); j ++) {
                if (gt->get_geno_at(j) == '2') {
                    new_haplo1[j] = '0';
                    new_haplo2[j] = '1';
                    break;
                }
            }
            Haplotype * new_haplotype1 = new Haplotype(new_haplo1);
            Haplotype * new_haplotype2 = new Haplotype(new_haplo2);
            hs->haploset_pushback(new_haplotype1);
            hs->haploset_pushback(new_haplotype2);
        }
    }
    gs->shuffle();
    bool changed = true;
    while (changed) {
        changed = false;
        for (size_t i = 0; i < gs->get_genos_len(); i ++) {
            Genotype * gt = gs->get_genos_at(i);
            if (gt->get_resolved()) continue;
            for (size_t j = 0; j < hs->get_haplos_len(); j ++) {
                Haplotype * ht = hs->get_haplos_at(j);
                if (gt->is_same_unambiguous_sites(ht)) {
                    gt->resolve(ht, hs);
                    changed = true;
                    break;
                }
            }
        }
        //gs->shuffle();
    }
    hs->print();
    gs->print();
}

void read_input(Genoset * gs) {
    unsigned int num_genotypes;
    string s;
    cin >> num_genotypes;
    while (num_genotypes -- > 0) {
        cin >> s;
        gs->add_geno(s);
    }
}

int main(int argc, const char * argv[]) {
    Genoset * gs = new Genoset;
    Haploset * hs = new Haploset;
    read_input(gs);
    clark_algorithm(hs, gs);
    return 0;
}
