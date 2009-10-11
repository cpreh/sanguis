#include "paused.hpp"
#include "unpaused.hpp"
#include "../message_functor.hpp"
#include "../message_event.hpp"
#include "../log.hpp"
#include "../../messages/unpause.hpp"
#include "../../messages/create.hpp"
#include "../../messages/unwrap.hpp"
#include "../../messages/base.hpp"
#include <sge/log/parameters/inherited.hpp>
#include <sge/log/headers.hpp>
#include <sge/log/object.hpp>
#include <sge/iconv.hpp>
#include <sge/text.hpp>
#include <boost/mpl/vector.hpp>
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
	message_functor<
		paused,
		boost::statechart::result
	> mf(
		*this,
		m.id()
	);

	return messages::unwrap<
		boost::mpl::vector<
			messages::player_pause,
			messages::player_unpause
		>,
		boost::statechart::result
	>(
		mf,
		*m.message(),
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
	SGE_LOG_WARNING(
		log(),
		sge::log::_
			<< SGE_TEXT("got superfluous pause"));;
	return discard_event();
}

boost::statechart::result
sanguis::server::states::paused::handle_default_msg(
	net::id_type,
	messages::base const &)
{
	return forward_event();
}

sge::log::object &
sanguis::server::states::paused::log()
{
	static sge::log::object log_(
		sge::log::parameters::inherited(
			server::log(),
			SGE_TEXT("paused")
		)
	);
	return log_;
}
