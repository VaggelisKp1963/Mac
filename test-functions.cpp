#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <queue>

using namespace std;


/*
    Παίρνει την πρώτη γραμμή κάθε αρχείου (πλήθος domain, πλήθος μεταβλητών,
    πλήθος περιορισμών από κάθε αρχείο αντίστοιχα)
*/
int get_first_line(string line) {
    string domains_num;

    for (char c : line) {
        domains_num += c;
        if (c == ' ' || c == '\n') break;
    }

    return stoi(domains_num);
}


/*-------------------------------------- ΣΥΝΑΡΤΗΣΕΙΣ ΑΡΧΕΙΩΝ dom --------------------------------------*/

/*
    Εξαγωγή του μεγέθους ενός domain και αποθήκευση σε vector.
    (2ος αριθμός στη γραμμή)
*/
void get_DOMAIN_SIZES(vector<int>& DOMAIN_SIZES, string line) {
    string domain_size;
    int i = 0;

    for (i = 0; i < size(line); i++) {
        if (line[i] == ' ') break;
    }

    for (int j = i + 1; j < size(line); j++) {
        if (line[j] == ' ') break;
        domain_size += line[j];
    }

    // cout << domain_size << endl;

    DOMAIN_SIZES.push_back(stoi(domain_size));
}


/*
    Εξαγωγή των αριθμών ενός domain μιας σειράς και αποθήκευση σε vector (domain).
    Προσθήκη του domain στο vector DOMAINS.

*/
void set_DOMAINS(vector<vector<int>>& DOMAINS, string line) {
    vector<int> domain;
    int COUNT_SPACES = 0, i = 0;
    string num;

    while (COUNT_SPACES != 2) {
        if (line[i] == ' ') {
            COUNT_SPACES++;
            i++;
            continue;
        }
        // cout << line[i] << endl;
        i++;
    }

    for (int j = i; j < size(line); j++) {
        if (line[j] == ' ') {
            int value = stoi(num);
            domain.push_back(value);
            num = "";
            continue;
        }
        if (line[j] == '\n') break;
        num += line[j];

        if (j == size(line) - 1) {
            int value = stoi(num);
            domain.push_back(value);
        }
    }

    DOMAINS.push_back(domain);
}


void read_doms_file(string dom_file, int& DOMAINS_NUM, vector<int>& DOMAIN_SIZES, vector<vector<int>>& DOMAINS) {

    string line;
    int COUNT_LINES = 0;
    ifstream Read(dom_file);

    while (getline(Read, line)) {
        if (COUNT_LINES == 0) {
            DOMAINS_NUM = get_first_line(line);
            COUNT_LINES++;
            continue;
        }
        get_DOMAIN_SIZES(DOMAIN_SIZES, line);
        set_DOMAINS(DOMAINS, line);
    }

    Read.close();

}



/*-------------------------------------- ΣΥΝΑΡΤΗΣΕΙΣ ΑΡΧΕΙΩΝ var --------------------------------------*/

/*
    Βρίσκει ποιο domain αντιστοιχεί σε κάθε μεταβλητή.
*/
int get_domain_id(string line) {
    int COUNT_SPACES = 0;
    string num;
    int i = 0;

    while (COUNT_SPACES == 0) {
        if (line[i] == ' ') {
            i++;
            COUNT_SPACES++;
            continue;
        }
        i++;
    }

    for (int j = i; j <= size(line); j++) {
        // cout << line[j] << endl;
        if (line[j] == '\n') break;
        num += line[j];
    }
    // cout << num << endl;
    return stoi(num);

}


/*
    Αποθήκευση του domain κάθε μεταβλητής στο VARS_DOMAINS.
    vector VARS_DOMAINS: αποθηκεύει vectors με τα πεδία τιμών κάθε μεταβλητής
*/
void set_VARS_DOMAINS(vector<vector<int>>& DOMAINS, vector<vector<int>>& VALUES, int domain_id) {
    VALUES.push_back(DOMAINS[domain_id]);
}



void read_vars_file(string var_file, int& VARS_NUM, vector<vector<int>> DOMAINS, vector<vector<int>>& VALUES) {
    string line;
    int COUNT_LINES = 0;

    ifstream Read(var_file);
    while (getline(Read, line)) {
        // cout << line << endl;
        if (COUNT_LINES == 0) {
            VARS_NUM = get_first_line(line);
            COUNT_LINES++;
            continue;
        }
        int domain_id = get_domain_id(line);
        set_VARS_DOMAINS(DOMAINS, VALUES, domain_id);
    }

    Read.close();
}

void set_X(vector<int>& X, int VARS_NUM) {

    for (int i = 0; i < VARS_NUM; i++)
        X.push_back(i);
}

/*
    Αρχικοποίηση ενός vector ίδιων διαστάσεων με το VARS_DOMAINS.
    Όπου υπάρχει -1, σημαίνει ότι η αντίστοιχη τιμή ενός πεδίου τιμών
    μιας μεταβλητής είναι διαθέσιμη.
*/
void set_D(vector<vector<int>>& D, vector<vector<int>> VALUES) {

    for (vector<int> v : VALUES) {
        int vector_size = size(v);
        vector<int>values(vector_size, -1);
        D.push_back(values);
    }
}



/*-------------------------------------- ΣΥΝΑΡΤΗΣΕΙΣ ΑΡΧΕΙΩΝ ctr --------------------------------------*/

/*
    Εξαγωγή περιορισμού κάθε γραμμής και αποθήκευση σε vector ctr.
    0: =
    1: >
    Το ctr προστίθεται στο vector CTRS, όπου αποθηκεύονται όλοι οι
    περιορισμοί.
*/
void get_CTR(string line, vector<vector<int>>& CTRS) {

    string num;
    vector<int> ctr;
    int flag = 0;

    for (char c : line) {
        if (c == ' ') {
            if (flag != 0) {
                continue;
            }
            // cout << num << " ";
            int NUM = stoi(num);
            num = "";
            ctr.push_back(NUM);
            continue;
        }
        if (c == '=') {
            ctr.push_back(0);
            flag++;
            continue;
        }
        if (c == '>') {
            ctr.push_back(1);
            flag++;
            continue;
        }
        num += c;
        // cout << num << " ";
    }
    ctr.push_back(stoi(num));

    CTRS.push_back(ctr);

}


void read_ctr_file(string ctr_file, int& CTRS_NUM, vector<vector<int>>& CTRS) {

    string line;
    int COUNT_LINES = 0;

    ifstream Read(ctr_file);
    while (getline(Read, line)) {
        // cout << line << endl;
        if (COUNT_LINES == 0) {
            CTRS_NUM = get_first_line(line);
            COUNT_LINES++;
            continue;
        }
        get_CTR(line, CTRS);
    }

    Read.close();
}


void init_weights(map<array<int, 2>, int>& weights, vector<vector<int>> C) {
    for (vector<int> c : C) {
        weights.insert({ {c[0], c[1]}, 0 });
    }
}


/* ------------------------------  AC related ------------------------------ */

bool is_null(vector<int> domain) {
    int non_valid = 0;

    for (int val : domain)
        if (val != -1) non_valid++;

    if (non_valid == size(domain)) return true;

    return false;
}


vector<int> neigh(int x_i, vector<vector<int>> C) {
    vector<int> neighbours;
    for (vector<int> c : C) {
        if (c[0] == x_i) {
            neighbours.push_back(c[1]);
            // cout << c[1] << " ";
        }
    }
    return neighbours;
}


bool check(int x_j, int value_j, int x_i, int value_i, vector<vector<int>> C) {
    int constraint_type;
    for (vector<int> c : C) {
        if (c[0] == x_i && c[1] == x_j) {
            // printf("%d %d %d %d\n", c[0], c[1], c[2], c[3]);
            // cout << "value_j = " << value_j << " value_i = " << value_i << endl;
            constraint_type = c[2];
            if (constraint_type == 0) {
                // printf("%d %d %s %d\n", c[0], c[1], "==", c[3]);
                if (abs(value_i - value_j) == c[3]) {
                    // cout << "x_j = " << x_j << " x_i = " << x_i << endl;
                    // cout << "value_j = " << value_j << " value_i = " << value_i << endl;
                    return true;
                }
                else return false;
            }
            if (constraint_type == 1) {
                // printf("%d %d %s %d\n", c[0], c[1], ">", c[3]);
                if (abs(value_i - value_j) > c[3]) {
                    // cout << "x_j = " << x_j << " x_i = " << x_i << endl;
                    // cout << "value_j = " << value_j << " value_i = " << value_i << endl;
                    return true;
                }
                else return false;
            }
        }
    }
    return false;
}


bool supported(int x_j, int value_j, int x_i, vector<vector<int>> D, vector<vector<int>> VALUES, vector<vector<int>> C) {
    bool support = false;
    for (int i = 0; i < size(D[x_i]); i++) {
        int value_i = VALUES[x_i][i];
        // cout << "value_i = " << value_i << endl;
        if (check(x_j, value_j, x_i, value_i, C)) {
            support = true;
            return support;
        }

    }
    return support;
}


bool revise(int x_j, int x_i, vector<vector<int>>& D, vector<vector<int>> VALUES, vector<vector<int>> C, map<array<int, 2>, int>& weights) {
    bool revised = false;
    for (int i = 0; i < size(D[x_j]); i++) {
        int value_j = VALUES[x_j][i];
        // printf("x_j = %d, x_i = %d, value_j = %d\n", x_j, x_i, value_j);
        bool found = supported(x_j, value_j, x_i, D, VALUES, C);
        if (found == false) {
            revised = true;
            D[x_j][i] = -2;
        }
    }
    if (is_null(D[x_j])) weights.at({ x_j, x_i }) = weights.at({ x_j, x_i }) + 1;
    return revised;
}



bool AC(vector<int> X, vector<vector<int>> C, vector<vector<int>>& D, vector<vector<int>> VALUES, map<array<int, 2>, int>& weights) {
    queue<int> Q;
    bool updated = false;

    for (int x : X)
        Q.push(x);

    while (!Q.empty()) {
        int x_i = Q.front();
        // cout << "x_i = " << x_i << endl;
        Q.pop();

        vector<int> N = neigh(x_i, C);
        for (int x_j : N) {
            bool updated = revise(x_j, x_i, D, VALUES, C, weights);
            if (is_null(D[x_j])) {
                // cout << "false" << endl;
                return false;
            }
            if (updated) Q.push(x_j);
        }
    }

    return true;
}

