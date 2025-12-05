#pragma once

#include <memory>
#include <ostream>

#include "vec.hpp"

enum class NPCType : int { Knight, Druid, Elf, Unknown };

namespace NPCTypeConverter {
NPCType StringToNPCType(const std::string& name);
std::string NPCTypeToString(NPCType type);
}  // namespace NPCTypeConverter

class Visitor;

class Knight;
class Druid;
class Elven;

class World;

class NPC {
    friend class Visitor;
    friend class FightVisitor;

public:
    using NumberType = int;
    NPC(std::string_view name, NumberType x, NumberType y);

    NPCType getType() const noexcept;
    const std::string& getName() const noexcept;
    const vec::Vec<NumberType>& getPos() const noexcept;
    virtual ~NPC() noexcept = default;

protected:
    virtual void Accept(Visitor& visitor, World& world) = 0;

protected:
    std::string name_;
    NPCType type_ = NPCType::Unknown;
    vec::Vec<NumberType> pos_;
};

std::ostream& operator<<(std::ostream& out, const NPC& npc);
