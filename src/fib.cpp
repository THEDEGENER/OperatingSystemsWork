#include <iostream>
#include <vector>
#include <chrono>
#include <utility>
#include <fstream>

// Include Boost multiprecision for big integer arithmetic.
#include <boost/multiprecision/cpp_int.hpp>

using boost::multiprecision::cpp_int;
using namespace std;
using namespace std::chrono;

// Recursive Fibonacci with memoization
cpp_int fib_memo(int n, vector<cpp_int>& memo) {
    if(n <= 1)
        return n;
    if(memo[n] != -1)
        return memo[n];
    memo[n] = fib_memo(n - 1, memo) + fib_memo(n - 2, memo);
    return memo[n];
}

// Fast doubling method: returns a pair {F(n), F(n+1)}
pair<cpp_int, cpp_int> fib_fast_doubling(int n) {
    if (n == 0)
        return {0, 1};
    auto p = fib_fast_doubling(n >> 1);
    cpp_int a = p.first;
    cpp_int b = p.second;
    cpp_int c = a * (2 * b - a);
    cpp_int d = a * a + b * b;
    if (n & 1)
        return {d, c + d};
    else
        return {c, d};
}

int write_file(auto fib_num) {
    // Opens the file "output.txt" for writing.
    // std::ios::out flag opens it in output mode.
    // std::ios::trunc flag (default for ofstream) clears the file if it already exists.


    std::ofstream outFile("fib.txt", std::ios::out | std::ios::trunc);

    // Check if the file was opened successfully
    if (!outFile) {
        std::cerr << "Error opening the file." << std::endl;
        return 1;
    }

    // Write text into the file
    outFile << fib_num << std::endl;
    

    // Close the file
    outFile.close();

    std::cout << "File written successfully." << std::endl;
    return 0;
}

int main() {
    int n;
    cout << "enter nth number to calculate > ";
    cin >> n;
    
    
    // --- Fast doubling approach ---
    auto start_doubling = high_resolution_clock::now();
    auto result_pair = fib_fast_doubling(n);
    cpp_int result_doubling = result_pair.first;
    auto end_doubling = high_resolution_clock::now();
    duration<double> elapsed_doubling = end_doubling - start_doubling;
    
    cout << "Fast doubling approach for F(" << n << ") computed in "
         << elapsed_doubling.count() << " seconds." << endl;
    // Uncomment if you want to print the result:
    // cout << "F(" << n << ") = " << result_doubling << endl;
    write_file(result_doubling);
    
    return 0;
}
