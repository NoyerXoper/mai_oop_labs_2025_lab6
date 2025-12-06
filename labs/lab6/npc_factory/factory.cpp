#include "factory.hpp"
#include "druid.hpp"
#include "elf.hpp"
#include "exceptions.hpp"
#include "knight.hpp"

namespace factory {
std::shared_ptr<game::NPC> CreateNPC(game::NPCType type, std::string_view name,
                                     game::NPC::NumberType x,
                                     game::NPC::NumberType y) {
    switch (type) {
    case game::NPCType::Knight:
        return std::make_shared<game::Knight>(name, x, y);
    case game::NPCType::Druid:
        return std::make_shared<game::Druid>(name, x, y);
    case game::NPCType::Elf:
        return std::make_shared<game::Elf>(name, x, y);
    default:
        throw exceptions::BadNPCTypeException("Invalid type of NPC");
    }
}
}  // namespace factory