#pragma once
#include <map>
#include <type_traits>
#include <algorithm>
template <typename R>
class range {
public:
    typedef typename R::value_type value_type;
    range(R &r) : range_(r) {
    }
public:
    template <typename KeyFn, typename ValueFn>
    std::multimap<typename std::result_of<KeyFn(value_type)>::type, typename std::result_of<ValueFn(value_type)>::type>
        group_by(const KeyFn &keyf, const ValueFn &valuef) {
            typedef typename std::result_of<KeyFn(value_type)>::type k_type;
            typedef typename std::result_of<ValueFn(value_type)>::type v_type;
            std::multimap<k_type, v_type>mm;
            std::for_each(std::begin(range_), std::end(range_), [&mm, &keyf, &valuef] (const value_type &item) {
                k_type key = keyf(item);
                v_type value = valuef(item);
                mm.insert(std::make_pair(key, value));
            } );
            return mm;
    }
private:
    R range_;
};