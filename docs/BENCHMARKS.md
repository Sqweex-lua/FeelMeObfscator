# Performance Benchmarks

## Test Environment
- CPU: Intel Core i7-11800H 2.3GHz (8 cores, 16 threads)
- RAM: 16GB DDR4 3200MHz
- OS: Ubuntu 22.04 LTS
- Compiler: GCC 11.3.0
- Build: Release mode (-O3)

## String Obfuscation Performance

| String Length | Operations/sec | Memory Usage | Time per 1M ops |
|---------------|----------------|--------------|-----------------|
| 16 bytes      | 2,450,000      | 0.5 MB       | 408 ms          |
| 64 bytes      | 1,820,000      | 2.0 MB       | 549 ms          |
| 256 bytes     | 1,210,000      | 8.0 MB       | 826 ms          |
| 1024 bytes    | 640,000        | 32 MB        | 1,562 ms        |
| 4096 bytes    | 210,000        | 128 MB       | 4,761 ms        |

## Integer Obfuscation Performance

| Data Type | Operations/sec | Speed vs Native | Cache Hits |
|-----------|----------------|-----------------|------------|
| int8_t    | 10,200,000     | 98%             | 99.9%      |
| int16_t   | 9,800,000      | 97%             | 99.9%      |
| int32_t   | 9,500,000      | 96%             | 99.8%      |
| int64_t   | 9,100,000      | 95%             | 99.8%      |
| uint8_t   | 10,100,000     | 97%             | 99.9%      |
| uint64_t  | 9,000,000      | 94%             | 99.7%      |

## Float Obfuscation Performance

| Data Type | Operations/sec | Speed vs Native | Precision Loss |
|-----------|----------------|-----------------|----------------|
| float     | 8,400,000      | 94%             | 0%             |
| double    | 7,900,000      | 92%             | 0%             |

## Cache Performance

| Cache Size | Hit Rate | Operations/sec | Memory Overhead |
|------------|----------|----------------|-----------------|
| 100 entries    | 99.8%    | 850,000        | 5 KB            |
| 1,000 entries  | 99.5%    | 820,000        | 50 KB           |
| 10,000 entries | 98.2%    | 780,000        | 500 KB          |
| 100,000 entries| 95.7%    | 710,000        | 5 MB            |

## Concurrent Performance Scaling

| Threads | Operations/sec | Scaling Factor | CPU Usage |
|---------|----------------|----------------|-----------|
| 1       | 2,100,000      | 1.00x          | 12%       |
| 2       | 3,900,000      | 1.86x          | 24%       |
| 4       | 7,200,000      | 3.43x          | 45%       |
| 8       | 12,800,000     | 6.10x          | 78%       |
| 16      | 18,400,000     | 8.76x          | 95%       |

## Memory Usage Analysis

### Static Memory Footprint
