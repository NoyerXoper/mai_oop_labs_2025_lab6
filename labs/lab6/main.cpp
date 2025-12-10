#include <iostream>

#include "druid.hpp"
#include "elf.hpp"
#include "exceptions.hpp"
#include "factory.hpp"
#include "knight.hpp"
#include "observer.hpp"
#include "visitor.hpp"
#include "world.hpp"

int main() {
    game::World world;
    game::Rules rules = game::RulesBuilder()
                            .AddRule(game::NPCType::Knight, game::NPCType::Elf)
                            .AddRule(game::NPCType::Elf, game::NPCType::Druid)
                            .AddRule(game::NPCType::Elf, game::NPCType::Knight)
                            .AddRule(game::NPCType::Druid, game::NPCType::Druid)
                            .Build();
    std::shared_ptr<game::FightVisitor> visitor =
        std::make_shared<game::FightVisitor>(rules);
    std::shared_ptr<game::NPCObserver> console_observer =
        std::make_shared<game::ConsoleLogMurderObserver>();
    std::shared_ptr<game::NPCObserver> file_observer =
        std::make_shared<game::FileLogMurderObserver>("./log.txt");
    world.AttachObserver(console_observer);
    world.AttachObserver(file_observer);
    bool running = true;
    while (running) {
        std::cout << "What do you wanna do?\n";
        std::cout << "1) Add new NPC\n";
        std::cout << "2) Save map to file\n";
        std::cout << "3) Load map from file\n";
        std::cout << "4) Print NPC\n";
        std::cout << "5) Make NPC fight\n";
        std::cout << "6) Quit\n";
        int action;
        std::cin >> action;
        switch (action) {
        case 1: {
            std::cout << "Enter NPC type(knight/druid/elf (in lower case)): ";
            game::NPCType type;
            std::string string_action;
            for (;;) {
                try {
                    std::cin >> string_action;
                    if (string_action == "exit") {
                        break;
                    }
                    type =
                        game::NPCTypeConverter::StringToNPCType(string_action);
                    std::string name;
                    std::cout << "Enter name of npc: ";
                    std::cin >> std::ws;
                    std::getline(std::cin, name);
                    int x, y;
                    std::cout << "Enter coordinates of the NPC (int from 0 to "
                                 "500, x and y): ";
                    for (;;) {
                        std::cin >> x >> y;
                        try {
                            world.EmplaceNPC(type, name, x, y);
                        } catch (const exceptions::BadNPCPositionException&) {
                            std::cout << "Enter valid position of npc: ";
                            continue;
                        }
                        break;
                    }
                } catch (const exceptions::BadNPCTypeException&) {
                    std::cout
                        << "Bad type, try again. To exit write \"exit\": ";
                    continue;
                }
                break;
            }
            break;
        }
        case 2: {
            std::string path;
            std::cout << "Enter path to file or \"exit\" to exit: ";
            for (;;) {
                std::cin >> std::ws;
                std::getline(std::cin, path);
                if (path == "exit") {
                    break;
                }
                std::ofstream out(path);
                if (!out) {
                    std::cout << "Couldn't open file, retry: ";
                    continue;
                }
                world.SaveToFile(out);
                break;
            }
            break;
        }
        case 3: {
            std::string path;
            std::cout << "Enter path to file or \"exit\" to exit: ";
            for (;;) {
                std::cin >> std::ws;
                std::getline(std::cin, path);
                if (path == "exit") {
                    break;
                }
                std::ifstream in(path);
                if (!in) {
                    std::cout << "Couldn't open file, retry: ";
                    continue;
                }
                world.LoadFromFile(in);
                break;
            }
            break;
        }
        case 4:
            for (auto& npc : world.IterateOverNPCs()) {
                std::cout << *npc << '\n';
            }
            break;
        case 5: {
            double radius;
            std::cout << "Enter radius of murder: ";
            for (;;) {
                std::cin >> radius;
                try {
                    visitor->setRaidusOfMurder(radius);
                } catch (const exceptions::InvlidRadiusException&) {
                    std::cout << "Enter non-negative radius: ";
                    continue;
                }
                break;
            }
            world.Accept(*visitor);
            break;
        }
        case 6:
            running = false;
            break;
        }
    }
}