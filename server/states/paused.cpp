#include "paused.hpp"
#include "unpaused.hpp"
#include "../message_functor.hpp"
#include "../log.hpp"
#include "../entities/entity.hpp"
#include "../../messages/unpause.hpp"
#include "../../messages/create.hpp"
#include "../../messages/unwrap.hpp"
#include "../../messages/base.hpp"

#include <sge/iconv.hpp>
#include <sge/text.hpp>
#include <sge/log/headers.hpp>

#include <boost/bind.hpp>
#include <boost/mpl/vector.hpp>

#include <typeinfo>
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
	message_event const &m)
{
	message_functor<paused,boost::statechart::result> mf(*this,m.id());

	return messages::unwrap<
		boost::mpl::vector<
			messages::player_pause,
			messages::player_unpause
		>,
		boost::statechart::result
	>(
		mf,
		*m.message(),
		boost::bind(
			&paused::handle_default_msg,
			this,
			m.id(),
			_1
		)
	);
}

boost::statechart::result
sanguis::server::states::paused::operator()(
	net::id_type,
	messages::player_unpause const &)
{
	context<running>().environment().send(
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
		sge::log::_1
			<< SGE_TEXT("got superfluous pause"));;
	return discard_event();
}

boost::statechart::result
sanguis::server::states::paused::handle_default_msg(
	net::id_type,
	messages::base const &m)
{
	return forward_event();
}

sge::log::logger &
sanguis::server::states::paused::log()
{
	static sge::log::logger log_(
		server::log(),
		SGE_TEXT("paused: "),
		true
	);
	return log_;
}
