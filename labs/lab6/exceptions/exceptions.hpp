#pragma once

#include <stdexcept>

namespace exceptions {
class BadNPCTypeException : public std::logic_error {
    using logic_error::logic_error;
};

class NPCNotFound : public std::logic_error {
    using logic_error::logic_error;
};

class InvlidRadiusException : public std::logic_error {
    using logic_error::logic_error;
};

class BadFileException : public std::runtime_error {
    using runtime_error::runtime_error;
};

class BadNPCPositionException : public std::runtime_error {
    using runtime_error::runtime_error;
};

}  // namespace exceptions