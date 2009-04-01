#ifndef SANGUIS_MESSAGES_SERIALIZATION_DISPATCHER_REGISTER_IMPL_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERIALIZATION_DISPATCHER_REGISTER_IMPL_HPP_INCLUDED

#include "dispatcher_register.hpp"
#include "context.hpp"
#include <sge/auto_ptr.hpp>

template<
	typename T
>
sanguis::messages::serialization::dispatcher_register::dispatcher_register(
	context &ctx,
	types::message::type const idx)
{
	sge::auto_ptr<
		dispatcher_base
	> disp(
		new dispatcher<T>
	);

	ctx.handlers_.insert(
		idx,
		disp
	);
}

#endif
