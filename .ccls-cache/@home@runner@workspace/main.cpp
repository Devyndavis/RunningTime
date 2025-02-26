#include <iostream>
#include <vector>
#include <algorithm> 
#include <chrono>

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

// Function to run tests
void runTests(const vector<int>& arr, int target) {
    auto start = chrono::high_resolution_clock::now();
    int index = recursiveBinarySearch(arr, target);
    auto end = chrono::high_resolution_clock::now();
    cout << "Recursive Binary Search: Target " << target << (index != -1 ? " found at index " : " not found") << index << endl;
    cout << "Time: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " µs\n";

    start = chrono::high_resolution_clock::now();
    index = iterativeBinarySearch(arr, target);
    end = chrono::high_resolution_clock::now();
    cout << "Iterative Binary Search: Target " << target << (index != -1 ? " found at index " : " not found") << index << endl;
    cout << "Time: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " µs\n";

    start = chrono::high_resolution_clock::now();
    index = sequentialSearch(arr, target);
    end = chrono::high_resolution_clock::now();
    cout << "Sequential Search: Target " << target << (index != -1 ? " found at index " : " not found") << index << endl;
    cout << "Time: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " µs\n";
}

int main() {
    vector<int> arr = {2, 3, 4, 10, 40, 50, 70, 80};  // Sample data
    sort(arr.begin(), arr.end());

    int target1 = 10;  // Present
    int target2 = 99;  // Not Present

    cout << "Testing with small dataset...\n";
    runTests(arr, target1);
    runTests(arr, target2);

    return 0;
}