#ifndef SANGUIS_MESSAGES_SERIALIZATION_DISPATCHER_REGISTER_IMPL_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERIALIZATION_DISPATCHER_REGISTER_IMPL_HPP_INCLUDED

#include "dispatcher_register.hpp"
#include "context.hpp"
#include "dispatcher.hpp"
#include "../../exception.hpp"
#include "../../log.hpp"
#include <fcppt/log/headers.hpp>
#include <fcppt/auto_ptr.hpp>
#include <fcppt/format.hpp>
#include <fcppt/text.hpp>
#include <fcppt/string.hpp>
#include <boost/mpl/at.hpp>

template<
	typename T
>
sanguis::messages::serialization::dispatcher_register<T>::dispatcher_register(
	context &ctx)
{
	fcppt::auto_ptr<
		dispatcher_base
	> disp(
		new dispatcher<T>
	);

	typedef typename boost::mpl::at_c<
		typename T::memory_type::types,
		0
	>::type msg_type;

	// TODO: fix this cast here, maybe replace majutsu::constant by an enum wrapper
	if(!ctx.handlers_.insert(
		static_cast<
			types::message::type
		>(msg_type::value),
		disp
	).second)
	{
		fcppt::string const error(
			(fcppt::format(
				FCPPT_TEXT("Message type registered twice: %1%!")
			)
				% static_cast<unsigned>(msg_type::value))
			.str()
		);

		FCPPT_LOG_FATAL(
			log(),
			fcppt::log::_
				<< error
		);

		throw exception(
			error
		);
	}
}

#endif
