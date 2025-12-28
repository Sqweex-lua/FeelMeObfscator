#include "FeelMeHappy.h"
#include <iostream>
#include <vector>

class SecureApplication {
private:
    const char* m_apiKey = FEEL("sk_live_1234567890abcdef");
    const char* m_dbUrl = FEEL("mysql://user:pass@localhost/db");
    int m_port = FEEL(8080);
    
public:
    void printConfig() {
        std::cout << "API Key: " << m_apiKey << std::endl;
        std::cout << "DB URL: " << m_dbUrl << std::endl;
        std::cout << "Port: " << m_port << std::endl;
    }
};

class APIClient {
private:
    const char* endpoints[3] = {
        FEEL("https://api.service.com/login"),
        FEEL("https://api.service.com/data"),
        FEEL("https://api.service.com/upload")
    };
    
public:
    void makeRequest(int endpoint) {
        std::cout << "Calling: " << endpoints[endpoint] << std::endl;
    }
};

template<typename T>
class Obfuscated {
private:
    T m_value;
    
public:
    Obfuscated(T value) : m_value(FEEL(value)) {}
    
    T get() const { return m_value; }
    
    operator T() const { return get(); }
};

int main() {
    std::cout << "=== Advanced Usage Examples ===" << std::endl;
    
    SecureApplication app;
    app.printConfig();
    
    APIClient client;
    client.makeRequest(0);
    
    Obfuscated<std::string> secretToken("my_secret_token_xyz");
    std::cout << "Token: " << secretToken.get() << std::endl;
    
    const char* sql = FEEL("SELECT * FROM users WHERE active = 1");
    std::cout << "SQL: " << sql << std::endl;
    
    const char* json = FEEL(R"({"name": "John", "age": 30})");
    std::cout << "JSON: " << json << std::endl;
    
    const char* xml = FEEL("<config><server>localhost</server></config>");
    std::cout << "XML: " << xml << std::endl;
    
    const char* code = FEEL(R"(
        #include <iostream>
        int main() {
            return 0;
        }
    )");
    std::cout << "Code sample hidden" << std::endl;
    
    std::vector<std::string> secrets = {
        FEEL(std::string("secret1")),
        FEEL(std::string("secret2")),
        FEEL(std::string("secret3"))
    };
    
    for (const auto& secret : secrets) {
        std::cout << "Vector secret: " << secret << std::endl;
    }
    
    return 0;
}
