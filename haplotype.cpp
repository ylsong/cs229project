//
//  haplotype.cpp
//  cs229project
//
//  Created by Yuanlang Song on 5/31/15.
//  Copyright (c) 2015 Yuanlang Song. All rights reserved.
//

#include "haplotype.h"

Haplotype::Haplotype(string s) {
    haplo = s;
}

size_t Haplotype::get_haplo_len() {
    return haplo.size();
}

char Haplotype::get_haplo_at(size_t i) {
    return haplo[i];
}

string Haplotype::get_haplo() {
    return haplo;
}
