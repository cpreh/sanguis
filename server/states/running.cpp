#include "running.hpp"
#include "unpaused.hpp"
#include "../global/context.hpp"
#include "../message_functor.hpp"
#include "../message_event.hpp"
#include "../log.hpp"
#include "../../connect_state.hpp"
#include "../../messages/unwrap.hpp"
#include "../../messages/highscore.hpp"
#include "../../messages/create.hpp"
#include "../../load/context.hpp"
#include <sge/container/map_impl.hpp>
#include <sge/log/parameters/inherited.hpp>
#include <sge/log/headers.hpp>
#include <sge/utf8/convert.hpp>
#include <sge/text.hpp>
#include <sge/type_info.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/foreach.hpp>
#include <tr1/functional>
#include <tr1/random>
#include <algorithm>
#include <ostream>

sanguis::server::states::running::running(
	my_context ctx
)
:
	my_base(ctx),
	global_context_(
		new global::context(
			std::tr1::bind(
				&machine::send_unicast,
				&context<
					machine
				>(),
				std::tr1::placeholders::_1,
				std::tr1::placeholders::_2
			),
			context<machine>().collision_system(),
			context<machine>().resources().models()
		)
	)
{
	SGE_LOG_DEBUG(
		log(),
		sge::log::_
			<< SGE_TEXT("constructor, listening")
	);

	context<machine>().listen();
}

sanguis::server::states::running::~running()
{}

boost::statechart::result
sanguis::server::states::running::react(
	message_event const &m
)
{
	message_functor<
		running,
		boost::statechart::result
	> mf(
		*this,
		m.id()
	);

	return messages::unwrap<
		boost::mpl::vector<
			messages::client_info,
			messages::connect,
			messages::disconnect,
			messages::player_cheat,
			messages::player_choose_perk
		>,
		boost::statechart::result
	>(
		mf,
		*m.message(),
		std::tr1::bind(
			&running::handle_default_msg,
			this,
			m.id(),
			std::tr1::placeholders::_1
		)
	);
}

boost::statechart::result
sanguis::server::states::running::operator()(
	net::id_type const net_id,
	messages::client_info const &m
)
{
	global_context_->insert_player(
		0, // FIXME: which world id?
		net_id,
		sge::utf8::convert(
			m.get<
				messages::string
			>()
		),
		state_cast<
			unpaused const *
		>()
		?
			connect_state::unpaused
		:
			connect_state::paused
	);

	return discard_event();
}

boost::statechart::result
sanguis::server::states::running::operator()(
	net::id_type const id,
	messages::connect const &
)
{
	SGE_LOG_INFO(
		log(),
		sge::log::_
			<< SGE_TEXT("client ")
			<< id
			<< SGE_TEXT(" connected")
	);

	return discard_event();
}

boost::statechart::result
sanguis::server::states::running::operator()(
	net::id_type const id,
	messages::disconnect const &
)
{
	SGE_LOG_INFO(
		log(),
		sge::log::_
			<< SGE_TEXT("client with id ")
			<< id
			<< SGE_TEXT(" disconnected")
	);

	global_context_->player_disconnect(
		id
	);

	return discard_event();
}

boost::statechart::result
sanguis::server::states::running::operator()(
	net::id_type const id,
	messages::player_cheat const &p)
{
	global_context_->player_cheat(
		id,
		// TODO: sanitize the input!
		static_cast<
			cheat_type::type
		>(
			p.get<
				messages::roles::cheat
			>()
		)
	);

	return discard_event();
}

boost::statechart::result
sanguis::server::states::running::operator()(
	net::id_type const id,
	messages::player_choose_perk const &p
)
{
	global_context_->player_choose_perk(
		id,
		// FIXME: sanitize the input!
		static_cast<
			perk_type::type
		>(
			p.get<
				messages::roles::perk
			>()
		)
	);

	return discard_event();

}

sanguis::server::global::context &
sanguis::server::states::running::global_context()
{
	return *global_context_;
}

boost::statechart::result
sanguis::server::states::running::handle_default_msg(
	net::id_type const id,
	messages::base const &m
)
{
#if 0
	SGE_LOG_WARNING(
		log(),
		sge::log::_
			<< SGE_TEXT("received unexpected message from id ")
			<< id
			<< SGE_TEXT(" of type ")
			<< sge::type_info(typeid(m)).name());
#endif
	return discard_event();
}

sge::log::object &
sanguis::server::states::running::log()
{
	static sge::log::object log_(
		sge::log::parameters::inherited(
			server::log(),
			SGE_TEXT("running")
		)
	);
	return log_;
}
