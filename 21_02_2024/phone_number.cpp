#include "phone_number.h"
#include <stdexcept>
#include <iostream>

PhoneNumber::PhoneNumber(const string &international_number) {
    // Поиск первого символа '-' после символа '+'.
    size_t first_dash_pos = international_number.find('-', 1);
    if (first_dash_pos == string::npos)
        throw invalid_argument("Invalid phone number format");

    // Получение кода страны.
    country_code_ = international_number.substr(1, first_dash_pos - 1);

    // Поиск второго символа '-'.
    size_t second_dash_pos = international_number.find('-', first_dash_pos + 1);
    if (second_dash_pos == string::npos)
        throw invalid_argument("Invalid phone number format");

    // Получение кода города.
    city_code_ = international_number.substr(first_dash_pos + 1, second_dash_pos - first_dash_pos - 1);

    // Получение местного номера.
    local_number_ = international_number.substr(second_dash_pos + 1);

    // Проверка на пустоту кода страны, кода города и местного номера.
    if (country_code_.empty() || city_code_.empty() || local_number_.empty())
        throw invalid_argument("Invalid phone number format");
}

string PhoneNumber::GetCountryCode() const {
    return country_code_;
}

string PhoneNumber::GetCityCode() const {
    return city_code_;
}

string PhoneNumber::GetLocalNumber() const {
    return local_number_;
}

string PhoneNumber::GetInternationalNumber() const {
    return "+" + country_code_ + "-" + city_code_ + "-" + local_number_;
}

int main() {
    try {
        // Правильные форматы номеров.
        PhoneNumber num1("+7-495-111-22-33");
        PhoneNumber num2("+7-495-1112233");
        PhoneNumber num3("+323-22-460002");
        
        // Неправильные форматы номеров.
        // В этих случаях ожидается выброс исключения invalid_argument.
        // PhoneNumber num4("+1-2-coursera-cpp");
        // PhoneNumber num5("1-2-333");
        // PhoneNumber num6("+7-1233");

        std::cout << "Country Code: " << num1.GetCountryCode() << std::endl;
        std::cout << "City Code: " << num1.GetCityCode() << std::endl;
        std::cout << "Local Number: " << num1.GetLocalNumber() << std::endl;
        std::cout << "International Number: " << num1.GetInternationalNumber() << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cerr << "Invalid phone number: " << e.what() << std::endl;
    }

    return 0;
}