#include "rules.hpp"

Rules::Rules(Rules::StorageType&& killingData): storage_(std::move(killingData)) {}

bool Rules::DoesKill(NPCTypes attacker, NPCTypes defender) const noexcept {
    auto it = storage_.find(attacker);
    if (it == storage_.end()) {
        return false;
    }
    return it->second.contains(defender);
}

void Rules::setRadiusOfMurder(double radius) noexcept {
    radiusOfMurder = radius;
}

double Rules::getRadiusOfMurder() const noexcept {
    return radiusOfMurder;
}

RulesBuilder& RulesBuilder::AddRule(NPCTypes attacker, NPCTypes victim) {
    storage_[attacker].insert(victim);
    return *this;
}

Rules RulesBuilder::Build() {
    return Rules(std::move(storage_));
}
