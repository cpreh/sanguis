#ifndef MESSAGE_FUNCTOR_HPP_INCLUDED
#define MESSAGE_FUNCTOR_HPP_INCLUDED

#include "../net/types.hpp"

template<typename T,typename R>
struct message_functor
{
	T &t;
	net::id_type id;

	message_functor(T &t,const net::id_type id) : t(t),id(id) {}

	template<typename U>
	R operator()(U m) { return t(id,m); }
};

#endif
