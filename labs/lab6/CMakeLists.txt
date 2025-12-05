include_directories(exceptions npc knight druid elf npc_factory observer rules vec2 visitor world)

add_library(GameLib npc/npc.cpp knight/knight.cpp druid/druid.cpp elf/elf.cpp npc_factory/factory.cpp observer/observer.cpp rules/rules.cpp visitor/visitor.cpp world/world.cpp)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE GameLib)

add_executable(test_exec tests/tests.cpp)
target_link_libraries(test_exec PRIVATE GameLib gtest gtest_main)
