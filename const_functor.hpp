#ifndef IDENTITY_FUNCTOR_HPP_INCLUDED
#define IDENTITY_FUNCTOR_HPP_INCLUDED

template<typename T>
struct const_functor_type
{
	typedef T result_type;

	const T t;

	const_functor_type(const T &t) : t(t) {}
	T operator()() const { return t; }
};

template<typename T>
inline const_functor_type<T> const_functor(const T &t)
{
	return const_functor_type<T>(t);
}

#endif
