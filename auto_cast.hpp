#ifndef jm4R_AUTO_CAST
#define jm4R_AUTO_CAST

namespace mj {

template <typename T>
class auto_cast_impl
{
    using type = const T&;
    type val_;
    
    auto_cast_impl(const T& val) : val_(val)
    {}
    
public:
    template <typename U>
    friend auto auto_cast(const U& val) -> auto_cast_impl<U>;
    
    template <typename U>
    operator U() &&
    {
        return static_cast<U>(val_);
    }
};

template <typename U>
auto auto_cast(const U& val) -> auto_cast_impl<U>
{
    return {val};
}

}  // namespace mj

#endif // jm4R_AUTO_CAST
