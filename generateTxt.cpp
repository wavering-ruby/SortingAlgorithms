#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

void createOrderedNumbers(unsigned int N) {
    ofstream file("OrdenedNumbers.txt");
    for (unsigned int i = 1; i <= N; i++) {
        file << i;
        if (i != N)
            file << ",";
    }
    file.close();
}

void createReverseOrderedNumbers(unsigned int N) {
    ofstream file("ReverseOrdenedNumbers.txt");
    for (unsigned int i = N; i >= 1; i--) {
        file << i;
        if (i != 1)
            file << ",";
    }
    file.close();
}

void createRandomNumbers(unsigned int N) {
    vector<unsigned int> nums(N);
    for (unsigned int i = 0; i < N; i++) {
        nums[i] = i + 1;
    }
    random_device rd;
    mt19937 g(rd());
    shuffle(nums.begin(), nums.end(), g);

    ofstream file("RandomNumbers.txt");
    for (unsigned int i = 0; i < N; i++) {
        file << nums[i];
        if (i != N - 1)
            file << ",";
    }
    file.close();
}