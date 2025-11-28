#pragma once

#include <memory>
#include <vector>

#include "npc.hpp"
#include "visitor.hpp"

class World {
using NPCStorageType = std::vector<std::shared_ptr<NPC>>;
public:

    World(const Rules& rules);
    World(Rules&& rules);

    void AddNPC(std::shared_ptr<NPC> npc_ptr);
    void Accept(Visitor& visitor);

    void setRadiusOfMurder(double radius) noexcept;
    double getRadiusOfMurder() noexcept;

    NPCStorageType& getEnities() noexcept;
    const NPCStorageType& getEnities() const noexcept;

private:
    NPCStorageType entities_;
    double radiusOfMurder;
};