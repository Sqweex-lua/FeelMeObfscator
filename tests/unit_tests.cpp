#include "FeelMeHappy.h"
#include <cassert>
#include <iostream>
#include <string>

void test_string_obfuscation() {
    const char* original = "Hello World";
    const char* obfuscated = FEEL(original);
    
    assert(obfuscated != nullptr);
    assert(strcmp(obfuscated, original) == 0);
    
    std::cout << "✓ String obfuscation test passed" << std::endl;
}

void test_int_obfuscation() {
    int original = 42;
    int obfuscated = FEEL(original);
    
    assert(obfuscated == original);
    
    for (int i = -1000; i <= 1000; i += 100) {
        int obf = FEEL(i);
        assert(obf == i);
    }
    
    std::cout << "✓ Integer obfuscation test passed" << std::endl;
}

void test_float_obfuscation() {
    float original = 3.14159f;
    float obfuscated = FEEL(original);
    
    assert(obfuscated == original);
    
    double doriginal = 123.456789;
    double dobfuscated = FEEL(doriginal);
    
    assert(dobfuscated == doriginal);
    
    std::cout << "✓ Float obfuscation test passed" << std::endl;
}

void test_array_obfuscation() {
    int arr[] = {1, 2, 3, 4, 5};
    int* obfArr = FEEL(arr);
    
    for (int i = 0; i < 5; i++) {
        assert(obfArr[i] == arr[i]);
    }
    
    const char* strings[] = {"one", "two", "three"};
    const char** obfStrings = FEEL(strings);
    
    for (int i = 0; i < 3; i++) {
        assert(strcmp(obfStrings[i], strings[i]) == 0);
    }
    
    std::cout << "✓ Array obfuscation test passed" << std::endl;
}

void test_struct_obfuscation() {
    struct TestStruct {
        int id;
        char name[32];
        float value;
    };
    
    TestStruct original = {1, "Test", 3.14f};
    TestStruct obfuscated = FEEL(original);
    
    assert(obfuscated.id == original.id);
    assert(strcmp(obfuscated.name, original.name) == 0);
    assert(obfuscated.value == original.value);
    
    std::cout << "✓ Struct obfuscation test passed" << std::endl;
}

void test_type_detection() {
    using namespace _feel_me_happy_;
    
    const char* path = "/usr/bin/app";
    auto type1 = TypeDetector::detect(path);
    assert(type1 == TypeDetector::DataType::Path);
    
    const char* url = "https://example.com";
    auto type2 = TypeDetector::detect(url);
    assert(type2 == TypeDetector::DataType::URL);
    
    const char* email = "test@example.com";
    auto type3 = TypeDetector::detect(email);
    assert(type3 == TypeDetector::DataType::Email);
    
    const char* sql = "SELECT * FROM users";
    auto type4 = TypeDetector::detect(sql);
    assert(type4 == TypeDetector::DataType::SQL);
    
    std::cout << "✓ Type detection test passed" << std::endl;
}

void test_cache_functionality() {
    using namespace _feel_me_happy_;
    
    ObfuscationCache<std::string, std::string> cache;
    
    std::string key = "test_key";
    std::string value = "test_value";
    Byte keyByte = 0x42;
    
    cache.put(key, value, keyByte);
    
    std::string retrieved;
    Byte retrievedKey;
    bool found = cache.get(key, retrieved, retrievedKey);
    
    assert(found);
    assert(retrieved == value);
    assert(retrievedKey == keyByte);
    
    cache.invalidate(key);
    found = cache.get(key, retrieved, retrievedKey);
    assert(!found);
    
    std::cout << "✓ Cache functionality test passed" << std::endl;
}

void test_concurrent_access() {
    const int numThreads = 10;
    const int iterations = 1000;
    
    std::vector<std::thread> threads;
    
    for (int i = 0; i < numThreads; i++) {
        threads.emplace_back([i, iterations]() {
            for (int j = 0; j < iterations; j++) {
                int value = i * 1000 + j;
                int obfuscated = FEEL(value);
                assert(obfuscated == value);
                
                std::string str = "thread_" + std::to_string(i) + "_iter_" + std::to_string(j);
                std::string obfStr = FEEL(str);
                assert(obfStr == str);
            }
        });
    }
    
    for (auto& thread : threads) {
        thread.join();
    }
    
    std::cout << "✓ Concurrent access test passed" << std::endl;
}

int main() {
    std::cout << "=== Running Unit Tests ===" << std::endl;
    
    test_string_obfuscation();
    test_int_obfuscation();
    test_float_obfuscation();
    test_array_obfuscation();
    test_struct_obfuscation();
    test_type_detection();
    test_cache_functionality();
    test_concurrent_access();
    
    std::cout << "\n=== All tests passed! ===" << std::endl;
    return 0;
}
