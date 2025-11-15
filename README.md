# GenTest

GenTest is a simple **Windows-only** console GUI for generating and validating problem tests.  
It allows you to generate inputs and outputs, validate them, and easily edit generator, solver, and validator files.

## Download

**Prerequisite:** `g++` (from MinGW or similar) must be installed and added to your PATH.

1. Download the zip file from GitHub, extract it.

2. - If `GenTest.exe` exists, double-click to launch.
   
   - Otherwise, compile manually:
   
   ```batch
   g++ GenTest.cpp -o GenTest.exe
   ```
   
   ```batch
   GenTest.exe
   ```

3. After that, the main menu will appear, and magic begins.

## Usage

**Note:** Before generating any test cases, make sure to modify the generator, validator, and solver according to the problem. Also, there are some helper functions declared in `./GenTest/config/lib.h`, such as random, file management, and utilities.

Helper functions (random generators, file management, utilities) are provided in [config](./GenTest/config) folder, and the main header is [lib.h](./GenTest/config/lib.h).

By the way, the default (example) generator, validator, and solver are for the problem A TIMES B.

#### GUI

1. Click on `GenTest.exe`; you will see a console with a few options.
   
   - Create new problem
     
     - This is where a new problem (test cases) will be generated.
     
     - You will be asked for the problem name/code (such as MINQUERY, GCDMAX, etc.), the number of test cases (e.g., 100, 50, 20), whether to generate inputs and outputs, and whether to add a test (input/output) validator.
     
     - Then, the app will generate a command line to generate test cases, and you can generate the tests right away!
   
   - Settings
     
     - You can change settings such as the input file extension, output file extension, and system type (default, hackerrank, or themis).
   
   - Credits
   
   - Exit

**Notes:**

- Type `<exit>` when prompted to automatically exit the program.

#### Command line

1. Go to the folder `./GenTest/` and compile `main.cpp` into `main.exe` using the `-std=c++14` flag.

2. Run `main.exe` in the console to generate a new program. Here are the available flags:`--code <name>`/`-c`: the name/code of the problem.
   
   - `--version`/`-v`: returns the current name and version.
   
   - `--ntest <#>`/`-t`: the number of test cases.
   
   - `--input`/`-inp`: generate inputs.
   
   - `--output`/`-out`: generate outputs.
   
   - `--validate <args>`/`-vl`: validate inputs or outputs:
     
     - `input`/`inp`: validate inputs only.
     
     - `output`/`out`: validate outputs only.
     
     - `both`: validate both inputs and outputs.
   
   - `--inpext <extension>`/`-ie`: extension of input files.
   
   - `--outext <extension>`/`-oe`: extension of output files.
   
   - `--system <type>`/`-sys`/`-s`: type of test cases (`default`, `hackerrank`, or `themis`).
   
   - `--cppversion <cppversion>`/`-cv`: version the `solver.cpp` will be compiled
     
     - Available versions: `{"c++98", "c++03", "c++11", "c++14", "c++17"}`
   
   - `-norecompile`/`-norc`: don't automatically compile related files.

For example, this is an example of generated command:

```batch
main.exe --code "PROBLEMCODE" --ntest 100 -input -output --validate both --system themis
```

- If you use the GUI App, it will generate it for you.

##### About generated test cases

- The test cases will be generated in `./GenTest/Tests`. From here, you can compress it to zip and then upload to your server, or do anything you want.
- The folder containing the tests will be open right after the everything was finished.

##### About solver file

- The `solver.cpp` file is the main correct solution that will be used to generate test. The input and output are from stdin and stdout, respectively.

## Credits

Made by Hung (hungg261).

Inspired by "testlib.h".

Note: I will update and maintain it frequently (hopefully). Rawhhhhh

HCMC, Vietnam, 2025.
