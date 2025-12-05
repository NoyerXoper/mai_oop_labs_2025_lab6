#pragma once

#include "npc.hpp"

namespace factory {
std::shared_ptr<NPC> CreateNPC(NPCType type, std::string_view name,
                               NPC::NumberType x, NPC::NumberType y);
}