# FeelMeHappy Obfuscator

[![Build Status](https://github.com/sqweeex-lua/FeelMeObfscator/workflows/Build/badge.svg)](https://github.com/sqweex-lua/FeelMeObfscator/actions)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![C++17](https://img.shields.io/badge/C++-17-blue.svg)](https://en.cppreference.com/w/cpp/17)

One macro to obfuscate them all. `FEEL()` automatically protects your strings, numbers, paths, and secrets.

## Features

- 🎯 **Single macro** `FEEL()` for everything
- 🔄 **Dynamic key rotation** every 15 minutes
- ⚡ **High performance** with caching
- 🔒 **Multiple obfuscation algorithms**
- 📱 **Cross-platform** (Windows, Linux, macOS, Android)
- 🧵 **Thread-safe** design

## Quick Start

```cpp
#include "FeelMeHappy.h"

int main() {
    const char* apiKey = FEEL("test123");
    const char* dbUrl = FEEL("mysql://user:pass@localhost/db");
    int port = FEEL(8080);
    const char* endpoint = FEEL("https://api.example.com/");
    
    return 0;
}
```
## C++ Standards

    C++17 (minimum)

    C++20 (recommended)

    C++23 (future)

## Compiler Support

GCC	7.0+	Full support
Clang	6.0+	Full support
MSVC	2017+	Full support
ICC	19.0+	Partial support
