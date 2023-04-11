#pragma once

#include "../../Components/Interface-Abstract/IComponent.hpp"

namespace nts
{
    enum class Tristate;
    Tristate operator&(Tristate a, Tristate b);
    Tristate operator|(Tristate a, Tristate b);
    Tristate operator^(Tristate a, Tristate b);
    Tristate operator!(Tristate a);
    std::string ConvertTristate(Tristate a);
    std::ostream &operator<<(std::ostream &os, Tristate a);
    std::pair<nts::Tristate, nts::Tristate> adder(nts::Tristate a, nts::Tristate b, nts::Tristate carry);
}
