#include <iostream>
#include <string>
#include <chrono>
#include <fstream>
#include <filesystem>

using namespace std;

void write(string file_path, string content) {
  ofstream file(file_path, ios::app);
  if (file.is_open()) {
    file << content;
  } else {
    file.open(file_path);
    file << content;
  }
  file.close();
}

void create_directory(string directory_path) {
  filesystem::create_directory(directory_path);
}

int main(int argc, char* argv[]) {

  string file_path;
  string directory_path;
  string username;
  string password;

  for (int i=0; i<argc; i++) {
    string arg = argv[i];
    if(arg == "-d"){
      if(i+1 <= argc){
        directory_path = argv[i+1];
      }
    }
    else if(arg == "-f"){
      if(i+1 <= argc){
        file_path = argv[i+1];
      }
    }
    else if(arg == "-u"){
      if(i+1 <= argc){
        username = argv[i+1];
      }
    }
    else if(arg == "-p"){
      if(i+1 <= argc){
        password = argv[i+1];
      }
    } 
    else {
      cout << "-d directory path \n-f for file path \n-u username \n-p password\n";
    }
  }

  cout << directory_path << "\n";

  return 0;
}
