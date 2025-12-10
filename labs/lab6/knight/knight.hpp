#pragma once

#include "npc.hpp"

namespace game {
class Knight : public NPC {
public:
    Knight(std::string_view name, NumberType x, NumberType y);

protected:
    virtual void Accept(Visitor& visitor, World& world) override;
};
}  // namespace game