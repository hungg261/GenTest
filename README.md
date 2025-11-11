# GenTest

GenTest is a simple Windows-only console GUI for generating and validating problem tests.  
It allows you to generate inputs and outputs, validate them, and edit generator/solver/validator files easily.

## Download

**Make sure you have `g++` installed (part of MinGW or similar) and added to your PATH.**

1. Download the zip file from GitHub, extract it then run `GenTest.exe`.
   
   If there is no `GenTest.exe`, compile `GenTest.cpp` and run:
   
   ```batch
   g++ GenTest.cpp -o GenTest.exe
   ```
   
   ```batch
   GenTest.exe
   ```

2. After that, the main menu will appear, and magic starts.

## Usage

**Note:** Before generating any test cases, make sure to modify the generator, validator and solver based on the problem. Also, there are some helpers function declared in `./GenTest/config/lib.h` such as random, file management, utilities.

#### GUI App

1. Click on `GenTest.exe`, you will see a console which has a few options.
   
   - Create new problem
     
     - This is where a new problem (test cases) will be generated.
     
     - You will be asked about problem name/code (such as MINQUERY, GCDMAX,...), the number of test cases (i.e. 100, 50, 20,...), if inputs and outputs are generated, add test (input/output) validator.
     
     - Then, the app will generate a command line to generate test cases, and you can generate the tests right away!
   
   - Settings
     
     - You can change things like input file extension. output file extension, type of system (could be default, hackerrank, or themis),...
   
   - Credits
   
   - Exit

**Notes:**

- Type `<exit>` when promted to automatically exit the program.

#### Command line

1. Go to folder `./GenTest/` and compile `main.cpp` into `main.exe`, version `-std=c++14`.

2. Run on console: `main.exe` to generate a new program, here are the flags:
   
   - `--code <name>`/`-c`: the name/code of the problem.
   
   - `--ntest <#>`/`-t`: the number of test cases.
   
   - `-input`/`-inp`: generate inputs.
   
   - `-output`/`-out`: generate outputs.
   
   - `--validate <args>`/`-v`: validate inputs or outputs:
     
     - `input`/`inp`: validate inputs only.
     
     - `output`/`out`: validate outputs only.
     
     - `both`: validate both inputs and outputs.
   
   - `--inpext <extension>`: extension of input files.
   
   - `--outext <extension>`: extension of output files.
   
   - `--system <type>`: type of test cases (`default`, `hackerrank`, or `themis`).
   
   - `--version <cppversion>`: version the `solver.cpp` will be compiled
     
     - Available versions: `{"c++98", "c++03", "c++11", "c++14", "c++17"}`
   
   - `-norecompile`/`-norc`: don't automatically compile related files.

For example, this is an example of generated command:

```batch
main.exe --code "PROBLEMCODE" --ntest 100 -input -output --validate both --system themis
```

- If you use the GUI App, it will generate it for you.

## Credits

Made by Hung (hungg261).

Inspired by "testlib.h".

Note: I will update and maintain it frequently (hopefully).

HCMC, Vietnam, 2025.
