//
//  haploset.h
//  cs229project
//
//  Created by Yuanlang Song on 5/31/15.
//  Copyright (c) 2015 Yuanlang Song. All rights reserved.
//

#ifndef __cs229project__haploset__
#define __cs229project__haploset__

#include <iostream>
#include "haplotype.h"
#include <unordered_map>
#include <fstream>
#include <vector>

#define SF_TIME 2000
using namespace std;

extern bool output_flag;
extern ofstream output_stream;

class Haploset {
    unordered_map<string,Haplotype*> haplo_set;
    vector<Haplotype*> haplos;
public:
    Haplotype* haploset_pushback(Haplotype * ht);
    size_t get_haplos_len();
    Haplotype * get_haplos_at(size_t i);
    void print();
    void shuffle();
};
#endif /* defined(__cs229project__haploset__) */
