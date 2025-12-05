#pragma once

#include "npc.hpp"

class Druid : public NPC {
public:
    Druid(std::string_view name, NumberType x, NumberType y);

protected:
    virtual void Accept(Visitor& visitor, World& world) override;
};