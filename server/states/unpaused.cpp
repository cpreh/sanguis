#include "unpaused.hpp"
#include "paused.hpp"
#include "../global/context.hpp"
#include "../message_functor.hpp"
#include "../message_event.hpp"
#include "../log.hpp"
#include "../../messages/call/object.hpp"
#include "../../messages/pause.hpp"
#include "../../messages/base.hpp"
#include "../../messages/create.hpp"
#include "../../exception.hpp"
#include "../../tick_event.hpp"
#include <sge/collision/world.hpp>
#include <sge/time/second_f.hpp>

#include <fcppt/math/vector/to_angle.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/vector/is_null.hpp>
#include <fcppt/container/map_impl.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/log/parameters/inherited.hpp>
#include <fcppt/format.hpp>
#include <fcppt/text.hpp>

#include <boost/mpl/vector/vector10.hpp>
#include <ostream>

sanguis::server::states::unpaused::unpaused()
:
	send_timer(
		sge::time::second_f(
			static_cast<sge::time::funit>(0.5)
		)
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
	context<
		running
	>().global_context().player_target(
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
			FCPPT_TEXT("got invalid weapon type in player_change_weapon")
		);

	context<
		running
	>().global_context().player_change_weapon(
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
	context<
		running
	>().global_context().player_angle(
		id,
		e.get<messages::roles::angle>()
	);

	return discard_event();
}

boost::statechart::result
sanguis::server::states::unpaused::operator()(
	net::id_type const id,
	messages::player_start_shooting const &
)
{
	context<
		running
	>().global_context().player_change_shooting(
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
	context<
		running
	>().global_context().player_change_shooting(
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
	context<
		running
	>().global_context().player_direction(
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
	FCPPT_LOG_WARNING(
		log(),
		fcppt::log::_ 
			<< FCPPT_TEXT("received superfluous unpause!")
	);

	return discard_event();
}

boost::statechart::result
sanguis::server::states::unpaused::operator()(
	net::id_type,
	messages::player_pause const &
)
{
	if(
		context<
			running
		>().global_context().player_count()
		> 1u
	)
		return discard_event();

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
	tick_event const &_event
)
{
	context<
		running
	>().global_context().update(
		_event.delta()
	);

	return discard_event();
}

boost::statechart::result
sanguis::server::states::unpaused::react(
	message_event const &m
)
{
	typedef message_functor<
		unpaused,
		boost::statechart::result
	> functor_type;
	
	functor_type mf(
		*this,
		m.id()
	);

	static messages::call::object<
		boost::mpl::vector8<
			messages::player_attack_dest,
			messages::player_rotation,
			messages::player_start_shooting,
			messages::player_stop_shooting,
			messages::player_change_weapon,
			messages::player_unpause,
			messages::player_pause,
			messages::player_direction
		>,
		functor_type
	> dispatcher;

	return dispatcher(
		*m.message(),
		mf,
		std::tr1::bind(
			&unpaused::handle_default_msg,
			this,
			m.id(),
			std::tr1::placeholders::_1
		)
	);
}

fcppt::log::object &
sanguis::server::states::unpaused::log()
{
	static fcppt::log::object log_(
		fcppt::log::parameters::inherited(
			server::log(),
			FCPPT_TEXT("unpaused")
		)
	);

	return log_;
}
