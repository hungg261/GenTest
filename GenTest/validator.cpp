#include <bits/stdc++.h>
#include "config/lib.h"
using namespace std;
using namespace RandomGen;
using namespace File;

#define int long long

bool input_validator(int test){
    ifstream reader("baitap.inp");
    string a, b;
    if(!(reader >> a >> b)) return false;

    for(char digit: a) if(!('0' <= digit && digit <= '9')) return false;
    for(char digit: b) if(!('0' <= digit && digit <= '9')) return false;

    if(0 < test && test <= 50){
        if(!(a.size() <= 3 && b.size() <= 3 && 1 <= stoi(a) && stoi(a) <= 100 && 1 <= stoi(b) && stoi(b) <= 100)) return false;
    }
    else if(50 < test && test <= 75){
        if(!(a.size() <= 10 && b.size() <= 10 && 1 <= stoll(a) && stoll(a) <= (int)1e9 && 1 <= stoll(b) && stoll(b) <= (int)1e9)) return false;
    }
    else if(75 < test && test <= 100){
        if(!(a.size() <= 501 && b.size() <= 501)) return false;
    }
    else return false;

    return true;
}

bool output_validator(int test){
    ifstream reader("baitap.out");
    string num;

    if(!(reader >> num)) return false;

    for(char digit: num){
        if(!('0' <= digit && digit <= '9')) return false;
    }

    if(0 < test && test <= 50){
        if(!(num.size() <= 5 && 1 * 1 <= stoi(num) && stoi(num) <= 100 * 100)) return false;
    }
    else if(50 < test && test <= 75){
        if(!(num.size() <= 19 && 1 * 1 <= stoll(num) && stoll(num) <= 1LL * (int)1e9 * (int)1e9)) return false;
    }
    else if(75 < test && test <= 100){
        if(!(num.size() <= 1001)) return false;
    }
    else return false;

    return true;
}

signed main(int32_t argc, char* argv[]){
    int test = -1;
    bool validate_input = true, validate_output = false;

    int cur_args = 1;
    while (cur_args < argc){
        string arg = argv[cur_args];

        if (arg == "-test" && cur_args + 1 < argc){
            test = stoi(argv[++cur_args]);
        }
        else if (arg == "-type" && cur_args + 1 < argc){
            string validate_type = argv[++cur_args];
            if (validate_type == "input"){
                validate_input = true;
                validate_output = false;
            } else if (validate_type == "output"){
                validate_input = false;
                validate_output = true;
            } else{
                validate_input = validate_output = true;
            }
        }
        ++cur_args;
    }

    cout << "\n-------- Validating --------\n";

    if (validate_input && !input_validator(test)){
        cerr << "Test input #" << test << " failed to validate.\n";
        return -69;
    }
    if (validate_output && !output_validator(test)){
        cerr << "Test output #" << test << " failed to validate.\n";
        return -67;
    }

    cout << "----------------------------\n\n";

    if (validate_input) cerr << "Test input #" << test << " validated.\n";
    if (validate_output) cerr << "Test output #" << test << " validated.\n";
    return 0;
}
