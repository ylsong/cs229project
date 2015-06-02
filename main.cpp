//
//  main.cpp
//  cs229project
//
//  Created by Yuanlang Song on 5/31/15.
//  Copyright (c) 2015 Yuanlang Song. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "haploset.h"
#include "haplotype.h"
#include "genotype.h"
#include "genoset.h"
#include <assert.h>
#include <getopt.h>

/* Argument options */
bool file_flag = false;
char * filename = NULL;
bool print_detail_flag = false;
bool consensus_flag = false;
unsigned long concensus_times = 0;
bool stochastic_flag = false;
bool output_flag = false;
char * output_filename = NULL;
ofstream output_stream;


void clark_algorithm(Haploset * hs, Genoset * gs) {
    for (size_t i = 0; i < gs->get_genos_len(); i ++) {
        Genotype * gt = gs->get_genos_at(i);
        if (gt->get_num_ambiguous_sites() == 0) {
            Haplotype * new_haplotype = new Haplotype(gt->get_geno());
            assert(new_haplotype != NULL);
            new_haplotype = hs->haploset_pushback(new_haplotype);
            gt->set_resolved(true);
            gt->set_resolved_by(new_haplotype, new_haplotype);
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
            new_haplotype1 = hs->haploset_pushback(new_haplotype1);
            new_haplotype2 = hs->haploset_pushback(new_haplotype2);
            gt->set_resolved(true);
            gt->set_resolved_by(new_haplotype1, new_haplotype2);
        }
    }
    if (stochastic_flag) gs->shuffle();
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
        if (stochastic_flag) gs->shuffle();
        if (stochastic_flag) hs->shuffle();
    }
    hs->print();
    if (print_detail_flag) gs->print();
}

void read_input_cin(Genoset * gs) {
    unsigned int num_genotypes;
    string s;
    cin >> num_genotypes;
    while (num_genotypes -- > 0) {
        cin >> s;
        gs->add_geno(s);
    }
}

void read_input_file(Genoset * gs) {
    ifstream is(filename, 'r');
    string line = "";
    getline(is, line);
    unsigned long num_genotypes = stoul(line.c_str());
    while (num_genotypes -- > 0) {
        getline(is, line);
        if (line == "") {
            cerr << "Read File Error" << endl;
            abort();
        }
        gs->add_geno(line);
    }
    is.close();
}

void print_help() {
    cout << "Usages: ./hi [ -r filename] [-d] [-s] [-o filename] [-c times]" << endl;
    cout << "Supported options:" << endl;
    cout << "-r filename   : Read file instead of directly from cin" << endl;
    cout << "-d            : Print resolvation map information" << endl;
    cout << "-s            : Set program to stochasic to get different results" << endl;
    cout << "-o filename   : Output results to a file instead of cout" << endl;
    cout << "-c times      : Turn on consensus mode and specify how many times" << endl;
    cout << "-h            : Print help page" << endl;
}

bool getoptions(int argc, char * const argv[]) {
    int c;
    while ((c = getopt(argc, argv, "hr:dso:c:")) != -1) {
        switch(c) {
            case 'h':
                print_help();
                return false;
            case 'd':
                print_detail_flag = true;
                break;
            case 's':
                stochastic_flag = true;
                break;
            case 'r':
                file_flag = true;
                filename = optarg;
                break;
            case 'o':
                output_flag = true;
                output_filename = optarg;
                output_stream.open(output_filename,'r');
                break;
            case 'c':
                consensus_flag = true;
                concensus_times = atoi(optarg);
                break;
            case '?':
                if (optopt == 'o' || optopt == 'c' || optopt == 'r') {
                    fprintf(stderr, "Option -%c requires an argument.\n", optopt);
                } else if (isprint(optopt)) {
                    fprintf(stderr, "Unknown option -%c.\n", optopt);
                } else {
                    fprintf(stderr, "Unknown option character \\x%x.\n", optopt);
                }
                print_help();
                return false;
            default:
                abort();
        }
    }
    return true;
}

int main(int argc, char * const argv[]) {
    //ifstream arq(getenv("INPUT"));
    //cin.rdbuf(arq.rdbuf());
    bool if_run = getoptions(argc, argv);
    if (!if_run) return 0;
    Genoset * gs = new Genoset;
    Haploset * hs = new Haploset;
    srand((unsigned int)time(NULL));
    if (file_flag) read_input_file(gs);
    else read_input_cin(gs);
    clark_algorithm(hs, gs);
    return 0;
}
