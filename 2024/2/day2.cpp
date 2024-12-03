#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

static void readFileToVector(const char* filename, std::vector<std::vector<int>>& matrix) {
    for (auto vector : matrix) {
        vector.clear();
    }
    matrix.clear();

    std::ifstream file(filename);
    std::string line;
    while (getline(file, line)) {
        std::stringstream numStringStream(line);
        std::string numString;
        std::vector<int> numsVector;
        while (getline(numStringStream, numString, ' ')) {
            numsVector.push_back(stoi(numString));
        }
        matrix.push_back(numsVector);
    }
}

int solvePart1(std::vector<std::vector<int>>& matrix) {
    int safeReports = 0;

    for (auto vector : matrix) {
        int lastNum = vector[0];
        int lastDirection = (vector[0] - vector[1]) > 0;
        int safe = 1;

        for (int i = 1; i < vector.size(); ++i) {
            int direction = (lastNum - vector[i]) > 0;
            int difference = abs(lastNum - vector[i]);
            if (difference == 0 || difference > 3 || direction != lastDirection) {
                safe = 0;
                break;
            }
            lastNum = vector[i];
        }

        safeReports += safe;
    }

    return safeReports;
}

int solvePart2(std::vector<std::vector<int>>& matrix) {
    int safeReports = 0;

    for (auto vector : matrix) {
        int lastNum = vector[0];
        int lastDirection = (vector[0] - vector[1]) > 0;
        int unsafeties = 0;

        for (int i = 1; i < vector.size(); ++i) {
            int direction = (lastNum - vector[i]) > 0;
            int difference = abs(lastNum - vector[i]);
            if (difference == 0 || difference > 3 || direction != lastDirection) {
                unsafeties++;
            }
            lastNum = vector[i];
        }

        safeReports += (unsafeties < 2);
    }

    return safeReports;
}

int main() {
    std::vector<std::vector<int>> matrix;
    readFileToVector("input.txt", matrix);

    int part1Solution = solvePart1(matrix);

    std::cout << part1Solution << std::endl;

    int part2Solution = solvePart2(matrix);

    std::cout << part2Solution << std::endl;

    return 0;
}