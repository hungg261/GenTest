/*

hungg261.
yes, i used AI for this because i was too lazy :)

*/

#include <bits/stdc++.h>
using namespace std;

/// ==================== Utilities ====================
namespace Utilities {
    namespace String {
        string toLower(const string &s) {
            string res = s;
            transform(res.begin(), res.end(), res.begin(), ::tolower);
            return res;
        }

        bool isExit(const string &s) { return toLower(s) == "<exit>"; }
    }

    /// Prompt for input with reprompt, < to go back, exit to quit
    string promptInput(const string &msg, bool allowBack = false) {
        string input;
        while (true) {
            cout << msg;
            getline(cin, input);

            if (Utilities::String::isExit(input)) exit(0);
            if (allowBack && input == "<") return "<";
            if (input.empty()) continue;
            return input;
        }
    }

    /// Ask Y/N question
    bool yesNo(const string &msg) {
        string ans;
        while (true) {
            cout << msg << " (Y/N): ";
            getline(cin, ans);
            if (Utilities::String::isExit(ans)) exit(0);
            ans = Utilities::String::toLower(ans);
            if (ans == "y") return true;
            if (ans == "n") return false;
            cout << "[!] Invalid input.\n";
        }
    }

    /// Open file in Explorer and select it
    void openInExplorer(const string &path) {
        string cmd = "explorer /select,\"" + path + "\"";
        system(cmd.c_str());
    }

    /// Run system command
    void runCommand(const string &cmd) {
        int ret = system(cmd.c_str());
        if (ret != 0) cout << "[!] Command failed with code: " << ret << "\n";
    }

    /// Compile C++ file
    void compileFile(const string &filename, const string &output = "main.exe", const string &cpp_version = "c++14") {
        cout << "[*] Compiling " << filename << " ...\n";
        int code = system(("g++ -std=" + cpp_version + " -o " + output + " " + filename).c_str());
        if (code != 0) {
            cerr << "[!] Compilation failed.\n";
            exit(1);
        }
    }
}

/// ==================== Configuration ====================
struct GenTestConfig {
    string inputExt = ".inp";
    string outputExt = ".out";
    string systemType = "default"; // default / themis / hackerrank
};

/// ==================== GUI Functions ====================
void showCredits() {
    cout << "\n================ Credits ================\n";
    cout << "GenTest - Test Generator\n";
    cout << "Author: Phan Thanh Hung - hungg261\n";
    cout << "Windows only\n";
    cout << "========================================\n\n";
    system("pause");
}

void showInfo() {
    system("main.exe --version");
}

void settingsMenu(GenTestConfig &cfg) {
    while (true) {
        cout << "\n================ Settings =================\n";
        cout << "[1] Set input extension (current: " << cfg.inputExt << ")\n";
        cout << "[2] Set output extension (current: " << cfg.outputExt << ")\n";
        cout << "[3] Set system type (current: " << cfg.systemType << ")\n";
        cout << "[4] Edit generator.cpp\n";
        cout << "[5] Edit solver.cpp\n";
        cout << "[6] Edit validator.cpp\n";
        cout << "[0] Back\n";
        cout << "========================================\n";

        string choice = Utilities::promptInput("-> ");
        if (choice == "0") return;

        if (choice == "1") cfg.inputExt = Utilities::promptInput("Enter new input extension (e.g., .inp): ");
        else if (choice == "2") cfg.outputExt = Utilities::promptInput("Enter new output extension (e.g., .out): ");
        else if (choice == "3") {
            string sys = Utilities::promptInput("Enter system type (default/themis/hackerrank): ");
            sys = Utilities::String::toLower(sys);
            if (sys == "default" || sys == "themis" || sys == "hackerrank") cfg.systemType = sys;
            else cout << "[!] Invalid system type.\n";
        } else if (choice == "4") Utilities::openInExplorer("generator.cpp");
        else if (choice == "5") Utilities::openInExplorer("solver.cpp");
        else if (choice == "6") Utilities::openInExplorer("validator.cpp");
        else cout << "[!] Invalid option.\n";
    }
}

void newProblemMenu(const GenTestConfig &cfg) {
    cout << "\n================ New Problem =================\n";

    string code = Utilities::promptInput("Enter problem code: ");
    if (code == "<") return;

    string ntestStr = Utilities::promptInput("Enter number of tests: ");
    int ntest = stoi(ntestStr);

    bool generateInput = Utilities::yesNo("Generate input?");
    bool generateOutput = Utilities::yesNo("Generate output?");

    bool validateInput = false, validateOutput = false;
    if(Utilities::yesNo("Add validator?")){
        validateInput = Utilities::yesNo("Validate input?");
        validateOutput = Utilities::yesNo("Validate output?");
    }

    /// Build command
    string cmd = "main.exe";
    cmd += string(" --code \"") + code + "\"";
    cmd += " --ntest " + to_string(ntest);
    if (generateInput) cmd += " --input";
    if (generateOutput) cmd += " --output";

    if (validateInput && !validateOutput) cmd += " --validate input";
    else if (!validateInput && validateOutput) cmd += " --validate output";
    else if (validateInput && validateOutput) cmd += " --validate both";

    cmd += " --inpext " + cfg.inputExt;
    cmd += " --outext " + cfg.outputExt;
    cmd += " --type " + cfg.systemType;

    cout << "\n================ Generated Command =================\n";
    cout << cmd << "\n";
    cout << "=====================================================\n";

    if (Utilities::yesNo("Run command now?")) Utilities::runCommand(cmd);
    else cout << "You can copy & run the command manually.\n";

    cout << "\nProblem finished.\n";
}

/// ==================== Main ====================
int main() {
    GenTestConfig cfg;

    /// Compile main.cpp at start
    Utilities::compileFile("main.cpp");

    while (true) {
        cout << "\n================ GenTest - Test Generator GUI ================\n";
        cout << "[1] New problem\n";
        cout << "[2] Settings\n";
        cout << "[3] Credits\n";
        cout << "[4] Info\n";
        cout << "[0] Exit\n";

        string choice = Utilities::promptInput("-> ");

        if (choice == "0") break;
        else if (choice == "1") newProblemMenu(cfg);
        else if (choice == "2") settingsMenu(cfg);
        else if (choice == "3") showCredits();
        else if (choice == "4") showInfo();
        else cout << "[!] Invalid option.\n";
    }

    cout << "\nExiting GenTest. Goodbye!\n";
    return 0;
}
