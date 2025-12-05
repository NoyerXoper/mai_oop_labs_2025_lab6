#pragma once

#include <fstream>

#include "npc.hpp"

class NPCObserver {
public:
    virtual void update(const NPC& attacker, const NPC& defender) = 0;
    virtual ~NPCObserver() = default;
};

class ConsoleLogMurderObserver : public NPCObserver {
public:
    ConsoleLogMurderObserver() = default;
    virtual void update(const NPC& attacker, const NPC& defender) override;
};

class FileLogMurderObserver : public NPCObserver {
public:
    FileLogMurderObserver(std::string_view path);
    virtual void update(const NPC& attacker, const NPC& defender) override;

private:
    std::ofstream out_;
};