# Bare-Metal C++ Dynamic Array (`darray`)

A custom, dependency-free dynamic array built from scratch in C++.

**The Origin Story:** This project was initially just supposed to be a basic dynamic array implementation inspired by watching **Tsoding**, but it rapidly evolved into a fully weaponized data structure. It bridges the gap between Python's high-level comfort (methods like `append`, `pop`, and `insert`) and raw C++ memory mechanics (manual `malloc`/`realloc`, pointer arithmetic, and the Rule of Three).

## 🚀 Features

* **Pythonic API in C++:** Includes forgiving methods like `insert()`, `remove()`, `pop(index)`, `extend()`, and `count()`.
* **Zero-Allocation QuickSort:** Features a custom, in-place QuickSort engine built entirely on raw pointer arithmetic (`int* l`, `int* r`) for blisteringly fast $O(N \log N)$ sorting without memory bloat.
* **Geometric Memory Expansion:** Automatically scales memory capacity to avoid $O(N)$ reallocation traps.
* **Memory Safe:** Fully implements the C++ **Rule of Three** (Destructor, Copy Constructor, Copy Assignment Operator) to prevent memory leaks and double-free crashes.
* **Built-in Debugger:** Includes a `debugprint()` method to instantly view capacity, item count, and raw byte footprint.

## 🚧 Current Limitations

While this class mimics Python's `list`, it is strictly a data container, not a math vector. It does **not** currently support element-wise or vectorized array operations.

* For example, doing `a[1, 2, 3] + b[1, 1, 1]` will not yield `[2, 3, 4]`.

## 🗺️ Roadmap

The engine is mathematically sound, but there is still room to grow. Future updates will focus on:

* **Phase 1: Mono-Type Dynamics (Templates):** Refactoring the class using C++ templates (`<typename T>`) so it isn't hardcoded to `int`. It will be able to store arrays of `float`, `std::string`, or custom structs.
* **Phase 2: True Dynamic List:** Pushing the boundaries of C++ to support heterogeneous data types in a single array (e.g., storing an `int`, a `string`, and a `float` right next to each other), achieving true parity with Python lists.

* Here is the updated `README.md` with the massive code block removed. The Quick Start section now features a clean, minimal usage example followed by a professional API reference detailing exactly what your public methods do.

---

# Bare-Metal C++ Dynamic Array (`darray`)

A custom, dependency-free dynamic array built from scratch in C++.

**The Origin Story:** This project was initially just supposed to be a basic dynamic array implementation inspired by watching **Tsoding**, but it rapidly evolved into a fully weaponized data structure. It bridges the gap between Python's high-level comfort (methods like `append`, `pop`, and `insert`) and raw C++ memory mechanics (manual `malloc`/`realloc`, pointer arithmetic, and the Rule of Three).

## 🚀 Features

* **Pythonic API in C++:** Includes forgiving methods like `insert()`, `remove()`, `pop(index)`, `extend()`, and `count()`.
* **Zero-Allocation QuickSort:** Features a custom, in-place QuickSort engine built entirely on raw pointer arithmetic (`int* l`, `int* r`) for blisteringly fast $O(N \log N)$ sorting without memory bloat.
* **Geometric Memory Expansion:** Automatically scales memory capacity to avoid $O(N)$ reallocation traps.
* **Memory Safe:** Fully implements the C++ **Rule of Three** (Destructor, Copy Constructor, Copy Assignment Operator) to prevent memory leaks and double-free crashes.
* **Built-in Debugger:** Includes a `debugprint()` method to instantly view capacity, item count, and raw byte footprint.

## 🚧 Current Limitations

While this class mimics Python's `list`, it is strictly a data container, not a math vector. It does **not** currently support element-wise or vectorized array operations.

* For example, doing `a[1, 2, 3] + b[1, 1, 1]` will not yield `[2, 3, 4]`.

## 🗺️ Roadmap

The engine is mathematically sound, but there is still room to grow. Future updates will focus on:

* **Phase 1: Mono-Type Dynamics (Templates):** Refactoring the class using C++ templates (`<typename T>`) so it isn't hardcoded to `int`. It will be able to store arrays of `float`, `std::string`, or custom structs.
* **Phase 2: True Dynamic List:** Pushing the boundaries of C++ to support heterogeneous data types in a single array (e.g., storing an `int`, a `string`, and a `float` right next to each other), achieving true parity with Python lists.

## 💻 Quick Start & Usage

Include the class in your project, initialize it, and use it just like a Python list.

```cpp
#include "darray.h" // Assuming you saved the class here

int main() {
    int initial_data[] = {15, 3, 9, 12};
    darray nums(initial_data);

    nums.append(42);
    nums.remove(9);
    nums.sort(true); // Sort descending

    nums.debugprint(); 
    // Output: darray stats: darr_count = 4, max capacity = 4, sizeof(head) = 16 bytes | [42, 15, 12, 3]
    
    return 0;
}

```

### 📚 API Reference

**Memory & Lifecycle (The Rule of Three)**

* `darray()`: Initializes an empty dynamic array with a default capacity of 1.
* `darray(int (&arr)[N])`: Template constructor that automatically detects the size of a raw C-array and safely copies it into the dynamic heap.
* `darray(const darray &other)`: Deep-copy constructor.
* `operator=(const darray& other)`: Safe assignment operator that prevents memory leaks when overwriting an existing `darray`.
* `clear()`: Instantly resets the item count to 0 and shrinks the heap capacity back to 1.
* `copysize(darray& arr, bool matchSlots)`: Resizes the underlying heap capacity to match another `darray`. If `matchSlots` is true, it automatically pads the array with `0`s to match the element count.

**List Operations (Pythonic API)**

* `append(int num)`: Pushes a number to the end of the array. Automatically doubles heap capacity if the array is full.
* `extend(const darray& array)`: Appends the entire contents of another `darray` to the end of this one, managing bulk reallocation automatically.
* `insert(int index, int item)`: Inserts a number at a specific index, shifting all subsequent elements to the right. Supports Python-style negative indexing.
* `remove(int item)`: Finds and deletes the **first** occurrence of a specific number, shifting subsequent elements left. Automatically shrinks heap capacity if utilization drops below 50%.
* `pop()`: Removes and returns the very last item in the array.
* `pop(int index)`: Removes and returns an item at a specific index. Supports negative indexing.

**Search & Sort**

* `sort(bool reversed=false)`: Triggers the internal raw-pointer QuickSort engine. Runs in-place in $O(N \log N)$ time.
* `reverse()`: Flips the array in-place using a two-pointer swap strategy.
* `index(int item)`: Scans the array and returns the index of the first occurrence of the item.
* `count(int item)`: Scans the array and returns the total number of times an item appears.

**Utilities**

* `copy()`: Returns a completely independent, deep-copied duplicate of the `darray`.
* `start()`: Returns the raw `int*` pointer to the underlying heap memory (useful for C-style iterations or raw memory manipulation).
* `zerout()`: Replaces all active elements in the array with `0` without altering the capacity or count.
* `debugprint()`: Prints a detailed diagnostic string to the console, including element count, maximum capacity, exact byte size on the heap, and the array contents.
