#ifndef SANGUIS_MESSAGES_SERIALIZATION_DISPATCHER_REGISTER_IMPL_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERIALIZATION_DISPATCHER_REGISTER_IMPL_HPP_INCLUDED

#include "dispatcher_register.hpp"
#include "context.hpp"
#include "dispatcher.hpp"
#include <sge/auto_ptr.hpp>
#include <boost/mpl/at.hpp>

template<
	typename T
>
sanguis::messages::serialization::dispatcher_register<T>::dispatcher_register(
	context &ctx)
{
	sge::auto_ptr<
		dispatcher_base
	> disp(
		new dispatcher<T>
	);

	typedef typename boost::mpl::at_c<
		typename T::memory_type::types,
		0
	>::type msg_type;

	ctx.handlers_.insert(
		msg_type::value,
		disp
	);
}

#endif
