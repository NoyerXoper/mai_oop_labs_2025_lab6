#include <gtest/gtest.h>

#include "druid.hpp"
#include "elf.hpp"
#include "factory.hpp"
#include "knight.hpp"
#include "npc.hpp"
#include "world.hpp"

class TestObserver : public game::NPCObserver {
public:
    virtual void update(const game::NPC& attacker,
                        const game::NPC& victim) override {
        ++updated_times;
    }
    std::size_t updated_times = 0;
};

class WorldTest : public ::testing::Test {
protected:
    void SetUp() override {
        world = game::World();
        game::Rules rules =
            game::RulesBuilder()
                .AddRule(game::NPCType::Knight, game::NPCType::Elf)
                .AddRule(game::NPCType::Elf, game::NPCType::Druid)
                .AddRule(game::NPCType::Elf, game::NPCType::Knight)
                .AddRule(game::NPCType::Druid, game::NPCType::Druid)
                .Build();
        fight_visitor = game::FightVisitor(rules);
    }

    void AddNPCS(std::size_t amount) {
        for (std::size_t i = 0; i < amount; ++i) {
            world.EmplaceNPC(static_cast<game::NPCType>(
                                 i % static_cast<int>(game::NPCType::Unknown)),
                             "Name", i % game::World::MAX_X,
                             i * i % game::World::MAX_Y);
        }
    }

    game::World world;
    game::FightVisitor fight_visitor;
};

TEST(FactoryTest, Creation) {
    auto npc1 = factory::CreateNPC(game::NPCType::Knight, "knight", 2, 2);
    auto npc2 = factory::CreateNPC(game::NPCType::Druid, "druid", 2, 2);
    auto npc3 = factory::CreateNPC(game::NPCType::Elf, "elf", 2, 2);

    EXPECT_EQ(npc1->getType(), game::NPCType::Knight);
    EXPECT_EQ(npc2->getType(), game::NPCType::Druid);
    EXPECT_EQ(npc3->getType(), game::NPCType::Elf);

    EXPECT_EQ(npc1->getName(), "knight");
    EXPECT_EQ(npc2->getName(), "druid");
    EXPECT_EQ(npc3->getName(), "elf");

    EXPECT_EQ(npc1->getPos(), vec::Vec<int>(2, 2));
    EXPECT_EQ(npc2->getPos(), vec::Vec<int>(2, 2));
    EXPECT_EQ(npc3->getPos(), vec::Vec<int>(2, 2));
}

TEST_F(WorldTest, AdditonOfNPCTest) {
    EXPECT_NO_THROW({
        this->world.AddNPC(
            factory::CreateNPC(game::NPCType::Druid, "druid", 2, 2));
    });
}

TEST_F(WorldTest, EmplacingOfNPCTest) {
    EXPECT_NO_THROW(
        { this->world.EmplaceNPC(game::NPCType::Druid, "druid", 2, 2); });
}

TEST_F(WorldTest, KillTest) {
    auto observer = std::make_shared<TestObserver>();
    this->world.AttachObserver(observer);
    this->AddNPCS(5);
    auto killer = this->world.IterateOverNPCs().begin();
    auto victim = ++this->world.IterateOverNPCs().begin();

    this->world.NotifyObservers(**killer, **victim);
    EXPECT_EQ(observer->updated_times, 1);
}

TEST_F(WorldTest, CarnageTest) {
    auto knight = factory::CreateNPC(game::NPCType::Knight, "knight", 0, 0);
    auto elf = factory::CreateNPC(game::NPCType::Elf, "elf", 0, 0);

    world.AddNPC(knight);
    world.AddNPC(elf);

    world.Accept(this->fight_visitor);

    EXPECT_EQ(world.NPCCount(), 0);
}