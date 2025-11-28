#pragma once

#include <map>
#include <set>

#include "npc.hpp"

class RulesBuilder;

class Rules {
public:
    bool DoesKill(NPCTypes attacker, NPCTypes defender) const noexcept;

    void setRadiusOfMurder(double radius) noexcept;
    double getRadiusOfMurder() const noexcept;

private:
    friend class RulesBuilder;
    using StorageType = std::map<NPCTypes, std::set<NPCTypes>>;

    Rules(StorageType&& killingData);
    StorageType storage_;
    double radiusOfMurder = 0;
};

class RulesBuilder {
public:
    RulesBuilder& AddRule(NPCTypes attacker, NPCTypes victim);
    Rules Build();
private:
    Rules::StorageType storage_;
};