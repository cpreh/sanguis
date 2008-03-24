#ifndef MESSAGE_FUNCTOR_HPP_INCLUDED
#define MESSAGE_FUNCTOR_HPP_INCLUDED

#include "../net/types.hpp"
#include "../messages/base.hpp"
#include <boost/statechart/result.hpp>
#include <functional>

template<typename T>
//struct message_functor : public std::unary_function<boost::statechart::result,sanguis::messages::base>
struct message_functor
{
	T &t;
	net::id_type id;

	message_functor(T &t,const net::id_type id) : t(t),id(id) 
	{
		sge::cout << SGE_TEXT("server: message functor id: ") << id << SGE_TEXT("\n");
	}

	template<typename U>
	boost::statechart::result operator()(U m)
	{
		sge::cout << SGE_TEXT("server: message functor call id: ") << id << SGE_TEXT("\n");
		return t(id,m);
	}
};

#endif
