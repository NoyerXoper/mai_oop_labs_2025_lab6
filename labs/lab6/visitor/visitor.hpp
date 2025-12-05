#pragma once

#include <set>

#include "npc.hpp"
#include "rules.hpp"

class World;

class Visitor {
    friend class Knight;
    friend class Druid;
    friend class Elven;

public:
    virtual void Visit(World& world) = 0;

    virtual void Visit(const NPC& npc, World& world) = 0;
};

class FightVisitor : public Visitor {
public:
    FightVisitor() = default;
    FightVisitor(const Rules& rules);
    FightVisitor(Rules&& rules);

    void setRaidusOfMurder(double radius);
    double getRaidusOfMurder() const;

    virtual void Visit(World& world) override;

    virtual void Visit(const NPC& npc, World& world) override;

private:
    std::set<std::shared_ptr<NPC>> killed_;
    Rules rules_;
};