#include<bits/stdc++.h>
#include "config/lib.h"
using namespace std;
using namespace RandomGen;
using namespace File;

#define int long long

struct Config{
    int NTEST = 50;
    string CODE = "TEST";
    string INP_DIR = "Tests/" + CODE + "/input", OUT_DIR = "Tests/" + CODE + "/output";

    string INP_EXT = ".inp", OUT_EXT = ".out";
    string SYSTEM = "default";

    string CPP_VERSION = "c++14";

    bool IS_INPUT = false, IS_OUTPUT = false;
    bool VALIDATE_INPUT = false, VALIDATE_OUTPUT = false;

    bool recompile = true;

    void update(){
        INP_DIR = SYSTEM == "default" || SYSTEM == "hackerrank" ? "Tests/" + CODE + "/input" : "Tests/" + CODE;
        OUT_DIR = SYSTEM == "default" || SYSTEM == "hackerrank" ? "Tests/" + CODE + "/output" : "Tests/" + CODE;
    }

    string getInpDir(int test){
        update();
        string dir;

        if(SYSTEM == "default") dir = INP_DIR + "/" + Utilities::String::toString(test) + INP_EXT;
        else if(SYSTEM == "hackerrank") dir = dir = INP_DIR + "/input" + Utilities::String::toString(test) + INP_EXT;
        else if(SYSTEM == "themis") dir = INP_DIR + "/TEST" + Utilities::String::toString(test) + "/" + CODE + INP_EXT;

        return dir;
    }

    string getOutDir(int test){
        update();
        string dir;

        if(SYSTEM == "default") dir = OUT_DIR + "/" + Utilities::String::toString(test) + OUT_EXT;
        else if(SYSTEM == "hackerrank") dir = dir = OUT_DIR + "/output" + Utilities::String::toString(test) + OUT_EXT;
        else if(SYSTEM == "themis") dir = OUT_DIR + "/TEST" + Utilities::String::toString(test) + "/" + CODE + OUT_EXT;

        return dir;
    }
};

namespace Info{
    Config config;

    int time_elapsed;
    int execution_time;

    int max_test_time = LLONG_MIN;
    int min_test_time = LLONG_MAX;
    double avg_test_time = 0;

    chrono::time_point<chrono::high_resolution_clock> start_time;
    chrono::time_point<chrono::high_resolution_clock> stop_time;

    ///////////////////////////////////////

    int to_ms(chrono::time_point<chrono::high_resolution_clock> start,
              chrono::time_point<chrono::high_resolution_clock> stop){

        return chrono::duration_cast<chrono::milliseconds>(stop - start).count();
    }

    void updateTime(){
        time_elapsed = 1.0 * clock() / CLOCKS_PER_SEC * 1000;
        execution_time = to_ms(start_time, stop_time);

        avg_test_time = 1.0 * execution_time / config.NTEST;
    }

    ///////////////////////////////////////

    struct TestCase{
        chrono::time_point<chrono::high_resolution_clock> test_start_time;
        chrono::time_point<chrono::high_resolution_clock> test_stop_time;
        int elapsed;

        TestCase(bool _start = false){ if(_start) Start(); }

        void Start(){
            this->test_start_time = chrono::high_resolution_clock::now();
        }

        void Stop(){
            this->test_stop_time = chrono::high_resolution_clock::now();
            updateTestTime();
        }

        int getTestTime(){
            return to_ms(test_start_time, test_stop_time);
        }

        void updateTestTime(){
            this->elapsed = getTestTime();
            Info::max_test_time = max(Info::max_test_time, this->elapsed);
            Info::min_test_time = min(Info::min_test_time, this->elapsed);
        }
    };
}

Config parseArgs(int32_t argc, char* argv[]){
    Config cfg;
    for (int i = 1; i < argc; ++i){
        string arg = argv[i];

        if((arg == "--code" || arg == "-c") && i + 1 < argc){
            cfg.CODE = argv[++i];
        }
        else if((arg == "--ntest" || arg == "-t") && i + 1 < argc){
            cfg.NTEST = stoi(argv[++i]);
        }
        else if(arg == "-input" || arg == "-inp"){
            cfg.IS_INPUT = true;
        }
        else if(arg == "-output" || arg == "-out"){
            cfg.IS_OUTPUT = true;
        }
        else if((arg == "--validate" || arg == "-v") && i + 1 < argc){
            string val = argv[++i];
            if(val == "input" || val == "inp"){
                cfg.VALIDATE_INPUT = true;
                cfg.VALIDATE_OUTPUT = false;
            } else if(val == "output" || val == "out"){
                cfg.VALIDATE_INPUT = false;
                cfg.VALIDATE_OUTPUT = true;
            } else if(val == "both"){
                cfg.VALIDATE_INPUT = true;
                cfg.VALIDATE_OUTPUT = true;
            } else{
                cerr << "Invalid value for --validate: " << val << '\n';
                exit(1);
            }
        }
        else if(arg == "--inpext" && i + 1 < argc){
            cfg.INP_EXT = argv[++i];
        }
        else if(arg == "--outext" && i + 1 < argc){
            cfg.OUT_EXT = argv[++i];
        }
        else if((arg == "--system" || arg == "--type") && i + 1 < argc){
            string val = argv[++i];
            if(val == "default" || val == "themis" || val == "hackerrank"){
                cfg.SYSTEM = val;
            } else{
                cerr << "Invalid type: " << val << " (unexpected system type)\n";
                exit(1);
            }
        }
        else if(arg == "--version" && i + 1 < argc) {
            string ver = argv[++i];
            static const vector<string> allowed = {"c++98", "c++03", "c++11", "c++14", "c++17"};
            if(find(allowed.begin(), allowed.end(), ver) != allowed.end()) {
                cfg.CPP_VERSION = ver;
            } else {
                cerr << "Invalid version: " << ver << " (allowed: c++98, c++03, c++11, c++14, c++17)\n";
                exit(1);
            }
        }
        else if(arg == "-norecompile" || arg == "-norc"){
            cfg.recompile = false;
        }
        else{
            cerr << "Unknown argument: " << arg << '\n';
            exit(1);
        }
    }

    if(!cfg.IS_INPUT && !cfg.IS_OUTPUT){
        cfg.IS_INPUT = true;
        cfg.IS_OUTPUT = true;
    }

    return cfg;
}

void sinh_input(int test){
    string inpPath = Info::config.getInpDir(test);

    ///////////////////////////////////////
    system(("generator.exe -test " + Utilities::String::toString(test)).c_str());
    ///////////////////////////////////////

    if(Info::config.SYSTEM == "themis"){
        createFolder(Utilities::String::removeFromLast(inpPath, '/'), true);
    }
    createFile(inpPath, readFile("baitap.inp"));
}

void sinh_output(int test){
    string outPath = Info::config.getOutDir(test);

    system("solver.exe < baitap.inp > baitap.out");

    string output = readFile("baitap.out");
    createFile(outPath, output);
}

void validate(int test){
    int validate_extcode = system(("validator.exe -test " + Utilities::String::toString(test) + " -type "
                                   + (Info::config.VALIDATE_INPUT && Info::config.VALIDATE_OUTPUT ? "both" :
                                      (Info::config.VALIDATE_INPUT ? "input" : "output"))).c_str());

    if(validate_extcode == 0){

    }
    else{
        cerr << "Program stopped!\n";
        exit(validate_extcode);
    }
}

signed main(int32_t argc, char* argv[]){
    Info::config = parseArgs(argc, argv);
    Info::config.update();

    if(!createFolder("./Tests/" + Info::config.CODE)){
        cout << "Problem already exists. Overwrite? (Y/N): ";

        char token; cin >> token;
        token = tolower(token);

        if(token == 'y'){
            deleteFolder("./Tests/" + Info::config.CODE, true);
            createFolder("./Tests/" + Info::config.CODE, true);
        }
        else{
            return 0;
        }
    }

    if(Info::config.IS_INPUT){
        createFolder(Info::config.INP_DIR);
        if(Info::config.recompile) system("g++ -std=c++14 -o generator generator.cpp");
    }
    if(Info::config.IS_OUTPUT){
        createFolder(Info::config.OUT_DIR);
        if(Info::config.recompile) system(("g++ -std=" + Info::config.CPP_VERSION + " -o solver solver.cpp").c_str());
    }
    if(Info::config.VALIDATE_INPUT || Info::config.VALIDATE_OUTPUT){
        if(Info::config.recompile) system("g++ -std=c++14 -o validator validator.cpp");
    }

    cout << "\n================== PROGRAM STARTED ==================\n\n";

    Info::start_time = chrono::high_resolution_clock::now();
    for(int test = 1; test <= Info::config.NTEST; ++test){
        cout << "[*] Generating test " << test << "...\n";

        Info::TestCase TestInfo;
        TestInfo.Start();

        if(Info::config.IS_INPUT) sinh_input(test);
        if(Info::config.IS_OUTPUT) sinh_output(test);
        if(Info::config.VALIDATE_INPUT || Info::config.VALIDATE_OUTPUT) validate(test);

        TestInfo.Stop();

        cout << "\n====================================\n";
    }
    Info::stop_time = chrono::high_resolution_clock::now();
    Info::updateTime();

    cout << "\n================== PROGRAM STOPPED ==================\n";

    cout << "\nInformation:\n";
    cout << "(*) Problem code: " << Info::config.CODE << "\n";
    cout << "(*) Input path: " << Info::config.INP_DIR << "\n";
    cout << "(*) Output path: " << Info::config.OUT_DIR << "\n";
    cout << "\n";
    cout << "(*) Elapsed: " << Info::time_elapsed << " ms\n";
    cout << "(*) #Tests: " << Info::config.NTEST << "\n";
    cout << "(*) #Time: " << Info::execution_time << " ms\n";
    cout << "\n";
    cout << "(*) Max. #Time: " << Info::max_test_time << " ms\n";
    cout << "(*) Min. #Time: " << Info::min_test_time << " ms\n";
    cout << "(*) Avg. #Time: " << Info::avg_test_time << " ms\n";
    cout << "\n";
    cout << "(*) is-Generate-Input: " << Info::config.IS_INPUT << "\n";
    cout << "(*) is-Generate-Output: " << Info::config.IS_OUTPUT << "\n";
    cout << "(*) is-Validate-Input: " << Info::config.VALIDATE_INPUT << "\n";
    cout << "(*) is-Validate-Output: " << Info::config.VALIDATE_OUTPUT << "\n";
    return 0;
}
