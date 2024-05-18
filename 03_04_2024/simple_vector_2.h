#include <cstdint>
#include <algorithm> // для std::copy, std::move
#include <iostream> // для отладочного вывода

using namespace std;

template <typename T>
class SimpleVector {
public:
    SimpleVector() = default;
    explicit SimpleVector(size_t size)
        : size_(size),
          capacity_(size),
          data_(new T[size]) {}

    ~SimpleVector() {
        delete[] data_;
    }

    T& operator[](size_t index) {
        return data_[index];
    }

    T* begin() {
        return data_;
    }

    T* end() {
        return data_ + size_;
    }

    size_t Size() const {
        return size_;
    }

    size_t Capacity() const {
        return capacity_;
    }

    void PushBack(const T& value) {
        if (size_ >= capacity_) {
            // Увеличиваем capacity_
            auto new_capacity = capacity_ == 0 ? 1 : 2 * capacity_;
            reserve(new_capacity);
        }
        data_[size_++] = value;
    }

    // При необходимости перегрузите
    // существующие публичные методы

private:
    size_t size_ = 0;
    size_t capacity_ = 0;
    T* data_ = nullptr;

    // Увеличение емкости вектора до указанного значения
    void reserve(size_t new_capacity) {
        if (new_capacity <= capacity_) return;
        
        auto new_data = new T[new_capacity];
        // Перемещаем элементы из старого массива в новый
        for (size_t i = 0; i < size_; ++i) {
            new_data[i] = std::move(data_[i]);
        }
        delete[] data_;
        data_ = new_data;
        capacity_ = new_capacity;
    }
};
