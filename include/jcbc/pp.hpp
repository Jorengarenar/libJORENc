#ifndef JCBC_PP_HPP_
#define JCBC_PP_HPP_

// Simple strong typedef
#define STRONG_TYPEDEF(T, D)                                 \
    struct D : public T {                                    \
        template<class... A> explicit D(A... a) : T(a...) {} \
        const T& raw() const { return *this; }               \
    }

// Safer (type wise) counting of array size (of course, only in the same or sub scope)
#define COUNT_OF(x) ((sizeof(x)/sizeof(0[x])) / ((size_t)(!(sizeof(x) % sizeof(0[x])))))

#endif // JCBC_PP_HPP_
