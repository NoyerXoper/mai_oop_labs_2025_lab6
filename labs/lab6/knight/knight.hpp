#pragma once

#include "npc.hpp"

class Knight : public NPC {
public:
    Knight(std::string_view name, NumberType x, NumberType y);

protected:
    virtual void Accept(Visitor& visitor, World& world) override;
};