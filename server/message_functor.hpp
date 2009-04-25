#ifndef SANGUIS_SERVER_MESSAGE_FUNCTOR_HPP_INCLUDED
#define SANGUIS_SERVER_MESSAGE_FUNCTOR_HPP_INCLUDED

#include "../net/id_type.hpp"

template<typename T,typename R>
struct message_functor
{
	T &t;
	sanguis::net::id_type id;

	message_functor(T &t,const sanguis::net::id_type id) : t(t),id(id) {}

	template<typename U>
	R operator()(U m) { return t(id,m); }
};

#endif
