#pragma once

#include "npc.hpp"

namespace game {
class Elf : public NPC {
public:
    Elf(std::string_view name, NumberType x, NumberType y);

protected:
    virtual void Accept(Visitor& visitor, World& world) override;
};
}  // namespace game