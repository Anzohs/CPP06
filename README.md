# CPP06 — C++ Type Casting

## Overview

CPP06 is the sixth module of the C++ branch at 42 School. It focuses on **type casting** in C++, teaching how to convert values between different types safely and correctly. The module covers the four C++ cast operators and provides practical exercises to understand when and how to use each one.

---

## Key Concepts

### The Four C++ Cast Operators

| Operator | Purpose |
|---|---|
| `static_cast` | Safe compile-time cast between compatible types |
| `dynamic_cast` | Safe runtime cast for polymorphic class hierarchies |
| `reinterpret_cast` | Low-level, bit-level reinterpretation of a value |
| `const_cast` | Add or remove `const`/`volatile` qualifiers |

### Why Avoid C-Style Casts?

C-style casts (`(int)x`, `(float*)ptr`) are powerful but dangerous: they can silently perform unsafe conversions with no type checking. C++ cast operators are preferred because they are explicit about intent and provide compile-time or runtime safety checks.

---

## Exercises

### Exercise 00 — Scalar Conversion

**Goal:** Implement a class `ScalarConverter` with a single static method `convert(const std::string& literal)` that:

1. Detects the type of a scalar literal passed as a string (`char`, `int`, `float`, or `double`).
2. Converts it to all four scalar types and prints the results.

**Example output:**
```
$ ./convert 42
char: '*'
int: 42
float: 42.0f
double: 42.0
```

**Key points:**
- Handles special float/double literals: `nan`, `nanf`, `+inf`, `-inf`, `+inff`, `-inff`.
- Uses `static_cast` for conversions between numeric types.
- Must display a meaningful message (`impossible`) when a conversion is not representable (e.g., a `double` that is out of `int` range, or a non-printable character).

---

### Exercise 01 — Serialization

**Goal:** Implement a `Serializer` class with two static methods:

```cpp
uintptr_t serialize(Data* ptr);
Data*      deserialize(uintptr_t raw);
```

`serialize` converts a pointer to an integer (`uintptr_t`), and `deserialize` converts it back to a pointer. The key teaching point is `reinterpret_cast`, the only cast that can legally perform a pointer-to-integer conversion.

**Key points:**
- `reinterpret_cast<uintptr_t>(ptr)` converts a pointer to an unsigned integer of the same size.
- `reinterpret_cast<Data*>(raw)` converts it back, and the resulting pointer must be identical to the original.
- This pattern appears in serialization, inter-process communication, and hardware-level programming.

---

### Exercise 02 — Identify Real Type

**Goal:** Implement three empty classes with an inheritance chain and a function that identifies the actual runtime type of an object passed as a `Base*` pointer (or reference) — **without using `typeid`**.

```
Base
├── A
├── B
└── C
```

```cpp
Base* generate(void);       // randomly returns a new A, B, or C
void  identify(Base* p);    // prints "A", "B", or "C"
void  identify(Base& p);    // prints "A", "B", or "C"
```

**Key points:**
- Uses `dynamic_cast` to test the actual type at runtime.
- `dynamic_cast<A*>(p)` returns `nullptr` if `p` does not point to an `A` (or a derived class of `A`).
- `dynamic_cast<A&>(p)` throws `std::bad_cast` if the reference does not refer to an `A`.
- For `dynamic_cast` to work, the base class must be **polymorphic** (i.e., have at least one `virtual` function, typically a virtual destructor).

---

## Compilation

Each exercise has its own `Makefile`. A typical build:

```bash
cd ex00 && make
./convert <literal>

cd ex01 && make
./serializer

cd ex02 && make
./identifier
```

---

## Summary

| Exercise | Cast Used | Concept |
|---|---|---|
| 00 — Scalar Conversion | `static_cast` | Safe compile-time numeric/char conversions |
| 01 — Serialization | `reinterpret_cast` | Bit-level pointer/integer reinterpretation |
| 02 — Identify Real Type | `dynamic_cast` | Runtime polymorphic type identification |

CPP06 builds the intuition to choose the right cast for the right job, a fundamental skill for writing safe, expressive, and portable C++ code.
