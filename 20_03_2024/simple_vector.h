#pragma once

#include <cstdlib>
#include <algorithm> // for std::copy

template <typename T>
class SimpleVector {
public:
    SimpleVector() : data(nullptr), size(0), capacity(0) {}
    explicit SimpleVector(size_t size) : data(new T[size]), size(size), capacity(size) {}
    ~SimpleVector() { delete[] data; }

    T& operator[](size_t index) { return data[index]; }

    T* begin() { return data; }
    T* end() { return data + size; }

    size_t Size() const { return size; }
    size_t Capacity() const { return capacity; }

    void PushBack(const T& value) {
        if (size >= capacity) {
            size_t new_capacity = capacity == 0 ? 1 : capacity * 2;
            T* new_data = new T[new_capacity];
            std::copy(data, data + size, new_data);
            delete[] data;
            data = new_data;
            capacity = new_capacity;
        }
        data[size++] = value;
    }

private:
    T* data;
    size_t size;
    size_t capacity;
};
