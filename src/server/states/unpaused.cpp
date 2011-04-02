#include "unpaused.hpp"
#include "paused.hpp"
#include "../events/disconnect.hpp"
#include "../events/message.hpp"
#include "../events/tick.hpp"
#include "../global/context.hpp"
#include "../message_functor.hpp"
#include "../log.hpp"
#include "../player_id_from_net.hpp"
#include "../../messages/call/object.hpp"
#include "../../messages/pause.hpp"
#include "../../messages/base.hpp"
#include "../../messages/create.hpp"
#include "../../cast_enum.hpp"

#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/container/map_impl.hpp>
#include <fcppt/log/output.hpp>
#include <fcppt/log/warning.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/log/parameters/inherited.hpp>
#include <fcppt/text.hpp>

#include <boost/mpl/vector/vector10.hpp>
#include <ostream>

sanguis::server::states::unpaused::unpaused()
{
}

sanguis::server::states::unpaused::~unpaused()
{
}

boost::statechart::result
sanguis::server::states::unpaused::handle_default_msg(
	server::player_id,
	messages::base const &
)
{
	return forward_event();
}

boost::statechart::result
sanguis::server::states::unpaused::operator()(
	server::player_id const _id,
	messages::player_attack_dest const &_message
)
{
	context<
		running
	>().global_context().player_target(
		_id,
		_message.get<
			messages::roles::attack_dest
		>()
	);

	return discard_event();
}

boost::statechart::result
sanguis::server::states::unpaused::operator()(
	server::player_id const _id,
	messages::player_change_weapon const &_message
)
{
	context<
		running
	>().global_context().player_change_weapon(
		_id,
		SANGUIS_CAST_ENUM(
			weapon_type,
			_message.get<
				messages::roles::weapon
			>()
		)
	);

	return discard_event();
}

boost::statechart::result
sanguis::server::states::unpaused::operator()(
	server::player_id const _id,
	messages::player_rotation const &_message
)
{
	context<
		running
	>().global_context().player_angle(
		_id,
		server::angle(
			_message.get<messages::roles::angle>()
		)
	);

	return discard_event();
}

boost::statechart::result
sanguis::server::states::unpaused::operator()(
	server::player_id const _id,
	messages::player_start_shooting const &
)
{
	context<
		running
	>().global_context().player_change_shooting(
		_id,
		true
	);

	return discard_event();
}

boost::statechart::result
sanguis::server::states::unpaused::operator()(
	server::player_id const _id,
	messages::player_stop_shooting const &
)
{
	context<
		running
	>().global_context().player_change_shooting(
		_id,
		false
	);

	return discard_event();
}

boost::statechart::result
sanguis::server::states::unpaused::operator()(
	server::player_id const _id,
	messages::player_direction const &_message
)
{
	context<
		running
	>().global_context().player_speed(
		_id,
		server::speed(
			_message.get<
				messages::roles::direction
			>()
		)
	);

	return discard_event();
}

boost::statechart::result
sanguis::server::states::unpaused::operator()(
	server::player_id,
	messages::player_unpause const &
)
{
	FCPPT_LOG_WARNING(
		unpaused::log(),
		fcppt::log::_ 
			<< FCPPT_TEXT("received superfluous unpause!")
	);

	return discard_event();
}

boost::statechart::result
sanguis::server::states::unpaused::operator()(
	server::player_id,
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
	events::tick const &_event
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
	events::message const &_message
)
{
	typedef message_functor<
		unpaused,
		boost::statechart::result
	> functor_type;
	
	functor_type functor(
		*this,
		_message.id()
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

	return
		dispatcher(
			*_message.get(),
			functor,
			std::tr1::bind(
				&unpaused::handle_default_msg,
				this,
				server::player_id_from_net(
					_message.id()
				),
				std::tr1::placeholders::_1
			)
		);
}

fcppt::log::object &
sanguis::server::states::unpaused::log()
{
	static fcppt::log::object my_logger(
		fcppt::log::parameters::inherited(
			server::log(),
			FCPPT_TEXT("unpaused")
		)
	);

	return my_logger;
}
