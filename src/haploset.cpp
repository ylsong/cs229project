//
//  haploset.cpp
//  cs229project
//
//  Created by Yuanlang Song on 5/31/15.
//  Copyright (c) 2015 Yuanlang Song. All rights reserved.
//

#include "haploset.h"
#include <assert.h>

Haplotype* Haploset::haploset_pushback(Haplotype * ht) {
    if (haplo_set.count(ht->get_haplo()) != 0) {
        Haplotype * res = haplo_set[ht->get_haplo()];
        assert(res != NULL);
        delete ht;
        if (us.find(res) == us.end()) {
            us.insert(res);
            haplos.push_back(res);
        }
        return res;
    } else {
        haplo_set.insert(make_pair(ht->get_haplo(), ht));
        if (us.find(ht) == us.end()) {
            us.insert(ht);
            haplos.push_back(ht);
        }
        return ht;
    }
}

Haplotype* Haploset::get_haplos_at(size_t i) {
    return haplos[i];
}

size_t Haploset::get_haplos_len() {
    return haplos.size();
}

void Haploset::print() {
    if (!output_flag) {
        cout << "Resolvation Results:" << endl;
        cout << "Total " << haplos.size() << " haplotypes generated" << endl;
        for (Haplotype* ht : haplos) {
            cout << ht->get_haplo() << endl;
        }
    }
    else {
        output_stream << "Resolvation Results:" << endl;
        output_stream << "Total " << haplos.size() << " haplotypes generated" << endl;
        for (Haplotype* ht : haplos) {
            output_stream << ht->get_haplo() << endl;
        }
    }
}

void Haploset::shuffle() {
    size_t len = haplos.size();
    if (len < 2) return;
    for (unsigned int i = 0; i < SF_TIME; i ++) {
        unsigned int a = rand() % len;
        unsigned int b = rand() % len;
        swap(haplos[a], haplos[b]);
    }
    //cout << "shuffled" << endl;
}

void Haploset::delete_haplos() {
    for (Haplotype * ht : haplos) delete ht;
}