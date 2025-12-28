#include "FeelMeHappy.h"
#include <iostream>

int main() {
    std::cout << "=== Basic Usage Examples ===" << std::endl;
    
    const char* secret = FEEL("My secret API key");
    std::cout << "Secret: " << secret << std::endl;
    
    int configValue = FEEL(42);
    std::cout << "Config: " << configValue << std::endl;
    
    float pi = FEEL(3.14159f);
    std::cout << "Pi: " << pi << std::endl;
    
    const char* path = FEEL("/usr/local/bin/app");
    std::cout << "Path: " << path << std::endl;
    
    const char* url = FEEL("https://api.example.com/data");
    std::cout << "URL: " << url << std::endl;
    
    const char* email = FEEL("admin@example.com");
    std::cout << "Email: " << email << std::endl;
    
    const char* ip = FEEL("192.168.1.100");
    std::cout << "IP: " << ip << std::endl;
    
    std::string dynamic = FEEL(std::string("Dynamic string"));
    std::cout << "Dynamic: " << dynamic << std::endl;
    
    int numbers[] = {1, 2, 3, 4, 5};
    int* obfNumbers = FEEL(numbers);
    std::cout << "Numbers[0]: " << obfNumbers[0] << std::endl;
    
    struct Config {
        int id;
        char name[32];
    };
    
    Config config = {1, "test"};
    Config obfConfig = FEEL(config);
    std::cout << "Config ID: " << obfConfig.id << std::endl;
    
    return 0;
}
