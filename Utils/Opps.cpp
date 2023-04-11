#include "Headers/Opps.hpp"

nts::Tristate nts::operator&(nts::Tristate a, nts::Tristate b)
{
    /*
    A B AND
    0 0 0
    0 1 0
    0 U 0
    1 0 0
    1 1 1
    1 U U
    U 0 0
    U 1 U
    U U U*/
    if (a == nts::Tristate::Undefined || b == nts::Tristate::Undefined)
    {
        if (a == nts::Tristate::False || b == nts::Tristate::False)
            return nts::Tristate::False;
        return nts::Tristate::Undefined;
    }
    return (Tristate)((int)a & (int)b);
}

nts::Tristate nts::operator|(nts::Tristate a, nts::Tristate b)
{
    /*
    A B OR
    0 0 0
    0 1 1
    0 U U
    1 0 1
    1 1 1
    1 U 1
    U 0 U
    U 1 1
    U U U*/
    if (a == nts::Tristate::True || b == nts::Tristate::True)
        return nts::Tristate::True;
    if (a == nts::Tristate::Undefined || b == nts::Tristate::Undefined)
        return nts::Tristate::Undefined;
    return (Tristate)((int)a | (int)b);
}

nts::Tristate nts::operator^(nts::Tristate a, nts::Tristate b)
{
    /*
    A B XOR
    0 0 0
    0 1 1
    0 U U
    1 0 1
    1 1 0
    1 U U
    U 0 U
    U 1 U
    U U U*/
    if (a == nts::Tristate::Undefined || b == nts::Tristate::Undefined)
        return nts::Tristate::Undefined;
    return (Tristate)((int)a ^ (int)b);
}

nts::Tristate nts::operator!(nts::Tristate a)
{
    /*
    A NOT
    0 1
    1 0
    U U*/
    if (a == nts::Tristate::Undefined)
        return nts::Tristate::Undefined;
    return (Tristate)(!(int)a);
}

std::string nts::ConvertTristate(nts::Tristate a)
{
    if (a == nts::Tristate::True)
        return "1";
    if (a == nts::Tristate::False)
        return "0";
    return "U";
}

// first is the result, second is the carry
std::pair<nts::Tristate, nts::Tristate> nts::adder(nts::Tristate a, nts::Tristate b, nts::Tristate carry)
{
    if (a == Tristate::Undefined || b == Tristate::Undefined || carry == Tristate::Undefined)
        return std::make_pair(Tristate::Undefined, Tristate::Undefined);
    if (a == Tristate::True && b == Tristate::True && carry == Tristate::True)
        return std::make_pair(Tristate::True, Tristate::True);
    if (a == Tristate::True && b == Tristate::True && carry == Tristate::False)
        return std::make_pair(Tristate::False, Tristate::True);
    if (a == Tristate::True && b == Tristate::False && carry == Tristate::True)
        return std::make_pair(Tristate::False, Tristate::True);
    if (a == Tristate::True && b == Tristate::False && carry == Tristate::False)
        return std::make_pair(Tristate::True, Tristate::False);
    if (a == Tristate::False && b == Tristate::True && carry == Tristate::True)
        return std::make_pair(Tristate::False, Tristate::True);
    if (a == Tristate::False && b == Tristate::True && carry == Tristate::False)
        return std::make_pair(Tristate::True, Tristate::False);
    if (a == Tristate::False && b == Tristate::False && carry == Tristate::True)
        return std::make_pair(Tristate::True, Tristate::False);
    if (a == Tristate::False && b == Tristate::False && carry == Tristate::False)
        return std::make_pair(Tristate::False, Tristate::False);
    return std::make_pair(Tristate::Undefined, Tristate::Undefined);
}

std::ostream &nts::operator<<(std::ostream &os, nts::Tristate a)
{
    os << ConvertTristate(a);
    return os;
}
