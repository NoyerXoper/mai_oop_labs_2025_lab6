#include <iostream>

#include "observer.hpp"

namespace game {
void ConsoleLogMurderObserver::update(const NPC& attacker, const NPC& victim) {
    std::cout << "Murder: " << attacker << " killed " << victim << '\n';
}

FileLogMurderObserver::FileLogMurderObserver(std::string_view path)
    : out_(path.data(), std::ios::out | std::ios::ate) {}

void FileLogMurderObserver::update(const NPC& attacker, const NPC& victim) {
    out_ << "Murder: " << attacker << " killed " << victim << '\n';
}
}  // namespace game