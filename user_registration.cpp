#include <filesystem>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <fstream>
#include <random>

// registration can be interactive and also "scriptable"

// split space separated strings and return the separated string by providing an
// index of the string in the array
std::vector<std::string> split(std::string word) {
  std::vector<std::string> words;
  std::istringstream string_stream(word);

  std::string separated_word;

  while (string_stream >> separated_word) {
    words.push_back(separated_word);
  }

  return words;
}

bool check_duplicate_user(std::string file_path, std::string username) {
  std::ifstream file(file_path, std::ios::app);
  std::string current_line;
  std::vector<std::string> users;

  while (std::getline(file, current_line)) {
    users.push_back(current_line);
  }

  for (std::string user : users) {
    if (split(user)[1] == username) {
      std::cout << "username duplication detected" << std::endl;
      return true;
    } else {
      continue;
    }
  }
  return false;
}

// getting the last line of the file **
std::string get_last_user(std::string file_path) {
  std::ifstream file(file_path, std::ios::app);
  std::string current_line;
  std::string last_line;

  while (std::getline(file, current_line)) {
    last_line = current_line;
  }

  return last_line;
}

// create file if file doesn't exist and add lines of user and password pair if
// the file already exist
bool handle_file(std::string file_path, std::string username,
                 std::string password) {

  // check if the file already exist
  if (!std::filesystem::exists(file_path)) {
    std::ofstream file(file_path, std::ios::app);
    file << 0 << " " << username << " " << password << "\n";
    // std::cout << "run when file doesn't exist yet" << std::endl;
    file.close();

  } else {
    if (check_duplicate_user(file_path, username)) {
      return false;
    } else {
      std::ofstream file(file_path, std::ios::app);
      std::string last_user = get_last_user(file_path);
      int last_user_id = std::stoi(split(last_user)[0]);
      file << (last_user_id + 1) << " " << username << " " << password << "\n";
      file.close();
      return true;
    }
  }

  return false;
}

std::vector<std::string> get_user_by_number(std::string file_path, int user_number) {
  std::ifstream file(file_path, std::ios::app);
  std::string current_line;
  std::string user;

  while(std::getline(file, current_line)) {
    if(std::stoi(split(current_line)[0]) == user_number) {
      user = current_line;
    }
  }

  return split(user);
}

// getting the user number or user id **
// int get_user_number(std::string file_path) {
//   std::ifstream file(file_path);

//   if (!file) {
//     std::cout << "file not found";
//     return 1;
//   }
//
//   std::string last_line;
//   std::string current_line;
//   while (std::getline(file, current_line)) {
//     last_line = current_line;
//   }

//   return 0;
// }

int main(int argc, char *argv[]) {

  std::string file_path;
  std::string username;
  std::string password;
  int user_number = -1;

  std::random_device rd;
  std::mt19937 generate(rd());

  std::uniform_int_distribution<int> numbers(0, 100);

  // check for flags arguments
  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];

    if (arg == "-i") {
      if (i + 1 <= argc) {
        file_path = argv[i + 1];
      }
    } else if (arg == "-u") {
      if (i + 1 <= argc) {
        username = argv[i + 1];
      }
    } else if (arg == "-p") {
      if (i + 1 <= argc) {
        password = argv[i + 1];
      }
    } else if (arg == "-h") {
      std::cout << "-i            input file name"
                << "\n"
                << "-u             username to be written to file"
                << "\n"
                << "-p            password to be written to file"
                << "\n";
    } else if (arg == "-g") {
      if (i + 1 <= argc) {
        user_number = std::stoi(argv[i + 1]);
      }
    } else if (argc < 1) {
      std::cout << "-h for help";
    }
  }

  handle_file(file_path, username, password);

  if(user_number != -1) {
    std::cout << get_user_by_number(file_path, user_number)[1] << std::endl;
  }
  // std::cout << file_path << " " << username << " " << password << "\n";

  return 0;
}
