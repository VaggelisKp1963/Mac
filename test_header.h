#include <iostream>
#include <vector>
#include <string>

using namespace std;

int get_first_line(string line);


/* DOMS */

void get_DOMAIN_SIZES(vector<int>& DOMAIN_SIZES, string line);

void set_DOMAINS(vector<vector<int>>& DOMAINS, string line);

void read_doms_file(string dom_file, int& DOMAINS_NUM, vector<int>& DOMAIN_SIZES, vector<vector<int>>& DOMAINS);



/* VARS */

int get_domain_id(string line);

void set_VARS_DOMAINS(vector<vector<int>>& DOMAINS, vector<vector<int>>& VARS_DOMAINS, int domain_id);

void read_vars_file(string var_file, int& VARS_NUM, vector<vector<int>> DOMAINS, vector<vector<int>>& VALUES);

void set_X(vector<int>& X, int VARS_NUM);

void set_D(vector<vector<int>>& D, vector<vector<int>> VALUES);


/* CTRS */

void get_CTR(string line, vector<vector<int>>& CTRS);

void read_ctr_file(string ctr_file, int& CTRS_NUM, vector<vector<int>>& CTRS);

void init_weights(map<array<int, 2>, int>& weights, vector<vector<int>> C);


/*  AC-3  */

vector<int> neigh(int x_i, vector<vector<int>> C);

bool check(int x_j, int value_j, int x_i, int value_i, vector<vector<int>> C);

bool supported(int x_j, int value_j, int x_i, vector<vector<int>> D, vector<vector<int>> VALUES, vector<vector<int>> C);

bool revise(int x_j, int x_i, vector<vector<int>>& D, vector<vector<int>> VALUES, vector<vector<int>> C, map<array<int, 2>, int>& weights);

bool is_null(vector<int> domain);

bool AC(vector<int> X, vector<vector<int>> C, vector<vector<int>>& D, vector<vector<int>> VALUES, map<array<int, 2>, int>& weights);