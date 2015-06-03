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
#include <unordered_map>
#include <unordered_set>

/* Argument options */
bool file_flag = false;
char * filename = NULL;
bool print_detail_flag = false;
bool consensus_flag = false;
unsigned long consensus_times = 1;
bool stochastic_flag = false;
bool output_flag = false;
char * output_filename = NULL;
bool min_plus_one_flag = false;
ofstream output_stream;

unordered_map<string,Haplotype*> haplo_set;
vector<Genoset *> consensus_vector;
vector<Genoset *> selected_genosets;

void clark_algorithm(Haploset * hs, Genoset * gs) {
    for (size_t i = 0; i < gs->get_genos_len(); i ++) {
        Genotype * gt = gs->get_genos_at(i);
        if (gt->get_num_ambiguous_sites() == 0) {
            Haplotype * new_haplotype = new Haplotype(gt->get_geno());
            assert(new_haplotype != NULL);
            new_haplotype = hs->haploset_pushback(new_haplotype);
            gt->set_resolved(true);
            gt->set_resolved_by(new_haplotype, new_haplotype);
            gs->incre_resolved_genotypes();
            //cout << gt->get_geno() << " is generating " << gt->get_geno() << endl;
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
            gs->incre_resolved_genotypes();
            //cout << gt->get_geno() << " is generating " << new_haplo1 << " and " << new_haplo2 << endl;
        }
    }
    if (stochastic_flag) gs->shuffle();
    if (stochastic_flag) hs->shuffle();
    bool changed = true;
    while (changed) {
        changed = false;
        for (size_t i = 0; i < gs->get_genos_len(); i ++) {
            Genotype * gt = gs->get_genos_at(i);
            if (gt->get_resolved()) continue;
            for (size_t j = 0; j < hs->get_haplos_len(); j ++) {
                Haplotype * ht = hs->get_haplos_at(j);
                if (gt->is_same_unambiguous_sites(ht)) {
                    gt->resolve(ht, hs, gs);
                    changed = true;
                    break;
                }
            }
        }
        if (stochastic_flag) gs->shuffle();
        if (stochastic_flag) hs->shuffle();
    }
    gs->set_distinct_haplotypes(hs->get_haplos_len());
    gs->sort_genos();
    if (!consensus_flag) {
        hs->print();
        cout << "Total " << gs->get_resolved_genotypes() << " have been resolved" << endl;
        if (print_detail_flag) gs->print();
    }
    
}

void read_input_cin(Genoset * gs) {
    unsigned int num_genotypes;
    string s;
    cout << ">>>Please input genotypes number followed by genotypes" << endl;
    cout << ">>>";
    cin >> num_genotypes;
    while (num_genotypes -- > 0) {
        cout << ">>>";
        cin >> s;
        gs->add_geno(s);
    }
}

void read_input_file(Genoset * gs) {
    ifstream is(filename);
    string line = "";
    getline(is, line);
    unsigned long num_genotypes = stoul(line.c_str());
    while (num_genotypes -- > 0) {
        getline(is, line);
        line.erase(remove(line.begin(), line.end(), ' '), line.end());
        if (line == "") {
            cerr << "Read File Error" << endl;
            abort();
        }
        gs->add_geno(line);
    }
    is.close();
}

void print_help() {
    cout << "Usages: ./hi [ -r filename] [-d] [-s] [-o filename] [-c times -p]" << endl;
    cout << "Supported options:" << endl;
    cout << "-r filename   : Read file instead of directly from cin" << endl;
    cout << "-d            : Print resolvation map information" << endl;
    cout << "-s            : Set program to stochasic to get different results" << endl;
    cout << "-o filename   : Output results to a file instead of cout" << endl;
    cout << "-c times      : Turn on consensus mode and specify how many times" << endl;
    cout << "-p            : Turn on max+1 mode for consensus method" << endl;
    cout << "-h            : Print help page" << endl;
}

bool getoptions(int argc, char * const argv[]) {
    int c;
    while ((c = getopt(argc, argv, "hr:dso:c:p")) != -1) {
        if (optarg != NULL && optarg[0] == '-') c = '?';
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
                consensus_times = atoi(optarg);
                stochastic_flag = true;
                break;
            case 'p':
                if (!consensus_flag) {
                    fprintf(stderr, "Option -p should be used together with -c\n");
                    print_help();
                    return false;
                } else {
                    min_plus_one_flag = true;
                    break;
                }
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
                print_help();
                return false;
        }
    }
    return true;
}

void consensus_method() {
    // Find smallest set of haplotypes
    unsigned long mini = -1;
    unsigned long mini2 = -1;
    unordered_set<string> us;
    for (Genoset * gs : consensus_vector) mini = min(mini, gs->get_distinct_haplotypes());
    if (min_plus_one_flag) {
        for (Genoset * gs : consensus_vector) {
            if (gs->get_distinct_haplotypes() != mini) mini2 = min(mini2, gs->get_distinct_haplotypes());
        }
    }
    if (mini2 == -1) mini2 = mini;
    for (Genoset * gs : consensus_vector) {
        if (gs->get_distinct_haplotypes() == mini
            || gs->get_distinct_haplotypes() == mini2)
            selected_genosets.push_back(gs);
    }
    unsigned long max_imply_num = 0;
    Haplotype * max_haplotype1 = NULL;
    Haplotype * max_haplotype2 = NULL;
    string output_string = "";
    for (size_t i = 0; i < selected_genosets[0]->get_genos_len(); i ++) {
        max_imply_num = 0;
        max_haplotype1 = NULL;
        max_haplotype2 = NULL;
        Genotype * gt = selected_genosets[0]->get_genos_at(i);
        unordered_map<Haplotype*, unsigned int> haplotype_map;
        for (size_t j = 0; j < selected_genosets.size(); j ++) {
            Genotype * gt = selected_genosets[j]->get_genos_at(i);
            if (gt->get_resolved_by1() == NULL) continue;
            if (haplotype_map.find(gt->get_resolved_by1()) == haplotype_map.end()) {
                haplotype_map[gt->get_resolved_by1()] = 1;
                haplotype_map[gt->get_resolved_by2()] = 1;
            } else {
                haplotype_map[gt->get_resolved_by1()] ++;
                haplotype_map[gt->get_resolved_by2()] ++;
            }
            if (max_imply_num < haplotype_map[gt->get_resolved_by2()]) {
                max_haplotype1 = gt->get_resolved_by1();
                max_haplotype2 = gt->get_resolved_by2();
            }
        }
        if (max_haplotype1 != NULL) {
            us.insert(max_haplotype1->get_haplo());
            us.insert(max_haplotype2->get_haplo());
        }
        if (max_haplotype1 == NULL) {
            output_string += gt->get_geno() + "  :  NOT RESOLVED\n";
        } else {
            output_string += gt->get_geno() + "  :  " + max_haplotype1->get_haplo()
            + "+" + max_haplotype2->get_haplo() + "\n";
        }
    }
    if (!output_flag) {
        cout << "Resolvation Results:" << endl;
        cout << "Total " << us.size() << " haplotypes generated" << endl;
        for (string s : us) {
            cout << s << endl;
        }
        cout << "Total " << selected_genosets[0]->get_resolved_genotypes()
             << " have been resolved" << endl;
    }
    else {
        output_stream << "Resolvation Results:" << endl;
        output_stream << "Total " << us.size() << " haplotypes generated" << endl;
        for (string s : us) {
            output_stream << s << endl;
        }
        output_stream << "Total " << selected_genosets[0]->get_resolved_genotypes()
        << " have been resolved" << endl;
    }
    if (print_detail_flag) {
        if (!output_flag) {
            cout << "Resolvation Map:" << endl;
            cout << output_string;
        }
        else {
            output_stream << "Resolvation Map:" << endl;
            output_stream << output_string;
        }
    }
}

int main(int argc, char * const argv[]) {
    //ifstream arq(getenv("INPUT"));
    //cin.rdbuf(arq.rdbuf());
    bool if_run = getoptions(argc, argv);
    if (!if_run) return 0;
    Genoset * gs = NULL;
    Haploset * hs = NULL;
    srand((unsigned int)time(NULL));
    for (int i = 0; i < consensus_times; i ++) {
        gs = new Genoset;
        hs = new Haploset;
        if (file_flag) read_input_file(gs);
        else read_input_cin(gs);
        clark_algorithm(hs, gs);
        consensus_vector.push_back(gs);
        delete hs;
    }
    if (consensus_flag) consensus_method();
    // Delete all genotypes and genosets
    for (Genoset * gs : consensus_vector) {
        gs->delete_genos();
        delete gs;
    }
    // Delete all haplotypes
    for (auto kv : haplo_set) {
        delete kv.second;
    }
    return 0;
}
