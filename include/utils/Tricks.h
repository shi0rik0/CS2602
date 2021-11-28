//
// Created by zsy on 2021/11/26.
//

#ifndef CLION_PROJ_TRICKS_H
#define CLION_PROJ_TRICKS_H

// https://stackoverflow.com/questions/44012938/how-to-tell-if-template-type-is-an-instance-of-a-template-class
template <class, template <class, class...> class>
struct is_instance : std::false_type {};

template <class...Ts, template <class, class...> class U>
struct is_instance<U<Ts...>, U> : std::true_type {};


// https://stackoverflow.com/questions/17201329/c11-ways-of-finding-if-a-type-has-member-function-or-supports-operator
template <typename C, typename F, typename = void>
struct is_call_possible : public std::false_type {};

template <typename C, typename R, typename... A>
struct is_call_possible<C, R(A...),
        typename std::enable_if<
                std::is_same<R, void>::value ||
                std::is_convertible<decltype(
                std::declval<C>().operator()(std::declval<A>()...)
                //                ^^^^^^^^^^ replace this with the member you need.
                ), R>::value
        >::type
> : public std::true_type {};

#endif //CLION_PROJ_TRICKS_H
