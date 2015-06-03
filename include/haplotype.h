//
//  haplotype.h
//  cs229project
//
//  Created by Yuanlang Song on 5/31/15.
//  Copyright (c) 2015 Yuanlang Song. All rights reserved.
//

#ifndef __cs229project__haplotype__
#define __cs229project__haplotype__

#include <stdio.h>
#include <string>

using namespace std;

class Haplotype {
    string haplo;
public:
    Haplotype(string s);
    string get_haplo();
    char get_haplo_at(size_t i);
    size_t get_haplo_len();
};
#endif /* defined(__cs229project__haplotype__) */
