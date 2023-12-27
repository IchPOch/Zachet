#include <iostream>
#include <thread>
#include <vector>
#include <numeric>

constexpr int N = 1000000;
constexpr int NumThreads = 4;


auto partialSum = [](int start, int end) {
    double result = 0;
    for (int n = start; n <= end; ++n) {
        result += static_cast<double>(n + 1) / n;
    }
    return result;
};

int main() {
    double sum = 0;

    std::vector<std::thread> threads;

    int step = N / NumThreads;

    for (int i = 0; i < NumThreads; ++i) {
        int start = i * step + 1;
        int end = (i == NumThreads - 1) ? N : (i + 1) * step;
        threads.emplace_back([start, end, &sum, i]() {
            sum += partialSum(start, end);
            });
    }

    for (auto& thread : threads) {
        thread.join();
    }

    std::cout << "Total sum: " << sum << std::endl;

    return 0;
}