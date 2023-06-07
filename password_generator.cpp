#include <iostream>
#include <random>
#include <string>
#include <fstream>

std::string generate_password(int length) {

  std::string password;
  std::string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()";

  std::random_device rd;
  std::mt19937 generator(rd());

  std::uniform_int_distribution<int> distributor(0,characters.length() - 1);

  for (int i=0; i < length; i++) {
    int randomNumber = distributor(generator);
    password += characters[randomNumber];
  }

  return password;
}

int generate_file(int length, std::string file_path, const int& iteration=1) {
   
  std::ofstream file(file_path, std::ios::app);

  if (iteration != 0) {

   if (!file) {
   // getting or creating the file to write
   std::ofstream newfile(file_path);

   for (int i=0; i < iteration; i++) {
      // generate the password
   std::string password = generate_password(length);

   // write the file
   newfile << password << "\n";
   }

   // close the file after writing
   newfile.close();

  } else {
   
   // generate multiple passwords
   for (int i=0; i < iteration; i++) {
   std::string password = generate_password(length);
   file << password << "\n"; 

   }

   file.close();
  
  }
  
  } else {

    if (!file) {
   // getting or creating the file to write
   std::ofstream newfile(file_path);

   // generate the password
   std::string password = generate_password(length);

   // write the file
   newfile << password << "\n";

   // close the file after writing
   newfile.close();

  } else {
   
   std::string password = generate_password(length);
   file << password << "\n"; 
   file.close();

  }
  }

  return 0;
}

int main(int argc, char* argv[]) {

  generate_file(std::stoi(argv[1]), argv[2], argv[3] != nullptr ? std::stoi(argv[3]) : 1);
  std::cout << "\n";

  return 0;
}
