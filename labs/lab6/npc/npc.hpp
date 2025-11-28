#pragma once

#include <memory>

enum class NPCTypes: int{
    Unknown,
    Knight,
    Druid,
    Elven
};

struct Vec2 {
    int x;
    int y;


};

class Visitor;

class Knight;
class Druid;
class Elven;

class NPC {
friend class Visitor;
friend class FightVisitor;
public:
    NPC(std::string_view name, int x, int y);

    NPCTypes getType() const noexcept;

protected:
    virtual void Accept(Visitor& visitor, World& world) = 0;

protected:
    std::string name_;
    NPCTypes type_ = NPCTypes::Unknown;
    Vec2 pos_;
};

class Knight: public NPC {
public: 
    Knight(std::string_view name, int x, int y);
protected:
    virtual void Accept(Visitor& visitor, World& world) override;
};

class Druid: public NPC {
public: 
    Druid(std::string_view name, int x, int y);
protected:
    virtual void Accept(Visitor& visitor, World& world) override;
};

class Elven: public NPC {
public: 
    Elven(std::string_view name, int x, int y);
protected:
    virtual void Accept(Visitor& visitor, World& world) override;
};
