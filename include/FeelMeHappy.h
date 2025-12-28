/*
FeelMeHappy.h - Универсальный обфускатор с одним макросом FEEL
Автор: AI Assistant
Версия: 5.0 Universal
*/

#ifndef FEELMEHAPPY_H
#define FEELMEHAPPY_H

#include <cstdint>
#include <cstddef>
#include <type_traits>
#include <cstring>
#include <ctime>
#include <cstdlib>
#include <atomic>
#include <random>
#include <thread>
#include <chrono>
#include <vector>
#include <memory>
#include <algorithm>
#include <functional>
#include <string>
#include <mutex>
#include <condition_variable>
#include <array>
#include <unordered_map>
#include <sstream>
#include <iomanip>
#include <codecvt>
#include <locale>
#include <regex>

// Определение платформы
#if defined(_WIN32) || defined(_WIN64)
    #define FEELMEHAPPY_WINDOWS
    #include <windows.h>
#elif defined(__ANDROID__)
    #define FEELMEHAPPY_ANDROID
    #include <jni.h>
    #include <sys/mman.h>
    #include <unistd.h>
    #include <android/log.h>
#elif defined(__linux__)
    #define FEELMEHAPPY_LINUX
    #include <sys/mman.h>
    #include <unistd.h>
#elif defined(__APPLE__)
    #define FEELMEHAPPY_MACOS
    #include <sys/mman.h>
    #include <mach/vm_map.h>
    #include <mach/mach_init.h>
    #include <mach/mach_vm.h>
#endif

// Определение архитектуры
#if defined(__x86_64__) || defined(_M_X64)
    #define FEELMEHAPPY_X64
#elif defined(__i386__) || defined(_M_IX86)
    #define FEELMEHAPPY_X86
#elif defined(__aarch64__) || defined(_M_ARM64)
    #define FEELMEHAPPY_ARM64
#elif defined(__arm__) || defined(_M_ARM)
    #define FEELMEHAPPY_ARM
#endif

#ifdef _MSC_VER
    #define FEELMEHAPPY_FORCEINLINE __forceinline
    #define FEELMEHAPPY_NOINLINE __declspec(noinline)
#else
    #define FEELMEHAPPY_FORCEINLINE __attribute__((always_inline)) inline
    #define FEELMEHAPPY_NOINLINE __attribute__((noinline))
#endif

// ==================== УНИВЕРСАЛЬНЫЙ МАКРОС FEEL ====================

#ifdef _DEBUG
    // Режим отладки - без обфускации
    #define FEEL(...) __VA_ARGS__
#else
    // Релиз режим - автоматическая обфускация всего
    #define FEEL(...) _feel_me_happy_::UniversalObfuscator::obfuscate(__VA_ARGS__)
#endif

namespace _feel_me_happy_ {

// Базовые типы
using Byte = uint8_t;
using Word = uint16_t;
using DWord = uint32_t;
using QWord = uint64_t;
using Size = size_t;

// Детектор типов
class TypeDetector {
public:
    enum class DataType {
        Unknown,
        CString,
        WideString,
        StdString,
        StdWString,
        Integer,
        Float,
        Double,
        Boolean,
        Pointer,
        Array,
        Struct,
        Char,
        ByteArray,
        Path,
        URL,
        Email,
        IP,
        Hex,
        Base64,
        DateTime,
        UUID,
        JSON,
        XML,
        SQL,
        Code,
        Binary
    };

    // Определение типа данных
    template<typename T>
    static DataType detect(const T& value) {
        if constexpr (std::is_same_v<T, char*> || std::is_same_v<T, const char*>) {
            return analyzeCString(value);
        } else if constexpr (std::is_same_v<T, wchar_t*> || std::is_same_v<T, const wchar_t*>) {
            return DataType::WideString;
        } else if constexpr (std::is_same_v<T, std::string>) {
            return analyzeStdString(value);
        } else if constexpr (std::is_same_v<T, std::wstring>) {
            return DataType::StdWString;
        } else if constexpr (std::is_integral_v<T>) {
            return DataType::Integer;
        } else if constexpr (std::is_floating_point_v<T>) {
            return DataType::Float;
        } else if constexpr (std::is_pointer_v<T>) {
            return DataType::Pointer;
        } else if constexpr (std::is_array_v<T>) {
            return DataType::Array;
        } else {
            return DataType::Struct;
        }
    }

private:
    static DataType analyzeCString(const char* str) {
        if (!str) return DataType::Unknown;
        
        std::string s(str);
        
        // Проверка на пути
        if (s.find("/") != std::string::npos || 
            s.find("\\") != std::string::npos ||
            s.find(".") != std::string::npos && 
            (s.find(".cpp") != std::string::npos ||
             s.find(".h") != std::string::npos ||
             s.find(".exe") != std::string::npos ||
             s.find(".dll") != std::string::npos)) {
            return DataType::Path;
        }
        
        // Проверка на URL
        if (s.find("http://") == 0 || s.find("https://") == 0 ||
            s.find("ftp://") == 0 || s.find("file://") == 0) {
            return DataType::URL;
        }
        
        // Проверка на email
        static std::regex email_regex(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
        if (std::regex_match(s, email_regex)) {
            return DataType::Email;
        }
        
        // Проверка на IP
        static std::regex ip_regex(R"((\d{1,3}\.){3}\d{1,3})");
        if (std::regex_match(s, ip_regex)) {
            return DataType::IP;
        }
        
        // Проверка на hex
        static std::regex hex_regex(R"(^[0-9a-fA-F]+$)");
        if (std::regex_match(s, hex_regex)) {
            return DataType::Hex;
        }
        
        // Проверка на base64
        static std::regex base64_regex(R"(^[A-Za-z0-9+/]+={0,2}$)");
        if (s.length() % 4 == 0 && std::regex_match(s, base64_regex)) {
            return DataType::Base64;
        }
        
        // Проверка на SQL
        std::string lower = s;
        std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
        if (lower.find("select ") != std::string::npos ||
            lower.find("insert ") != std::string::npos ||
            lower.find("update ") != std::string::npos ||
            lower.find("delete ") != std::string::npos ||
            lower.find("create ") != std::string::npos ||
            lower.find("drop ") != std::string::npos) {
            return DataType::SQL;
        }
        
        // Проверка на JSON/XML
        if ((s.find("{") != std::string::npos && s.find("}") != std::string::npos) ||
            (s.find("[") != std::string::npos && s.find("]") != std::string::npos)) {
            return DataType::JSON;
        }
        
        if (s.find("<?xml") != std::string::npos || 
            s.find("<") != std::string::npos && s.find(">") != std::string::npos) {
            return DataType::XML;
        }
        
        // Проверка на код
        if (s.find("#include") != std::string::npos ||
            s.find("int ") != std::string::npos ||
            s.find("void ") != std::string::npos ||
            s.find("return ") != std::string::npos ||
            s.find("if (") != std::string::npos ||
            s.find("for (") != std::string::npos ||
            s.find("while (") != std::string::npos) {
            return DataType::Code;
        }
        
        return DataType::CString;
    }
    
    static DataType analyzeStdString(const std::string& s) {
        // Аналогично анализу C-строк
        return analyzeCString(s.c_str());
    }
};

// Генератор случайных ключей
class KeyGenerator {
private:
    static std::mt19937_64 engine;
    static std::mutex mutex;
    
public:
    static Byte generateByte() {
        std::lock_guard<std::mutex> lock(mutex);
        return static_cast<Byte>(engine() & 0xFF);
    }
    
    static Word generateWord() {
        std::lock_guard<std::mutex> lock(mutex);
        return static_cast<Word>(engine() & 0xFFFF);
    }
    
    static DWord generateDWord() {
        std::lock_guard<std::mutex> lock(mutex);
        return static_cast<DWord>(engine() & 0xFFFFFFFF);
    }
    
    static QWord generateQWord() {
        std::lock_guard<std::mutex> lock(mutex);
        return engine();
    }
    
    static void generateBytes(Byte* buffer, Size size) {
        std::lock_guard<std::mutex> lock(mutex);
        for (Size i = 0; i < size; ++i) {
            buffer[i] = static_cast<Byte>(engine() & 0xFF);
        }
    }
};

std::mt19937_64 KeyGenerator::engine(std::random_device{}());
std::mutex KeyGenerator::mutex;

// Алгоритмы обфускации
class ObfuscationAlgorithms {
public:
    // XOR обфускация
    template<typename T>
    static T xorObfuscate(const T& data, Byte key) {
        T result = data;
        Byte* bytes = reinterpret_cast<Byte*>(&result);
        for (Size i = 0; i < sizeof(T); ++i) {
            bytes[i] ^= key ^ (i * 0x9E);
        }
        return result;
    }
    
    // ADD обфускация
    template<typename T>
    static T addObfuscate(const T& data, Byte key) {
        T result = data;
        Byte* bytes = reinterpret_cast<Byte*>(&result);
        for (Size i = 0; i < sizeof(T); ++i) {
            bytes[i] += key + i;
        }
        return result;
    }
    
    // ROL обфускация
    template<typename T>
    static T rolObfuscate(const T& data, Byte bits) {
        if constexpr (sizeof(T) == 1) {
            return (data << bits) | (data >> (8 - bits));
        } else if constexpr (sizeof(T) == 2) {
            return (data << bits) | (data >> (16 - bits));
        } else if constexpr (sizeof(T) == 4) {
            return (data << bits) | (data >> (32 - bits));
        } else if constexpr (sizeof(T) == 8) {
            return (data << bits) | (data >> (64 - bits));
        }
        return data;
    }
    
    // ROR обфускация
    template<typename T>
    static T rorObfuscate(const T& data, Byte bits) {
        if constexpr (sizeof(T) == 1) {
            return (data >> bits) | (data << (8 - bits));
        } else if constexpr (sizeof(T) == 2) {
            return (data >> bits) | (data << (16 - bits));
        } else if constexpr (sizeof(T) == 4) {
            return (data >> bits) | (data << (32 - bits));
        } else if constexpr (sizeof(T) == 8) {
            return (data >> bits) | (data << (64 - bits));
        }
        return data;
    }
    
    // NOT обфускация
    template<typename T>
    static T notObfuscate(const T& data) {
        return ~data;
    }
    
    // Комбинированная обфускация для строк
    static std::string obfuscateString(const std::string& str, Byte key) {
        std::string result = str;
        for (Size i = 0; i < result.size(); ++i) {
            result[i] ^= key ^ (i * 0x37);
            result[i] += (i % 0xFF);
            result[i] = (result[i] << 3) | (result[i] >> 5);
        }
        return result;
    }
    
    static std::wstring obfuscateWString(const std::wstring& str, Byte key) {
        std::wstring result = str;
        for (Size i = 0; i < result.size(); ++i) {
            result[i] ^= key ^ (i * 0x37);
            result[i] += (i % 0xFFFF);
            result[i] = (result[i] << 3) | (result[i] >> 13);
        }
        return result;
    }
};

// Кэш обфусцированных данных
template<typename Key, typename Value>
class ObfuscationCache {
private:
    struct CacheEntry {
        Value data;
        std::chrono::steady_clock::time_point timestamp;
        Byte key;
    };
    
    std::unordered_map<Key, CacheEntry> cache;
    std::mutex mutex;
    const std::chrono::minutes cacheDuration{15};
    
public:
    void clear() {
        std::lock_guard<std::mutex> lock(mutex);
        cache.clear();
    }
    
    bool get(const Key& key, Value& value, Byte& storedKey) {
        std::lock_guard<std::mutex> lock(mutex);
        auto it = cache.find(key);
        if (it != cache.end()) {
            auto now = std::chrono::steady_clock::now();
            if (now - it->second.timestamp < cacheDuration) {
                value = it->second.data;
                storedKey = it->second.key;
                return true;
            }
            cache.erase(it);
        }
        return false;
    }
    
    void put(const Key& key, const Value& value, Byte obfKey) {
        std::lock_guard<std::mutex> lock(mutex);
        CacheEntry entry{value, std::chrono::steady_clock::now(), obfKey};
        cache[key] = entry;
        
        // Очистка старых записей
        auto now = std::chrono::steady_clock::now();
        for (auto it = cache.begin(); it != cache.end(); ) {
            if (now - it->second.timestamp > cacheDuration) {
                it = cache.erase(it);
            } else {
                ++it;
            }
        }
    }
    
    void invalidate(const Key& key) {
        std::lock_guard<std::mutex> lock(mutex);
        cache.erase(key);
    }
    
    Size size() const {
        std::lock_guard<std::mutex> lock(mutex);
        return cache.size();
    }
};

// Генератор случайных функций
class FunctionGenerator {
private:
    struct GeneratedFunction {
        void* address;
        Size size;
        std::string name;
    };
    
    std::vector<GeneratedFunction> functions;
    std::mutex mutex;
    std::atomic<bool> running{false};
    std::thread generatorThread;
    
public:
    FunctionGenerator() {
        running = true;
        generatorThread = std::thread([this]() {
            generationWorker();
        });
    }
    
    ~FunctionGenerator() {
        running = false;
        if (generatorThread.joinable()) {
            generatorThread.join();
        }
        cleanup();
    }
    
private:
    void generationWorker() {
        while (running) {
            std::this_thread::sleep_for(std::chrono::minutes(15));
            
            // Генерируем от 100 до 500 функций
            Size count = 100 + (KeyGenerator::generateByte() % 401);
            
            std::lock_guard<std::mutex> lock(mutex);
            cleanup();
            
            for (Size i = 0; i < count; ++i) {
                generateRandomFunction();
            }
        }
    }
    
    void generateRandomFunction() {
#ifdef FEELMEHAPPY_WINDOWS
        Size size = 64 + (KeyGenerator::generateByte() % 193);
        void* memory = VirtualAlloc(nullptr, size, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
        if (memory) {
            // Заполняем случайными байтами
            Byte* bytes = static_cast<Byte*>(memory);
            for (Size i = 0; i < size; ++i) {
                bytes[i] = KeyGenerator::generateByte();
            }
            
            // Делаем исполняемым
            DWORD oldProtect;
            VirtualProtect(memory, size, PAGE_EXECUTE_READ, &oldProtect);
            
            functions.push_back({memory, size, "func_" + std::to_string(functions.size())});
        }
#endif
    }
    
    void cleanup() {
        for (const auto& func : functions) {
#ifdef FEELMEHAPPY_WINDOWS
            VirtualFree(func.address, 0, MEM_RELEASE);
#endif
        }
        functions.clear();
    }
};

// Основной класс обфускатора
class UniversalObfuscator {
private:
    static UniversalObfuscator* instance;
    static std::mutex instanceMutex;
    
    ObfuscationCache<std::string, std::string> stringCache;
    ObfuscationCache<std::wstring, std::wstring> wstringCache;
    ObfuscationCache<QWord, QWord> intCache;
    ObfuscationCache<QWord, double> floatCache;
    std::unique_ptr<FunctionGenerator> funcGenerator;
    std::atomic<Byte> currentKey{0x37};
    
    std::thread keyRotator;
    std::atomic<bool> running{false};
    
    UniversalObfuscator() {
        currentKey = KeyGenerator::generateByte();
        running = true;
        funcGenerator = std::make_unique<FunctionGenerator>();
        
        // Поток для смены ключа каждые 15 минут
        keyRotator = std::thread([this]() {
            while (running) {
                std::this_thread::sleep_for(std::chrono::minutes(15));
                rotateKey();
                clearCaches();
            }
        });
    }
    
    ~UniversalObfuscator() {
        running = false;
        if (keyRotator.joinable()) {
            keyRotator.join();
        }
    }
    
    void rotateKey() {
        currentKey = KeyGenerator::generateByte();
    }
    
    void clearCaches() {
        stringCache.clear();
        wstringCache.clear();
        intCache.clear();
        floatCache.clear();
    }
    
public:
    static UniversalObfuscator& getInstance() {
        std::lock_guard<std::mutex> lock(instanceMutex);
        if (!instance) {
            instance = new UniversalObfuscator();
        }
        return *instance;
    }
    
    static void destroy() {
        std::lock_guard<std::mutex> lock(instanceMutex);
        if (instance) {
            delete instance;
            instance = nullptr;
        }
    }
    
    // Универсальный метод обфускации
    template<typename T>
    static auto obfuscate(const T& value) -> T {
        auto& inst = getInstance();
        Byte key = inst.currentKey.load();
        
        // Определяем тип данных
        auto dataType = TypeDetector::detect(value);
        
        // Применяем соответствующую обфускацию
        if constexpr (std::is_same_v<T, const char*> || std::is_same_v<T, char*>) {
            return inst.obfuscateCString(value, dataType, key);
        } else if constexpr (std::is_same_v<T, const wchar_t*> || std::is_same_v<T, wchar_t*>) {
            return inst.obfuscateWString(value, key);
        } else if constexpr (std::is_same_v<T, std::string>) {
            return inst.obfuscateStdString(value, dataType, key);
        } else if constexpr (std::is_same_v<T, std::wstring>) {
            return inst.obfuscateStdWString(value, key);
        } else if constexpr (std::is_integral_v<T>) {
            return inst.obfuscateInteger(value, key);
        } else if constexpr (std::is_floating_point_v<T>) {
            return inst.obfuscateFloat(value, key);
        } else if constexpr (std::is_pointer_v<T>) {
            return inst.obfuscatePointer(value, key);
        } else if constexpr (std::is_array_v<T>) {
            return inst.obfuscateArray(value, std::extent_v<T>, key);
        } else {
            // Для структур и классов
            return inst.obfuscateStruct(value, key);
        }
    }
    
private:
    // Методы обфускации для разных типов
    
    const char* obfuscateCString(const char* str, TypeDetector::DataType type, Byte key) {
        if (!str) return nullptr;
        
        std::string keyStr = str;
        std::string cached;
        Byte cachedKey;
        
        if (stringCache.get(keyStr, cached, cachedKey)) {
            return cached.c_str();
        }
        
        std::string result = str;
        
        // Применяем обфускацию в зависимости от типа
        switch (type) {
            case TypeDetector::DataType::Path:
            case TypeDetector::DataType::URL:
            case TypeDetector::DataType::Email:
            case TypeDetector::DataType::IP:
            case TypeDetector::DataType::SQL:
            case TypeDetector::DataType::Code:
                // Для критических данных усиленная обфускация
                result = ObfuscationAlgorithms::obfuscateString(result, key);
                result = ObfuscationAlgorithms::obfuscateString(result, key ^ 0xAA);
                break;
                
            default:
                // Стандартная обфускация
                result = ObfuscationAlgorithms::obfuscateString(result, key);
                break;
        }
        
        stringCache.put(keyStr, result, key);
        return stringCache.get(keyStr, cached, cachedKey) ? cached.c_str() : result.c_str();
    }
    
    const wchar_t* obfuscateWString(const wchar_t* str, Byte key) {
        if (!str) return nullptr;
        
        std::wstring keyStr = str;
        std::wstring cached;
        Byte cachedKey;
        
        if (wstringCache.get(keyStr, cached, cachedKey)) {
            return cached.c_str();
        }
        
        std::wstring result = str;
        result = ObfuscationAlgorithms::obfuscateWString(result, key);
        
        wstringCache.put(keyStr, result, key);
        return wstringCache.get(keyStr, cached, cachedKey) ? cached.c_str() : result.c_str();
    }
    
    std::string obfuscateStdString(const std::string& str, TypeDetector::DataType type, Byte key) {
        std::string cached;
        Byte cachedKey;
        
        if (stringCache.get(str, cached, cachedKey)) {
            return cached;
        }
        
        std::string result = str;
        
        switch (type) {
            case TypeDetector::DataType::Path:
            case TypeDetector::DataType::URL:
            case TypeDetector::DataType::Email:
            case TypeDetector::DataType::IP:
            case TypeDetector::DataType::SQL:
            case TypeDetector::DataType::Code:
                result = ObfuscationAlgorithms::obfuscateString(result, key);
                result = ObfuscationAlgorithms::obfuscateString(result, key ^ 0x55);
                break;
                
            default:
                result = ObfuscationAlgorithms::obfuscateString(result, key);
                break;
        }
        
        stringCache.put(str, result, key);
        return result;
    }
    
    std::wstring obfuscateStdWString(const std::wstring& str, Byte key) {
        std::wstring cached;
        Byte cachedKey;
        
        if (wstringCache.get(str, cached, cachedKey)) {
            return cached;
        }
        
        std::wstring result = str;
        result = ObfuscationAlgorithms::obfuscateWString(result, key);
        
        wstringCache.put(str, result, key);
        return result;
    }
    
    template<typename T>
    T obfuscateInteger(T value, Byte key) {
        QWord keyVal = static_cast<QWord>(value);
        QWord cached;
        Byte cachedKey;
        
        if (intCache.get(keyVal, cached, cachedKey)) {
            return static_cast<T>(cached);
        }
        
        T result = value;
        
        // Комбинированная обфускация для целых чисел
        result = ObfuscationAlgorithms::xorObfuscate(result, key);
        result = ObfuscationAlgorithms::rolObfuscate(result, key % (sizeof(T) * 8));
        result = ObfuscationAlgorithms::addObfuscate(result, key);
        
        intCache.put(keyVal, static_cast<QWord>(result), key);
        return result;
    }
    
    template<typename T>
    T obfuscateFloat(T value, Byte key) {
        QWord keyVal;
        std::memcpy(&keyVal, &value, sizeof(T));
        
        double cached;
        Byte cachedKey;
        
        if (floatCache.get(keyVal, cached, cachedKey)) {
            return static_cast<T>(cached);
        }
        
        // Обфускация через целочисленное представление
        using IntType = typename std::conditional<sizeof(T) == 4, DWord, QWord>::type;
        IntType intValue;
        std::memcpy(&intValue, &value, sizeof(T));
        
        IntType obfuscatedInt = obfuscateInteger(intValue, key);
        
        T result;
        std::memcpy(&result, &obfuscatedInt, sizeof(T));
        
        QWord resultKey;
        std::memcpy(&resultKey, &result, sizeof(T));
        floatCache.put(keyVal, static_cast<double>(result), key);
        
        return result;
    }
    
    template<typename T>
    T* obfuscatePointer(T* ptr, Byte key) {
        if (!ptr) return nullptr;
        
        // Обфускация указателя через целочисленное представление
        uintptr_t intPtr = reinterpret_cast<uintptr_t>(ptr);
        uintptr_t obfuscated = obfuscateInteger(intPtr, key);
        
        return reinterpret_cast<T*>(obfuscated);
    }
    
    template<typename T, Size N>
    T* obfuscateArray(T (&arr)[N], Byte key) {
        for (Size i = 0; i < N; ++i) {
            arr[i] = obfuscate(arr[i]);
        }
        return arr;
    }
    
    template<typename T>
    T obfuscateStruct(const T& value, Byte key) {
        T result = value;
        Byte* bytes = reinterpret_cast<Byte*>(&result);
        
        // Обфускация каждого байта структуры
        for (Size i = 0; i < sizeof(T); ++i) {
            bytes[i] ^= key ^ (i * 0x9E);
            bytes[i] += (i % 0xFF);
            bytes[i] = (bytes[i] << 4) | (bytes[i] >> 4);
        }
        
        return result;
    }
};

UniversalObfuscator* UniversalObfuscator::instance = nullptr;
std::mutex UniversalObfuscator::instanceMutex;

} // namespace _feel_me_happy_

static struct FeelInitializer {
    FeelInitializer() {
    }
    ~FeelInitializer() {
        _feel_me_happy_::UniversalObfuscator::destroy();
    }
} feelInit;

#endif // FEELMEHAPPY_H
