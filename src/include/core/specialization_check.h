#pragma once 

namespace apc
{
    template <typename T1, template <typename... T2> class TMP2>
    struct is_specialization
    {
        static constexpr bool value = false;
    };

    template <template <typename... T1> class TMP1, typename... T1>
    struct is_specialization<TMP1<T1...>, TMP1>
    {
        static constexpr bool value = true;
    };
}