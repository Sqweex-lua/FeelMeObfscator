#include "FeelMeHappy.h"
#include <chrono>
#include <iostream>
#include <vector>
#include <iomanip>

class PerformanceTimer {
private:
    std::chrono::high_resolution_clock::time_point start;
    
public:
    PerformanceTimer() {
        start = std::chrono::high_resolution_clock::now();
    }
    
    double elapsed() const {
        auto end = std::chrono::high_resolution_clock::now();
        return std::chrono::duration<double, std::milli>(end - start).count();
    }
};

void benchmark_string_obfuscation() {
    const int iterations = 1000000;
    std::vector<std::string> testStrings = {
        "short",
        "medium length string",
        "very long string for testing obfuscation performance",
        "https://api.example.com/v1/endpoint",
        "/usr/local/bin/application",
        "admin@company.com"
    };
    
    PerformanceTimer timer;
    
    for (int i = 0; i < iterations; i++) {
        for (const auto& str : testStrings) {
            volatile auto result = FEEL(str.c_str());
            (void)result;
        }
    }
    
    double time = timer.elapsed();
    double opsPerSec = (iterations * testStrings.size()) / (time / 1000.0);
    
    std::cout << "String obfuscation: " 
              << std::fixed << std::setprecision(2)
              << opsPerSec / 1000000.0 << " million ops/sec" << std::endl;
}

void benchmark_int_obfuscation() {
    const int iterations = 10000000;
    
    PerformanceTimer timer;
    
    for (int i = 0; i < iterations; i++) {
        volatile int result = FEEL(i);
        (void)result;
    }
    
    double time = timer.elapsed();
    double opsPerSec = iterations / (time / 1000.0);
    
    std::cout << "Integer obfuscation: "
              << std::fixed << std::setprecision(2)
              << opsPerSec / 1000000.0 << " million ops/sec" << std::endl;
}

void benchmark_float_obfuscation() {
    const int iterations = 5000000;
    
    PerformanceTimer timer;
    
    for (int i = 0; i < iterations; i++) {
        volatile float result = FEEL(static_cast<float>(i) * 0.1f);
        (void)result;
    }
    
    double time = timer.elapsed();
    double opsPerSec = iterations / (time / 1000.0);
    
    std::cout << "Float obfuscation: "
              << std::fixed << std::setprecision(2)
              << opsPerSec / 1000000.0 << " million ops/sec" << std::endl;
}

void benchmark_cache_performance() {
    const int uniqueStrings = 1000;
    const int iterations = 100000;
    
    std::vector<std::string> strings;
    for (int i = 0; i < uniqueStrings; i++) {
        strings.push_back("string_" + std::to_string(i) + "_test_data");
    }
    
    PerformanceTimer timer;
    
    for (int i = 0; i < iterations; i++) {
        int index = i % uniqueStrings;
        volatile auto result = FEEL(strings[index].c_str());
        (void)result;
    }
    
    double time = timer.elapsed();
    double opsPerSec = iterations / (time / 1000.0);
    
    std::cout << "Cache performance: "
              << std::fixed << std::setprecision(2)
              << opsPerSec / 1000.0 << " thousand ops/sec" << std::endl;
}

void benchmark_memory_usage() {
    const int iterations = 10000;
    const int stringLength = 1024;
    
    std::string longString(stringLength, 'X');
    
    PerformanceTimer timer;
    
    size_t totalMemory = 0;
    for (int i = 0; i < iterations; i++) {
        auto result = FEEL(longString.c_str());
        totalMemory += strlen(result) + 1;
    }
    
    double time = timer.elapsed();
    
    std::cout << "Memory test: " 
              << std::fixed << std::setprecision(2)
              << (totalMemory / 1024.0 / 1024.0) << " MB processed in "
              << time << " ms" << std::endl;
}

void benchmark_concurrent_performance() {
    const int numThreads = 8;
    const int iterations = 100000;
    
    PerformanceTimer timer;
    
    std::vector<std::thread> threads;
    for (int t = 0; t < numThreads; t++) {
        threads.emplace_back([iterations, t]() {
            for (int i = 0; i < iterations; i++) {
                int value = t * iterations + i;
                volatile int result = FEEL(value);
                (void)result;
                
                std::string str = "thread_" + std::to_string(t) + "_" + std::to_string(i);
                volatile auto strResult = FEEL(str.c_str());
                (void)strResult;
            }
        });
    }
    
    for (auto& thread : threads) {
        thread.join();
    }
    
    double time = timer.elapsed();
    double totalOps = numThreads * iterations * 2;
    double opsPerSec = totalOps / (time / 1000.0);
    
    std::cout << "Concurrent performance (" << numThreads << " threads): "
              << std::fixed << std::setprecision(2)
              << opsPerSec / 1000000.0 << " million ops/sec" << std::endl;
}

int main() {
    std::cout << "=== Performance Benchmarks ===" << std::endl;
    std::cout << std::endl;
    
    benchmark_string_obfuscation();
    benchmark_int_obfuscation();
    benchmark_float_obfuscation();
    benchmark_cache_performance();
    benchmark_memory_usage();
    benchmark_concurrent_performance();
    
    std::cout << std::endl;
    std::cout << "=== Benchmarks completed ===" << std::endl;
    
    return 0;
}
