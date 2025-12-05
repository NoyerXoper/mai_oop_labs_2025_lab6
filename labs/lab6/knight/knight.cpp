#include "knight.hpp"

#include "visitor.hpp"

Knight::Knight(std::string_view name, NumberType x, NumberType y)
    : NPC(name, x, y) {
    type_ = NPCType::Knight;
}

void Knight::Accept(Visitor& visitor, World& world) {
    visitor.Visit(*this, world);
}