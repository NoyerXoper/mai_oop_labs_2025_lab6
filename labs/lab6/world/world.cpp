#include "world.hpp"
#include "exceptions.hpp"
#include "factory.hpp"

World::IterateOverNPCStruct::IterateOverNPCStruct(World& world)
    : world_(world) {}

World::NPCStorageType::const_iterator
World::IterateOverNPCStruct::begin() const noexcept {
    return world_.entities_.begin();
}

World::NPCStorageType::const_iterator
World::IterateOverNPCStruct::end() const noexcept {
    return world_.entities_.end();
}

void World::SaveToFile(std::ofstream& out) const {
    for (auto& npc : entities_) {
        out << NPCTypeConverter::NPCTypeToString(npc->getType()) << ' '
            << npc->getName() << "| " << npc->getPos().x << ' '
            << npc->getPos().y << '\n';
    }
}

void World::LoadFromFile(std::ifstream& in) {
    NPCStorageType temp_storage;
    std::string type_str;
    std::string name;
    NPCType type;
    NPC::NumberType x, y;
    while (in >> type_str) {
        try {
            type = NPCTypeConverter::StringToNPCType(type_str);
        } catch (const exceptions::BadNPCTypeException&) {
            throw exceptions::BadFileException("Invalid type of NPC spotted");
        }
        in >> std::ws;

        if (!std::getline(in, name, '|')) {
            throw exceptions::BadFileException(
                "Problem with reading name of NPC");
        }
        if (in >> x >> y) {
            temp_storage.insert(factory::CreateNPC(type, name, x, y));
        } else {
            throw exceptions::BadFileException("Couldn't read coordinates");
        }
    }
    std::swap(temp_storage, entities_);
}

void World::AddNPC(std::shared_ptr<NPC> npc) {
    auto& pos = npc->getPos();
    if (pos.x < MIN_X || pos.x > MAX_X || pos.y < MIN_Y || pos.y > MAX_Y) {
        throw exceptions::BadNPCPositionException("Invalid position of NPC");
    }
    AddNPCAfterChecks(npc);
}

void World::EmplaceNPC(NPCType type, std::string_view name, NPC::NumberType x,
                       NPC::NumberType y) {
    if (x < MIN_X || x > MAX_X || y < MIN_Y || y > MAX_Y) {
        throw exceptions::BadNPCPositionException("Invalid position of NPC");
    }
    AddNPCAfterChecks(factory::CreateNPC(type, name, x, y));
}

void World::AddNPCAfterChecks(std::shared_ptr<NPC> npc) {
    entities_.insert(npc);
}

void World::Accept(Visitor& visitor) {
    visitor.Visit(*this);
}

void World::AttachObserver(std::shared_ptr<NPCObserver> observer) {
    observers_.insert(observer);
}

void World::DetachObserver(std::shared_ptr<NPCObserver> observer) {
    auto it = observers_.find(observer);
    if (it != observers_.end()) {
        observers_.erase(it);
    }
}

World::IterateOverNPCStruct World::IterateOverNPCs() noexcept {
    return {*this};
}

void World::KillNPC(std::shared_ptr<NPC> npc_ptr) {
    auto it = entities_.find(npc_ptr);
    if (it == entities_.end()) {
        throw exceptions::NPCNotFound("NPC not found in world");
    }
    entities_.erase(it);
}

std::size_t World::NPCCount() const noexcept {
    return entities_.size();
}

void World::NotifyObservers(const NPC& attacker, const NPC& victim) {
    for (auto& observer : observers_) {
        observer->update(attacker, victim);
    }
}