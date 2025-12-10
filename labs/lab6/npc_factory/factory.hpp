#pragma once

#include "npc.hpp"

namespace factory {
std::shared_ptr<game::NPC> CreateNPC(game::NPCType type, std::string_view name,
                                     game::NPC::NumberType x,
                                     game::NPC::NumberType y);
}