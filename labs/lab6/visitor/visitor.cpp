#include "visitor.hpp"
#include "npc.hpp"
#include "world.hpp"

namespace game {
FightVisitor::FightVisitor(const Rules& rules)
    : rules_(rules) {}

FightVisitor::FightVisitor(Rules&& rules)
    : rules_(std::move(rules)) {}

void FightVisitor::setRaidusOfMurder(double radius) {
    rules_.setRadiusOfMurder(radius);
}

double FightVisitor::getRaidusOfMurder() const {
    return rules_.getRadiusOfMurder();
}

void FightVisitor::Visit(World& world) {
    for (auto& npc : world.IterateOverNPCs()) {
        npc->Accept(*this, world);
    }
    for (auto& killed : killed_) {
        world.KillNPC(killed);
    }
    killed_.clear();
}

void FightVisitor::Visit(const NPC& attacker, World& world) {
    for (auto& victim : world.IterateOverNPCs()) {
        if (std::addressof(attacker) == victim.get()) {
            continue;
        }
        if (attacker.getPos().DistanceToOther(victim->getPos()) <=
                getRaidusOfMurder() &&
            rules_.DoesKill(attacker.getType(), victim->getType())) {
            killed_.insert(victim);
            world.NotifyObservers(attacker, *victim);
        }
    }
}
}  // namespace game