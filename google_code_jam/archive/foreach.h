/*
 * Differences from BOOST_FOREACH:
 *
 *   - Only supports builtin arrays and STL-container-like things (begin(), end(), iterator, const_iterator)
 *   - Doesn't guard against multiple evaluation of the second argument
 *   - Much simpler and faster to compile
 *   - Probably buggy
 */
#include <cstdlib>  // for size_t


namespace foreach_detail {

struct auto_any_base
{
    operator bool() const { return false; }
};

template<class T>
struct auto_any : auto_any_base
{
    mutable T item;
    auto_any(T const& t) : item(t) {}
};

typedef auto_any_base const& auto_any_t;

template<class T>
inline auto_any<T> make_auto_any(T const& t) { return auto_any<T>(t); }

template<class T> inline typename T::const_iterator range_begin(T const& x) { return x.begin(); }
template<class T> inline typename T::const_iterator range_end  (T const& x) { return x.end(); }

template<class T> inline typename T::iterator range_begin(T& x) { return x.begin(); }
template<class T> inline typename T::iterator range_end  (T& x) { return x.end(); }

template<class T, std::size_t sz> inline T* range_begin(T (&a)[sz]) { return a; }
template<class T, std::size_t sz> inline T* range_end  (T (&a)[sz]) { return a + sz; }

template<class T>
inline T& cast(auto_any_t x, T const*)
{
    return static_cast<auto_any<T>const&>(x).item;
}

template<class T>
inline bool equal(auto_any_base const& a, auto_any_base const& b, T* type)
{
    return cast(a,type) == cast(b,type);
}

template<class T>
inline T const* address(T const& a) { return &a; }

} // namespace foreach_detail


#define foreach_range(VAR,LOW,HIGH) \
    if (foreach_detail::auto_any_t _foreach_cur = foreach_detail::make_auto_any(LOW)) {} else                              \
    if (foreach_detail::auto_any_t _foreach_end = foreach_detail::make_auto_any(HIGH)) {} else                             \
    for (bool _foreach_continue = true;                                                                                    \
            _foreach_continue && !foreach_detail::equal(_foreach_cur, _foreach_end, false?0:foreach_detail::address(LOW)); \
            _foreach_continue ? ++foreach_detail::cast(_foreach_cur, false?0:foreach_detail::address(LOW)) : (void)0)      \
        if (!!(_foreach_continue = false)) {} else                                                                         \
        for (VAR = *foreach_detail::cast(_foreach_cur, false?0:foreach_detail::address(LOW)); !_foreach_continue; _foreach_continue = true)

#define foreach(VAR,COL) \
    foreach_range(VAR,foreach_detail::range_begin(COL),foreach_detail::range_end(COL))
