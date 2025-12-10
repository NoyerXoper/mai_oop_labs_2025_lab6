#pragma once

#include <fstream>
#include <memory>
#include <vector>

#include "npc.hpp"
#include "observer.hpp"
#include "visitor.hpp"

namespace game {
class World {
    using NPCStorageType = std::set<std::shared_ptr<NPC>>;
    using ObserverStorageType = std::set<std::shared_ptr<NPCObserver>>;
    struct IterateOverNPCStruct {
    private:
        friend class World;
        World& world_;
        IterateOverNPCStruct(World& world);

    public:
        NPCStorageType::const_iterator begin() const noexcept;
        NPCStorageType::const_iterator end() const noexcept;
    };

public:
    static constexpr NPC::NumberType MIN_X = 0;
    static constexpr NPC::NumberType MAX_X = 500;

    static constexpr NPC::NumberType MIN_Y = 0;
    static constexpr NPC::NumberType MAX_Y = 500;
    void LoadFromFile(std::ifstream& in);
    void SaveToFile(std::ofstream& in) const;

    void AddNPC(std::shared_ptr<NPC> npc_ptr);
    void EmplaceNPC(NPCType type, std::string_view name, NPC::NumberType x,
                    NPC::NumberType y);
    void Accept(Visitor& visitor);

    std::size_t NPCCount() const noexcept;
    void KillNPC(std::shared_ptr<NPC> npc_ptr);

    IterateOverNPCStruct IterateOverNPCs() noexcept;

    void AttachObserver(std::shared_ptr<NPCObserver> observer);
    void DetachObserver(std::shared_ptr<NPCObserver> observer);

    void NotifyObservers(const NPC& attacker, const NPC& victim);

private:
    void AddNPCAfterChecks(std::shared_ptr<NPC> npc);
    NPCStorageType entities_;
    ObserverStorageType observers_;
    double radiusOfMurder;
};
}  // namespace game