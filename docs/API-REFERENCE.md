# FeelMeHappy API Reference

## Table of Contents
1. [Macros](#macros)
2. [Types](#types)
3. [Classes](#classes)
4. [Functions](#functions)
5. [Configuration](#configuration)

## Macros

### `FEEL(value)`
Main obfuscation macro. Works with any data type.

```cpp
const char* str = FEEL("Hello");
int num = FEEL(42);
float f = FEEL(3.14f);
