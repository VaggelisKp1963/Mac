#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include "file-func.h"

using namespace std;

int main() {


    int DOMAINS_NUM;
    vector<int> DOMAIN_SIZES;
    vector<vector<int>> DOMAINS;
    read_doms_file("dom2-f25.txt", DOMAINS_NUM, DOMAIN_SIZES, DOMAINS);

    /* Εκτύπωση vector πεδίων τιμών */
    // for(vector<int> Domain:DOMAINS){
    //     for(int value: Domain){
    //         cout << value << " ";
    //     }
    //     cout << endl;
    // }

    /* Εκτύπωση vector μεγεθών πεδίου τιμών */
    // for(int size:DOMAIN_SIZES){
    //     cout << size << " ";
    // }
    // cout << endl;


    int VARS_NUM;
    vector<vector<int>> VALUES;
    vector<vector<int>> D;
    read_vars_file("var2-f25.txt", VARS_NUM, DOMAINS, VALUES);
    vector<int> X;
    set_X(X, VARS_NUM);
    set_D(D, VALUES);


    /* Εκτύπωση πεδίων τιμών όλων των μεταβλητών */
    // for(vector<int> VAR_DOMAIN:VALUES){
    //     for(int value: VAR_DOMAIN){
    //         cout << value << " ";
    //     }
    //     cout << endl;
    // }

    // for(vector<int> VAR_DOMAIN:D){
    //     for(int value: VAR_DOMAIN){
    //         cout << value << " ";
    //     }
    //     cout << endl;
    // }


    int CTRS_NUM;
    map<array<int, 2>, int> weights;
    map<array<int, 2>, int> ::iterator it = weights.begin();
    vector<vector<int>> CTRS;
    read_ctr_file("ctr2-f25.txt", CTRS_NUM, CTRS);
    init_weights(weights, CTRS);

    /* Εκτύπωση vector περιορισμών */
    // for(vector<int> ctr:CTRS){
    //     for(int c:ctr){
    //         cout << c << " ";
    //     }
    //     cout << endl;
    // } 


    // while(it!=weights.end()){
    //     cout << "Key[0] -> " << (it->first)[0] <<" Key[1] -> " << (it->first)[1] << " value -> " << (it->second)<<endl;
    //     it++;
    // }

    AC(X, CTRS, D, VALUES, weights);



    for (vector<int> VAR_DOMAIN : D) {
        for (int value : VAR_DOMAIN) {
            cout << value << " ";
        }
        cout << endl;
    }


}

