/******************************************************************************
 * Project: File Template
 * Author: Phan Thanh Hung - hungg261
 * Created (dd-mm-yyyy): 01-11-2025
 * Description:
 *      Template for random generation.
 * Version: >= C++14, Windows
 ******************************************************************************/
#ifndef FILE_H
#define FILE_H

#include<bits/stdc++.h>
#include <conio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

namespace File{

bool createFolder(string dirpath, bool debug = false){
    if(!mkdir(dirpath.c_str())) return true;

    if(debug){
        cerr << "Folder already existed!\n";
        cerr << ("Path: " + dirpath) << "\n";
        exit(-1);
    }
    return false;
}

bool deleteFolder(string dirpath, bool debug = false){
    if(system(("rmdir /S /Q \"" + dirpath + "\"").c_str()) != 0){
        if(debug){
            cerr << "Couldn\'t delete folder!\n";
            exit(-2);
        }
        return false;
    }

    return true;
}

bool appendFile(string filepath, string content = "", ios::openmode mode = ios::app | ios::binary, bool debug = false){
    ofstream fileObj(filepath, mode);

    if(!fileObj){
        if(debug){
            cerr << ("Couldn\'t open file " + filepath) << "\n";
        }

        exit(-3); return false;
    }


    fileObj << content;

    fileObj.close();
    return true;
}

bool createFile(string filepath, string content = ""){
    return appendFile(filepath, content, ios::out | ios::binary);
}

string readFile(const string& filename) {
    ifstream file(filename, ios::in | ios::binary);
    if (!file) return "";

    string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    return content;
}

bool deleteFile(string filepath){
    if(remove(filepath.c_str()) != 0){
        exit(-4);
        return false;
    }

    return true;
}


void highlightFileInExplorer(const string &path) {
    string cmd = "explorer /select,\"" + path + "\"";
    system(cmd.c_str());
}

void openFolderInExplorer(const string& path){
    string cmd = "explorer \"" + path + "\"";
    system(cmd.c_str());
}

}

#endif // FILE_H
