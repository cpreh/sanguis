#include <sanguis/server/states/unpaused.hpp>
#include <sanguis/server/states/paused.hpp>
#include <sanguis/server/states/log_location.hpp>
#include <sanguis/server/events/disconnect.hpp>
#include <sanguis/server/events/message.hpp>
#include <sanguis/server/events/tick.hpp>
#include <sanguis/server/global/context.hpp>
#include <sanguis/server/message_functor.hpp>
#include <sanguis/server/player_id_from_net.hpp>
#include <sanguis/messages/call/object.hpp>
#include <sanguis/messages/pause.hpp>
#include <sanguis/messages/base.hpp>
#include <sanguis/messages/create.hpp>
#include <sanguis/cast_enum.hpp>
#include <sanguis/log_parameters.hpp>
#include <fcppt/math/vector/object_impl.hpp>
#include <fcppt/container/map_impl.hpp>
#include <fcppt/log/parameters/object.hpp>
#include <fcppt/log/location.hpp>
#include <fcppt/log/output.hpp>
#include <fcppt/log/warning.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <ostream>
#include <fcppt/config/external_end.hpp>

namespace
{

fcppt::log::object logger(
	sanguis::log_parameters(
		sanguis::server::states::log_location()
		/
		FCPPT_TEXT("unpaused")
	)
);

}

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
		::logger,
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
		*messages::create(
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
		boost::mpl::vector7<
			messages::player_attack_dest,
			messages::player_start_shooting,
			messages::player_stop_shooting,
			messages::player_change_weapon,
			messages::player_unpause,
			messages::player_pause,
			messages::player_direction
		>,
		functor_type
	>::type dispatcher;

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
