//
//  haploset.cpp
//  cs229project
//
//  Created by Yuanlang Song on 5/31/15.
//  Copyright (c) 2015 Yuanlang Song. All rights reserved.
//

#include "haploset.h"

Haplotype* Haploset::haploset_pushback(Haplotype * ht) {
    if (haplo_set.find(ht->get_haplo()) != haplo_set.end()) {
        delete ht;
        return haplo_set[ht->get_haplo()];
    } else {
        haplo_set.insert(make_pair(ht->get_haplo(), ht));
        haplos.push_back(ht);
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
    cout << "Resolvation Results:" << endl;
    for (Haplotype* ht : haplos) {
        cout << ht->get_haplo() << endl;
    }
}