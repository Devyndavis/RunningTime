#include <iostream>
#include <vector>
#include <algorithm> 
#include <chrono>
#include <cstdlib>  
#include <ctime>    

using namespace std;

// Sequential Search
int sequentialSearch(const vector<int>& arr, int target) {
    for (size_t i = 0; i < arr.size(); i++) {
        if (arr[i] == target) return i;
    }
    return -1;
}

// Recursive Binary Search
int recursiveBinarySearchHelper(const vector<int>& arr, int target, int left, int right) {
    if (left > right) return -1;
    int mid = left + (right - left) / 2;
    if (arr[mid] == target) return mid;
    else if (arr[mid] > target) return recursiveBinarySearchHelper(arr, target, left, mid - 1);
    else return recursiveBinarySearchHelper(arr, target, mid + 1, right);
}

int recursiveBinarySearch(const vector<int>& arr, int target) {
    return recursiveBinarySearchHelper(arr, target, 0, arr.size() - 1);
}

// Iterative Binary Search
int iterativeBinarySearch(const vector<int>& arr, int target) {
    int left = 0, right = arr.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) return mid;
        else if (arr[mid] > target) right = mid - 1;
        else left = mid + 1;
    }
    return -1;
}

// Function to generate a sorted vector with N random numbers in range 1-100
vector<int> generateRandomVector(int size) {
    vector<int> arr(size);
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 100 + 1; // Random number between 1 and 100
    }
    sort(arr.begin(), arr.end()); // Sorting before binary search
    return arr;
}

// Function to measure search times
void analyzePerformance(int N) {
    cout << "\nTesting with N = " << N << "...\n";

    double sumRBS = 0, sumIBS = 0, sumSeqS = 0;

    for (int i = 0; i < 10; i++) {
        vector<int> arr = generateRandomVector(N);
        int target = rand() % 100 + 1; // Random target

        // Recursive Binary Search
        auto start = chrono::high_resolution_clock::now();
        recursiveBinarySearch(arr, target);
        auto end = chrono::high_resolution_clock::now();
        sumRBS += chrono::duration_cast<chrono::microseconds>(end - start).count();

        // Iterative Binary Search
        start = chrono::high_resolution_clock::now();
        iterativeBinarySearch(arr, target);
        end = chrono::high_resolution_clock::now();
        sumIBS += chrono::duration_cast<chrono::microseconds>(end - start).count();

        // Sequential Search
        start = chrono::high_resolution_clock::now();
        sequentialSearch(arr, target);
        end = chrono::high_resolution_clock::now();
        sumSeqS += chrono::duration_cast<chrono::microseconds>(end - start).count();
    }

    cout << "Average Running Time for Recursive Binary Search: " << sumRBS / 10.0 << " µs\n";
    cout << "Average Running Time for Iterative Binary Search: " << sumIBS / 10.0 << " µs\n";
    cout << "Average Running Time for Sequential Search: " << sumSeqS / 10.0 << " µs\n";
    cout << "----------------------------------------------\n";
}

int main() {
    srand(time(0)); // Seed for random number generation

    // Run tests for different values of N
    analyzePerformance(5000);
    analyzePerformance(50000);
    analyzePerformance(100000);
    analyzePerformance(150000);
    analyzePerformance(1000000);

    return 0;
}