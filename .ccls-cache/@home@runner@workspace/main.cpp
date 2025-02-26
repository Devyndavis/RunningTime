#include <iostream>
#include <vector>
#include <algorithm> 
#include <chrono>
#include <cstdlib>  // For rand() and srand()
#include <ctime>    // For time()

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

// Function to generate a vector with random numbers in range 1-100
vector<int> generateRandomVector(int size) {
    vector<int> arr;
    for (int i = 0; i < size; i++) {
        arr.push_back(rand() % 100 + 1); // Random number between 1 and 100
    }
    sort(arr.begin(), arr.end()); // Sorting before binary search
    return arr;
}

// Function to run tests
void runTests(const vector<int>& arr, int target) {
    cout << "Searching for target: " << target << endl;

    int index;

    auto start = chrono::high_resolution_clock::now();
    index = recursiveBinarySearch(arr, target);
    auto end = chrono::high_resolution_clock::now();
    cout << "Recursive Binary Search: " << (index != -1 ? "Found at index " : "Not found") << index << endl;
    cout << "Time: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " µs\n";

    start = chrono::high_resolution_clock::now();
    index = iterativeBinarySearch(arr, target);
    end = chrono::high_resolution_clock::now();
    cout << "Iterative Binary Search: " << (index != -1 ? "Found at index " : "Not found") << index << endl;
    cout << "Time: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " µs\n";

    start = chrono::high_resolution_clock::now();
    index = sequentialSearch(arr, target);
    end = chrono::high_resolution_clock::now();
    cout << "Sequential Search: " << (index != -1 ? "Found at index " : "Not found") << index << endl;
    cout << "Time: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " µs\n";

    cout << "------------------------------------\n";
}

int main() {
    srand(time(0)); // Seed for random number generation

    // Generate random vector
    vector<int> arr = generateRandomVector(20); // Adjust size as needed

    // Display vector contents
    cout << "Generated vector:\n";
    for (int num : arr) cout << num << " ";
    cout << "\n------------------------------------\n";

    // Generate a random target
    int target = rand() % 100 + 1;

    // Run searches
    runTests(arr, target);

    return 0;
}