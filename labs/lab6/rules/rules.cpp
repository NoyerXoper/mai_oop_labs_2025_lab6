#include "rules.hpp"
#include "exceptions.hpp"

Rules::Rules(Rules::StorageType&& killingData)
    : storage_(std::move(killingData)) {}

bool Rules::DoesKill(NPCType attacker, NPCType defender) const noexcept {
    auto it = storage_.find(attacker);
    if (it == storage_.end()) {
        return false;
    }
    return it->second.contains(defender);
}

void Rules::setRadiusOfMurder(double radius) {
    if (radius < 0) {
        throw exceptions::InvlidRadiusException("Radius must be non-negative");
    }
    radiusOfMurder = radius;
}

double Rules::getRadiusOfMurder() const {
    return radiusOfMurder;
}

RulesBuilder& RulesBuilder::AddRule(NPCType attacker, NPCType victim) {
    storage_[attacker].insert(victim);
    return *this;
}

Rules RulesBuilder::Build() {
    return Rules(std::move(storage_));
}
