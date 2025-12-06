#include "druid.hpp"

#include "visitor.hpp"

namespace game {
Druid::Druid(std::string_view name, NumberType x, NumberType y)
    : NPC(name, x, y) {
    type_ = NPCType::Druid;
}

void Druid::Accept(Visitor& visitor, World& world) {
    visitor.Visit(*this, world);
}
}  // namespace game