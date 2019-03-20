#ifndef jm4R_TEST_UTILS
#define jm4R_TEST_UTILS

#include <iostream>

namespace mj {

struct Verbose
{
    Verbose()
    {
        std::cout << "{ V() }";
    }
    Verbose(const Verbose&)
    {
        std::cout << "{ V(const V&) }";
    }
    Verbose(Verbose&&) noexcept
    {
        std::cout << "{ V(V&&) noexcept }";
    }
    template <typename... Args>
    Verbose(Args&&...)
    {
        std::cout << "{ V(Args&&...) }";
    }
    ~Verbose()
    {
        std::cout << "{ ~V() }";
    }
    Verbose& operator=(const Verbose&)
    {
        std::cout << "{ operator=(const V&) }";
        return *this;
    }
    Verbose& operator=(Verbose&&) noexcept
    {
        std::cout << "{ operator=(V&&) noexcept }";
        return *this;
    }
};

}  // namespace mj

#endif // jm4R_TEST_UTILS
