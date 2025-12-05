#include "factory.hpp"
#include "druid.hpp"
#include "elf.hpp"
#include "exceptions.hpp"
#include "knight.hpp"

namespace factory {
std::shared_ptr<NPC> CreateNPC(NPCType type, std::string_view name,
                               NPC::NumberType x, NPC::NumberType y) {
    switch (type) {
    case NPCType::Knight:
        return std::make_shared<Knight>(name, x, y);
    case NPCType::Druid:
        return std::make_shared<Druid>(name, x, y);
    case NPCType::Elf:
        return std::make_shared<Elf>(name, x, y);
    default:
        throw exceptions::BadNPCTypeException("Invalid type of NPC");
    }
}
}  // namespace factory