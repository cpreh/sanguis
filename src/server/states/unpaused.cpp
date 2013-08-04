#include <sanguis/log_parameters.hpp>
#include <sanguis/weapon_type.hpp>
#include <sanguis/messages/base.hpp>
#include <sanguis/messages/create.hpp>
#include <sanguis/messages/pause.hpp>
#include <sanguis/messages/player_attack_dest.hpp>
#include <sanguis/messages/player_change_world.hpp>
#include <sanguis/messages/player_direction.hpp>
#include <sanguis/messages/player_pause.hpp>
#include <sanguis/messages/player_position.hpp>
#include <sanguis/messages/player_start_shooting.hpp>
#include <sanguis/messages/player_stop_shooting.hpp>
#include <sanguis/messages/player_unpause.hpp>
#include <sanguis/messages/call/object.hpp>
#include <sanguis/messages/roles/attack_dest.hpp>
#include <sanguis/messages/roles/center.hpp>
#include <sanguis/messages/roles/direction.hpp>
#include <sanguis/messages/roles/weapon.hpp>
#include <sanguis/server/center.hpp>
#include <sanguis/server/machine.hpp>
#include <sanguis/server/message_functor.hpp>
#include <sanguis/server/player_id.hpp>
#include <sanguis/server/speed.hpp>
#include <sanguis/server/events/disconnect.hpp>
#include <sanguis/server/events/message.hpp>
#include <sanguis/server/events/tick.hpp>
#include <sanguis/server/global/context.hpp>
#include <sanguis/server/states/log_location.hpp>
#include <sanguis/server/states/paused.hpp>
#include <sanguis/server/states/running.hpp>
#include <sanguis/server/states/unpaused.hpp>
#include <fcppt/cast_to_enum.hpp>
#include <fcppt/text.hpp>
#include <fcppt/container/map_impl.hpp>
#include <fcppt/log/location.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/log/output.hpp>
#include <fcppt/log/warning.hpp>
#include <fcppt/log/parameters/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <boost/statechart/result.hpp>
#include <functional>
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
	sanguis::server::player_id,
	sanguis::messages::base const &
)
{
	return
		this->forward_event();
}

boost::statechart::result
sanguis::server::states::unpaused::operator()(
	sanguis::server::player_id const _id,
	sanguis::messages::player_attack_dest const &_message
)
{
	this->context<
		sanguis::server::states::running
	>().global_context().player_target(
		_id,
		_message.get<
			sanguis::messages::roles::attack_dest
		>()
	);

	return
		this->discard_event();
}

boost::statechart::result
sanguis::server::states::unpaused::operator()(
	sanguis::server::player_id const _id,
	sanguis::messages::player_change_world const &
)
{
	this->context<
		sanguis::server::states::running
	>().global_context().player_change_world(
		_id
	);

	return
		this->discard_event();
}

boost::statechart::result
sanguis::server::states::unpaused::operator()(
	sanguis::server::player_id const _id,
	sanguis::messages::player_direction const &_message
)
{
	this->context<
		sanguis::server::states::running
	>().global_context().player_speed(
		_id,
		sanguis::server::speed(
			_message.get<
				sanguis::messages::roles::direction
			>()
		)
	);

	return
		this->discard_event();
}

boost::statechart::result
sanguis::server::states::unpaused::operator()(
	sanguis::server::player_id,
	sanguis::messages::player_pause const &
)
{
	if(
		this->context<
			sanguis::server::states::running
		>().global_context().player_count()
		> 1u
	)
		return
			this->discard_event();

	this->context<
		sanguis::server::machine
	>().send_to_all(
		*sanguis::messages::create(
			sanguis::messages::pause()
		)
	);

	return
		this->transit<
			sanguis::server::states::paused
		>();
}

boost::statechart::result
sanguis::server::states::unpaused::operator()(
	sanguis::server::player_id const _id,
	sanguis::messages::player_position const &_message
)
{
	this->context<
		sanguis::server::states::running
	>().global_context().player_position(
		_id,
		sanguis::server::center(
			_message.get<
				sanguis::messages::roles::center
			>()
		)
	);

	return
		this->discard_event();
}

boost::statechart::result
sanguis::server::states::unpaused::operator()(
	sanguis::server::player_id const _id,
	sanguis::messages::player_start_shooting const &
)
{
	this->context<
		sanguis::server::states::running
	>().global_context().player_change_shooting(
		_id,
		true
	);

	return
		this->discard_event();
}

boost::statechart::result
sanguis::server::states::unpaused::operator()(
	sanguis::server::player_id const _id,
	sanguis::messages::player_stop_shooting const &
)
{
	this->context<
		sanguis::server::states::running
	>().global_context().player_change_shooting(
		_id,
		false
	);

	return
		this->discard_event();
}

boost::statechart::result
sanguis::server::states::unpaused::operator()(
	sanguis::server::player_id,
	sanguis::messages::player_unpause const &
)
{
	FCPPT_LOG_WARNING(
		::logger,
		fcppt::log::_
			<< FCPPT_TEXT("received superfluous unpause!")
	);

	return
		this->discard_event();
}

boost::statechart::result
sanguis::server::states::unpaused::react(
	sanguis::server::events::tick const &_event
)
{
	this->context<
		sanguis::server::states::running
	>().global_context().update(
		_event.delta()
	);

	return
		this->discard_event();
}

boost::statechart::result
sanguis::server::states::unpaused::react(
	sanguis::server::events::message const &_message
)
{
	if(
		!this->context<
			sanguis::server::states::running
		>().global_context().has_player(
			_message.id()
		)
	)
		return
			this->forward_event();

	typedef sanguis::server::message_functor<
		sanguis::server::states::unpaused,
		boost::statechart::result
	> functor_type;

	functor_type functor(
		*this,
		_message.id()
	);

	static sanguis::messages::call::object<
		boost::mpl::vector8<
			sanguis::messages::player_attack_dest,
			sanguis::messages::player_start_shooting,
			sanguis::messages::player_stop_shooting,
			sanguis::messages::player_change_world,
			sanguis::messages::player_unpause,
			sanguis::messages::player_pause,
			sanguis::messages::player_direction,
			sanguis::messages::player_position
		>,
		functor_type
	> dispatcher;

	return
		dispatcher(
			*_message.get(),
			functor,
			std::bind(
				&sanguis::server::states::unpaused::handle_default_msg,
				this,
				_message.id(),
				std::placeholders::_1
			)
		);
}
