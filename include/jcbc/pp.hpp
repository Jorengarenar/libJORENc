#ifndef JCBC_PP_HPP_
#define JCBC_PP_HPP_

// Simple strong typedef
#define STRONG_TYPEDEF(T, D)                                 \
    struct D : public T {                                    \
        template<class... A> explicit D(A... a) : T(a...) {} \
        const T& raw() const { return *this; }               \
    }

#endif // JCBC_PP_HPP_
