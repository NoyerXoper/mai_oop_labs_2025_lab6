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
    // Visitor will deleted killed npcs
    virtual void Visit(World& world) = 0;

protected:
    virtual void Visit(const Knight& knight, World& world) = 0;
    virtual void Visit(const Druid& druid, World& world) = 0;
    virtual void Visit(const Elven& Elven, World& world) = 0;
};

// The argument of visit method is "killer"
class FightVisitor: public Visitor {
public:
    FightVisitor(const Rules& rules);
    FightVisitor(Rules&& rules);

    virtual void Visit(World& world) override;

    void setRaidusOfMurder(double radius) noexcept;
    double getRaidusOfMurder() const noexcept;

protected:
    virtual void Visit(const Knight& knight, World& world) override;
    virtual void Visit(const Druid& druid, World& world) override;
    virtual void Visit(const Elven& elven, World& world) override;

private:
    std::set<std::size_t> killed_;
    Rules rules_;
};