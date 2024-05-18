#pragma once

namespace RAII {

template <typename Provider>
class Booking {
public:
    
    Booking(Provider* provider, int id)
        : provider_(provider), id_(id), active_(true) {}
    
    Booking(Booking&& other) noexcept
        : provider_(other.provider_), id_(other.id_), active_(other.active_) {
        other.active_ = false; // Перемещенный объект неактивен
    }
    
    Booking& operator=(Booking&& other) noexcept {
        if (this != &other) {
            if (active_) {
                provider_->CancelOrComplete(*this);
            }
            provider_ = other.provider_;
            id_ = other.id_;
            active_ = other.active_;
            other.active_ = false; // Перемещенный объект неактивен
        }
        return *this;
    }

    ~Booking() {
        if (active_) {
            provider_->CancelOrComplete(*this);
        }
    }

    int GetId() const {
        return id_;
    }

private:
    Provider* provider_; // Указатель на провайдера, для которого было сделано бронирование
    int id_;             // ID бронирования
    bool active_;        // Активен ли объект бронирования

    // Запрещаем копирование
    Booking(const Booking&) = delete;
    Booking& operator=(const Booking&) = delete;
};

} // namespace RAII
