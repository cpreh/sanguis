#ifndef SANGUIS_MESSAGES_SERIALIZATION_DISPATCHER_REGISTER_IMPL_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERIALIZATION_DISPATCHER_REGISTER_IMPL_HPP_INCLUDED

#include <sanguis/messages/serialization/dispatcher_register.hpp>
#include <sanguis/messages/serialization/context.hpp>
#include <sanguis/messages/serialization/dispatcher.hpp>
#include <sanguis/exception.hpp>
#include <sanguis/log.hpp>
#include <fcppt/container/ptr/insert_unique_ptr_map.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/unique_ptr.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/format.hpp>
#include <fcppt/text.hpp>
#include <fcppt/string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/at.hpp>
#include <fcppt/config/external_end.hpp>

template<
	typename T
>
sanguis::messages::serialization::dispatcher_register<T>::dispatcher_register(
	context &_ctx
)
{
	typedef fcppt::unique_ptr<
		dispatcher_base
	> dispatcher_base_unique_ptr;

	typedef typename boost::mpl::at_c<
		typename T::memory_type::types,
		0
	>::type msg_type;

	// TODO: fix this cast here, maybe replace majutsu::constant by an enum wrapper
	if(
		!fcppt::container::ptr::insert_unique_ptr_map(
			_ctx.handlers_,
			static_cast<
				types::message::type
			>(
				msg_type::value
			),
			dispatcher_base_unique_ptr(
				fcppt::make_unique_ptr<
					dispatcher<T>
				>()
			)
		).second
	)
	{
		fcppt::string const error(
			(
				fcppt::format(
					FCPPT_TEXT("Message type registered twice: %1%!")
				)
				% static_cast<
					unsigned
				>(
					msg_type::value
				)
			)
			.str()
		);

		FCPPT_LOG_FATAL(
			sanguis::log(),
			fcppt::log::_
				<< error
		);

		throw sanguis::exception(
			error
		);
	}
}

template<
	typename T
>
sanguis::messages::serialization::dispatcher_register<T>::~dispatcher_register()
{
}

#endif
