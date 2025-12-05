#pragma once

#include <map>
#include <set>

#include "npc.hpp"

class RulesBuilder;

class Rules {
public:
    Rules() = default;
    bool DoesKill(NPCType attacker, NPCType defender) const noexcept;

    void setRadiusOfMurder(double radius);
    double getRadiusOfMurder() const;

private:
    friend class RulesBuilder;
    using StorageType = std::map<NPCType, std::set<NPCType>>;

    Rules(StorageType&& killingData);
    StorageType storage_;
    double radiusOfMurder = 0;
};

class RulesBuilder {
public:
    RulesBuilder& AddRule(NPCType attacker, NPCType victim);
    Rules Build();

private:
    Rules::StorageType storage_;
};