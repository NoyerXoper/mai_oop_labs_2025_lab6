#include "npc.hpp"
#include "visitor.hpp"

NPC::NPC(std::string_view name, int x, int y): name_(name), pos_(x, y) {}

NPCTypes NPC::getType() const noexcept {
    return type_;
}

Knight::Knight(std::string_view name, int x, int y): NPC(name, x, y) {
    type_ = NPCTypes::Knight;
}

void Knight::Accept(Visitor& visitor, World& world) {
    visitor.Visit(*this, world);
}

Druid::Druid(std::string_view name, int x, int y): NPC(name, x, y) {
    type_ = NPCTypes::Druid;
}

void Druid::Accept(Visitor& visitor, World& world) {
    visitor.Visit(*this, world);
}

Elven::Elven(std::string_view name, int x, int y): NPC(name, x, y) {
    type_ = NPCTypes::Elven;
}

void Elven::Accept(Visitor& visitor, World& world) {
    visitor.Visit(*this, world);
}
