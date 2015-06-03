//
//  genotype.cpp
//  cs229project
//
//  Created by Yuanlang Song on 5/31/15.
//  Copyright (c) 2015 Yuanlang Song. All rights reserved.
//

#include "genotype.h"



Genotype::Genotype(string s) {
    geno = s;
    num_ambiguous_sites = 0;
    for (char c : s) {
        if (c == '2') num_ambiguous_sites++;
    }
    resolved = false;
    resolved_by[0] = NULL;
    resolved_by[1] = NULL;
}

string Genotype::get_geno() {
    return geno;
}

char Genotype::get_geno_at(size_t i) {
    return geno[i];
}

bool Genotype::get_resolved() {
    return resolved;
}

unsigned int Genotype::get_num_ambiguous_sites() {
    return num_ambiguous_sites;
}

size_t Genotype::get_geno_len() {
    return geno.size();
}

bool Genotype::is_same_unambiguous_sites(Haplotype * ht) {
    for (size_t i = 0; i < geno.size(); i ++) {
        if (geno[i] == '2') continue;
        else {
            if (geno[i] != ht->get_haplo_at(i)) return false;
        }
    }
    return true;
}

void Genotype::resolve(Haplotype * ht, Haploset * hs, Genoset * gs) {
    string new_haplo = geno;
    for (size_t i = 0; i < geno.size(); i ++) {
        if (geno[i] == '2') {
            new_haplo[i] = ht->get_haplo_at(i) == '1' ? '0' : '1';
        }
    }
    Haplotype * new_haplotype = new Haplotype(new_haplo);
    resolved_by[0] = hs->haploset_pushback(new_haplotype);
    resolved_by[1] = ht;
    resolved = true;
    gs->incre_resolved_genotypes();
    //cout << geno << " is resolved by " <<ht->get_haplo() << " and generating " << new_haplo << endl;
}

void Genotype::print() {
    if (!output_flag) {
        if (resolved_by[0] == NULL) {
            cout << geno << "  :  NOT RESOLVED" << endl;
        } else {
            cout << geno << "  :  " << resolved_by[0]->get_haplo()
            << "+" << resolved_by[1]->get_haplo() << endl;
        }
    } else {
        if (resolved_by[0] == NULL) {
            output_stream << geno << "  :  NOT RESOLVED" << endl;
        } else {
            output_stream << geno << "  :  " << resolved_by[0]->get_haplo()
            << "+" << resolved_by[1]->get_haplo() << endl;
        }
    }
    
    
}

void Genotype::set_resolved_by(Haplotype * ht1, Haplotype * ht2) {
    resolved_by[0] = ht1;
    resolved_by[1] = ht2;
}

void Genotype::set_resolved(bool b) {
    resolved = b;
}

