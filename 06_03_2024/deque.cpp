#include <vector>
#include <stdexcept>

template <typename T>
class Deque {
public:
    Deque() = default;

    bool Empty() const {
        return front_.empty() && back_.empty();
    }

    size_t Size() const {
        return front_.size() + back_.size();
    }

    T& operator[](size_t index) {
        return const_cast<T&>(static_cast<const Deque&>(*this)[index]);
    }

    const T& operator[](size_t index) const {
        return At(index);
    }

    T& At(size_t index) {
        if (index >= Size()) {
            throw std::out_of_range("Index out of range");
        }
        return index < front_.size() ? front_[front_.size() - index - 1] : back_[index - front_.size()];
    }

    const T& At(size_t index) const {
        if (index >= Size()) {
            throw std::out_of_range("Index out of range");
        }
        return index < front_.size() ? front_[front_.size() - index - 1] : back_[index - front_.size()];
    }

    T& Front() {
        if (front_.empty()) {
            return back_.front();
        }
        return front_.back();
    }

    const T& Front() const {
        if (front_.empty()) {
            return back_.front();
        }
        return front_.back();
    }

    T& Back() {
        if (back_.empty()) {
            return front_.front();
        }
        return back_.back();
    }

    const T& Back() const {
        if (back_.empty()) {
            return front_.front();
        }
        return back_.back();
    }

    void PushFront(const T& value) {
        front_.push_back(value);
    }

    void PushBack(const T& value) {
        back_.push_back(value);
    }

private:
    std::vector<T> front_;
    std::vector<T> back_;
};

#include <iostream>

int main() {
    // Создание объекта Deque
    Deque<int> deque;

    // Проверка на пустоту
    std::cout << "Is deque empty? " << (deque.Empty() ? "Yes" : "No") << std::endl;

    // Добавление элементов
    deque.PushBack(1);
    deque.PushBack(2);
    deque.PushFront(0);

    // Проверка размера
    std::cout << "Size of deque: " << deque.Size() << std::endl;

    // Вывод всех элементов
    std::cout << "Deque elements: ";
    for (size_t i = 0; i < deque.Size(); ++i) {
        std::cout << deque[i] << " ";
    }
    std::cout << std::endl;

    // Изменение элемента по индексу
    deque[1] = 3;

    // Вывод измененного элемента
    std::cout << "Element at index 1: " << deque[1] << std::endl;

    // Вывод первого и последнего элементов
    std::cout << "First element: " << deque.Front() << std::endl;
    std::cout << "Last element: " << deque.Back() << std::endl;

    return 0;
}
