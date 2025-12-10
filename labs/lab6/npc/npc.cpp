#include "npc.hpp"

#include <algorithm>
#include <array>
#include <map>

#include "exceptions.hpp"
#include "visitor.hpp"

namespace game {
NPCType NPCTypeConverter::StringToNPCType(const std::string& name) {
    static const std::map<std::string, NPCType> types = {
        {"knight", NPCType::Knight},
        {"druid", NPCType::Druid},
        {"elf", NPCType::Elf}};
    std::string temp = name;
    std::transform(temp.begin(), temp.end(), temp.begin(),
                   [](unsigned char ch) { return std::tolower(ch); });

    try {
        return types.at(temp);
    } catch (const std::out_of_range&) {
        throw exceptions::BadNPCTypeException("Can't cast " + name +
                                              "to NPCType");
    }
}

std::string NPCTypeConverter::NPCTypeToString(NPCType type) {
    static constexpr std::array names = {"Knight", "Druid", "Elf", "Unknown"};
    return names.at(static_cast<int>(type));
}

NPC::NPC(std::string_view name, NumberType x, NumberType y)
    : name_(name)
    , pos_(x, y) {}

NPCType NPC::getType() const noexcept {
    return type_;
}

const std::string& NPC::getName() const noexcept {
    return name_;
}

const vec::Vec<NPC::NumberType>& NPC::getPos() const noexcept {
    return pos_;
}

std::ostream& operator<<(std::ostream& out, const NPC& npc) {
    out << NPCTypeConverter::NPCTypeToString(npc.getType()) << ' '
        << npc.getName() << " at " << npc.getPos();
    return out;
}
}  // namespace game