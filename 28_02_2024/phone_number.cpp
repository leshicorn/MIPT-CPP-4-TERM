#include "phone_number.h"
#include <stdexcept>

PhoneNumber::PhoneNumber(const std::string &international_number) {
    // Поиск первого символа '-' после символа '+'.
    size_t first_dash_pos = international_number.find('-', 1);
    if (first_dash_pos == std::string::npos)
        throw std::invalid_argument("Invalid phone number format");

    // Получение кода страны.
    country_code_ = international_number.substr(1, first_dash_pos - 1);

    // Поиск второго символа '-'.
    size_t second_dash_pos = international_number.find('-', first_dash_pos + 1);
    if (second_dash_pos == std::string::npos)
        throw std::invalid_argument("Invalid phone number format");

    // Получение кода города.
    city_code_ = international_number.substr(first_dash_pos + 1, second_dash_pos - first_dash_pos - 1);

    // Получение местного номера.
    local_number_ = international_number.substr(second_dash_pos + 1);

    // Проверка на пустоту кода страны, кода города и местного номера.
    if (country_code_.empty() || city_code_.empty() || local_number_.empty())
        throw std::invalid_argument("Invalid phone number format");
}

std::string PhoneNumber::GetCountryCode() const {
    return country_code_;
}

std::string PhoneNumber::GetCityCode() const {
    return city_code_;
}

std::string PhoneNumber::GetLocalNumber() const {
    return local_number_;
}

std::string PhoneNumber::GetInternationalNumber() const {
    return "+" + country_code_ + "-" + city_code_ + "-" + local_number_;
}
