#include<bits/stdc++.h>
#include "config/lib.h"
using namespace std;
using namespace RandomGen;
using namespace File;

#define int long long

NumberGen NumGen;
StringGen StrGen;
VectorGen VecGen;
int test = -1;

void generate_test(){
    stringstream input;
    ///////////////////////////////////////
    if(0 < test && test <= 50){
        int a = NumGen.Rand<int>(1, 100), b = NumGen.Rand<int>(1, 100);
        input << a << ' ' << b << '\n';
    }
    else if(50 < test && test <= 75){
        int a = NumGen.Rand<int>(1, 1e9), b = NumGen.Rand<int>(1, 1e9);
        input << a << ' ' << b << '\n';
    }
    else if(75 < test && test <= 100){
        string a = NumGen.BigRand("1" + string(50, '0'), "1" + string(500, '0')), b = NumGen.BigRand("1" + string(50, '0'), "1" + string(500, '0'));
        input << a << ' ' << b << '\n';
    }
    else exit(-3636);
    ///////////////////////////////////////
    createFile("baitap.inp", input.str());
}

signed main(int32_t argc, char* argv[]){
    ios_base::sync_with_stdio(0); cin.tie(0);

    if (argc >= 3 && string(argv[1]) == "-test"){
        try{
            test = stoi(argv[2]);
        } catch (...){
            cerr << "Error: Invalid test number.\n";
            return -1;
        }
    } else{
        cerr << "Usage: generate.exe -test <number>\n";
        return -1;
    }

    generate_test();

    return 0;
}
