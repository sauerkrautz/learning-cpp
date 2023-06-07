#include <ctime>
#include <iostream>
#include <random>
#include <thread>
#include <vector>

void generate_random_number() {
  int number[] = {100000,10000000};
  std::random_device rd;
  std::mt19937 random(rd());
  std::vector<int> random_numbers;

  std::uniform_int_distribution<int> random_number(0, number[1] - 1);

  for(int i=0; i < number[0]; i++) {
    random_numbers.push_back(random_number(random));
  }

  for(int i=0; i<number[0]; i++) {
    std::cout << random_numbers[i] << std::endl;
  }

}

int main(int argc, char* argv[]) {
  int time = std::clock();
  std::thread th1(generate_random_number);
  std::thread th2(generate_random_number);

  th1.join();
  th2.join();
  std::cout << time << std::endl;
  return 0;
}
