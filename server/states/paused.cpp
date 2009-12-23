#include "paused.hpp"
#include "unpaused.hpp"
#include "../message_functor.hpp"
#include "../message_event.hpp"
#include "../log.hpp"
#include "../../messages/call/object.hpp"
#include "../../messages/unpause.hpp"
#include "../../messages/create.hpp"
#include "../../messages/base.hpp"
#include <fcppt/log/parameters/inherited.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/iconv.hpp>
#include <fcppt/text.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <tr1/functional>
#include <ostream>

// reactions
boost::statechart::result
sanguis::server::states::paused::react(
	tick_event const &)
{
	return discard_event();
}

boost::statechart::result
sanguis::server::states::paused::react(
	message_event const &m
)
{
	typedef message_functor<
		paused,
		boost::statechart::result
	> functor_type;
	
	functor_type mf(
		*this,
		m.id()
	);

	static messages::call::object<
		boost::mpl::vector2<
			messages::player_pause,
			messages::player_unpause
		>,
		functor_type
	> dispatcher;
	
	return dispatcher(
		*m.message(),
		mf,
		std::tr1::bind(
			&paused::handle_default_msg,
			this,
			m.id(),
			std::tr1::placeholders::_1
		)
	);
}

boost::statechart::result
sanguis::server::states::paused::operator()(
	net::id_type,
	messages::player_unpause const &
)
{
	context<machine>().send_to_all(
		messages::create(
			messages::unpause()
		)
	);

	return transit<unpaused>();
}

boost::statechart::result
sanguis::server::states::paused::operator()(
	net::id_type,
	messages::player_pause const &)
{
	FCPPT_LOG_WARNING(
		log(),
		fcppt::log::_
			<< FCPPT_TEXT("got superfluous pause"));;
	return discard_event();
}

boost::statechart::result
sanguis::server::states::paused::handle_default_msg(
	net::id_type,
	messages::base const &)
{
	return forward_event();
}

fcppt::log::object &
sanguis::server::states::paused::log()
{
	static fcppt::log::object log_(
		fcppt::log::parameters::inherited(
			server::log(),
			FCPPT_TEXT("paused")
		)
	);
	return log_;
}
