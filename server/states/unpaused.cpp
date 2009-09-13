#include "unpaused.hpp"
#include "paused.hpp"
#include "../entities/player.hpp"
#include "../entities/entity.hpp"
#include "../entities/property.hpp"
#include "../message_functor.hpp"
#include "../log.hpp"
#include "../../messages/pause.hpp"
#include "../../messages/base.hpp"
#include "../../messages/unwrap.hpp"
#include "../../messages/create.hpp"
#include "../../exception.hpp"

#include <sge/math/vector/to_angle.hpp>
#include <sge/math/vector/arithmetic.hpp>
#include <sge/math/vector/basic_impl.hpp>
#include <sge/math/vector/is_null.hpp>
#include <sge/container/map_impl.hpp>
#include <sge/collision/world.hpp>
#include <sge/log/headers.hpp>
#include <sge/format.hpp>
#include <sge/text.hpp>
#include <sge/time/resolution.hpp>
#include <sge/time/second_f.hpp>

#include <boost/lexical_cast.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/bind.hpp>
#include <ostream>

sanguis::server::states::unpaused::unpaused()
:
	send_timer(
		sge::time::second_f(
			static_cast<sge::time::funit>(0.5)
		)
	),
	global_context_(
		context<
			running
		>().global_context()
	)
{}

boost::statechart::result
sanguis::server::states::unpaused::handle_default_msg(
	net::id_type,
	messages::base const &
)
{
	return forward_event();
}

boost::statechart::result
sanguis::server::states::unpaused::operator()(
	net::id_type const id,
	messages::player_attack_dest const &e
)
{
	global_context_.player_target(
		id,
		e.get<
			messages::roles::attack_dest
		>()
	);

	return discard_event();
}

boost::statechart::result
sanguis::server::states::unpaused::operator()(
	net::id_type const id,
	messages::player_change_weapon const &e
)
{
	weapon_type::type const wt(
		static_cast<
			weapon_type::type
		>(
			e.get<messages::roles::weapon>()
		)
	);

	if (wt > weapon_type::size)
		throw exception(
			SGE_TEXT("got invalid weapon type in player_change_weapon")
		);

	global_context_.player_change_weapon(
		id,
		wt
	);

	return discard_event();
}

boost::statechart::result
sanguis::server::states::unpaused::operator()(
	net::id_type const id,
	messages::player_rotation const &e
)
{
	global_context_.player_angle(
		id,
		e.get<messages::roles::angle>()
	);

	/*send(
		message_convert::rotate(
			player_
		)
	);*/

	return discard_event();
}

boost::statechart::result
sanguis::server::states::unpaused::operator()(
	net::id_type const id,
	messages::player_start_shooting const &
)
{
	global_context_.player_change_shooting(
		id,
		true
	);

	return discard_event();
}

boost::statechart::result
sanguis::server::states::unpaused::operator()(
	net::id_type const id,
	messages::player_stop_shooting const &
)
{
	global_context_.player_change_shooting(
		id,
		false
	);

	return discard_event();
}

boost::statechart::result
sanguis::server::states::unpaused::operator()(
	net::id_type const id,
	messages::player_direction const &e
)
{
	global_context_.player_direction(
		id,
		e.get<
			messages::roles::direction
		>()
	);

	return discard_event();
}

boost::statechart::result
sanguis::server::states::unpaused::operator()(
	net::id_type,
	messages::player_unpause const &
)
{
	SGE_LOG_WARNING(
		log(),
		sge::log::_1 
			<< SGE_TEXT("received superfluous unpause!")
	);

	return discard_event();
}

boost::statechart::result
sanguis::server::states::unpaused::operator()(
	net::id_type,
	messages::player_pause const &
)
{
	context<
		machine
	>().send_to_all(
		messages::create(
			messages::pause()
		)
	);
	
	return transit<paused>();
}

boost::statechart::result
sanguis::server::states::unpaused::react(
	tick_event const &t
)
{
	global_context_.update(
		t.delta()
	);

	return discard_event();
}

boost::statechart::result
sanguis::server::states::unpaused::react(
	message_event const &m)
{
	message_functor<
		unpaused,
		boost::statechart::result
	> mf(
		*this,
		m.id()
	);

	return messages::unwrap<
		boost::mpl::vector<
			messages::player_attack_dest,
			messages::player_rotation,
			messages::player_start_shooting,
			messages::player_stop_shooting,
			messages::player_change_weapon,
			messages::player_unpause,
			messages::player_pause,
			messages::player_direction
		>,
		boost::statechart::result
	>(
		mf,
		*m.message(),
		boost::bind(
			&unpaused::handle_default_msg,
			this,
			m.id(),
			_1
		)
	);
}

sge::log::logger &
sanguis::server::states::unpaused::log()
{
	static sge::log::logger log_(
		server::log(),
		SGE_TEXT("unpaused: "),
		true
	);

	return log_;
}
