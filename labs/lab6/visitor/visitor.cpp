#include "npc.hpp"
#include "visitor.hpp"
#include "world.hpp"

FightVisitor::FightVisitor(const Rules& rules): rules_(rules) {}

FightVisitor::FightVisitor(Rules&& rules): rules_(std::move(rules)) {}

void FightVisitor::Visit(World& world) {
    for(auto& npc: world.getEnities()) {
        npc->Accept(*this, world);
    }
}

void FightVisitor::Visit(const Knight& knight, World& world) {
    auto& field = world.getEnities();
    for (auto& victim: world.getEnities()) {
        if (std::addressof(knight) == victim.get()) {
            continue;
        }
    }
}