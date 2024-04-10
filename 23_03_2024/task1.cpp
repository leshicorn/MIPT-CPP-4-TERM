    #include <iostream>
#include <queue>
#include <unordered_map>

int main() {
    int n;
    std::cin >> n;

    std::unordered_map<int, int> lineup; // хэш-таблица для хранения информации о порядке встать
    std::queue<int> players; // очередь для хранения спортсменов

    // Читаем информацию о каждом спортсмене и его месте в строю
    for (int i = 0; i < n; ++i) {
        int player, ahead_of;
        std::cin >> player >> ahead_of;
        lineup[player] = ahead_of;
        if (ahead_of == 0) {
            players.push(player); // если никого нет перед текущим спортсменом, добавляем его в очередь
        }
    }

    // Печатаем порядок спортсменов на поле
    while (!players.empty()) {
        int current_player = players.front();
        players.pop();
        std::cout << current_player << '\n';
        // Проверяем, есть ли кого-то, кто должен встать перед текущим спортсменом
        if (lineup.find(current_player) != lineup.end()) {
            int ahead_of = lineup[current_player];
            players.push(ahead_of);
        }
    }

    return 0;
}
