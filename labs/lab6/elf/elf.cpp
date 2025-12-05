#include "elf.hpp"

#include "visitor.hpp"

Elf::Elf(std::string_view name, NumberType x, NumberType y)
    : NPC(name, x, y) {
    type_ = NPCType::Elf;
}

void Elf::Accept(Visitor& visitor, World& world) {
    visitor.Visit(*this, world);
}