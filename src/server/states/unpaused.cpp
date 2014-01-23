#include <sanguis/log_parameters.hpp>
#include <sanguis/weapon_type.hpp>
#include <sanguis/messages/adapted_types/is_primary_weapon.hpp>
#include <sanguis/messages/client/attack_dest.hpp>
#include <sanguis/messages/client/base.hpp>
#include <sanguis/messages/client/change_world.hpp>
#include <sanguis/messages/client/direction.hpp>
#include <sanguis/messages/client/drop_or_pickup_weapon.hpp>
#include <sanguis/messages/client/pause.hpp>
#include <sanguis/messages/client/reload.hpp>
#include <sanguis/messages/client/start_shooting.hpp>
#include <sanguis/messages/client/stop_shooting.hpp>
#include <sanguis/messages/client/unpause.hpp>
#include <sanguis/messages/client/call/object.hpp>
#include <sanguis/messages/roles/attack_dest.hpp>
#include <sanguis/messages/roles/direction.hpp>
#include <sanguis/messages/server/create.hpp>
#include <sanguis/messages/server/pause.hpp>
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
#include <fcppt/log/_.hpp>
#include <fcppt/log/location.hpp>
#include <fcppt/log/object.hpp>
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
	sanguis::messages::client::base const &
)
{
	return
		this->forward_event();
}

boost::statechart::result
sanguis::server::states::unpaused::operator()(
	sanguis::server::player_id const _id,
	sanguis::messages::client::attack_dest const &_message
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
	sanguis::messages::client::change_world const &
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
	sanguis::messages::client::direction const &_message
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
	sanguis::server::player_id const _id,
	sanguis::messages::client::drop_or_pickup_weapon const &_message
)
{
	this->context<
		sanguis::server::states::running
	>().global_context().player_drop_or_pickup_weapon(
		_id,
		_message.get<
			sanguis::messages::adapted_types::is_primary_weapon
		>()
	);

	return
		this->discard_event();
}

boost::statechart::result
sanguis::server::states::unpaused::operator()(
	sanguis::server::player_id,
	sanguis::messages::client::pause const &
)
{
	if(
		this->context<
			sanguis::server::states::running
		>().global_context().multiple_players()
	)
		return
			this->discard_event();

	this->context<
		sanguis::server::machine
	>().send_to_all(
		*sanguis::messages::server::create(
			sanguis::messages::server::pause()
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
	sanguis::messages::client::reload const &_message
)
{
	this->context<
		sanguis::server::states::running
	>().global_context().player_reload(
		_id,
		_message.get<
			sanguis::messages::adapted_types::is_primary_weapon
		>()
	);

	return
		this->discard_event();
}

boost::statechart::result
sanguis::server::states::unpaused::operator()(
	sanguis::server::player_id const _id,
	sanguis::messages::client::start_shooting const &_message
)
{
	this->context<
		sanguis::server::states::running
	>().global_context().player_change_shooting(
		_id,
		true,
		_message.get<
			sanguis::messages::adapted_types::is_primary_weapon
		>()
	);

	return
		this->discard_event();
}

boost::statechart::result
sanguis::server::states::unpaused::operator()(
	sanguis::server::player_id const _id,
	sanguis::messages::client::stop_shooting const &_message
)
{
	this->context<
		sanguis::server::states::running
	>().global_context().player_change_shooting(
		_id,
		false,
		_message.get<
			sanguis::messages::adapted_types::is_primary_weapon
		>()
	);

	return
		this->discard_event();
}

boost::statechart::result
sanguis::server::states::unpaused::operator()(
	sanguis::server::player_id,
	sanguis::messages::client::unpause const &
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

	static sanguis::messages::client::call::object<
		boost::mpl::vector9<
			sanguis::messages::client::attack_dest,
			sanguis::messages::client::change_world,
			sanguis::messages::client::direction,
			sanguis::messages::client::drop_or_pickup_weapon,
			sanguis::messages::client::pause,
			sanguis::messages::client::reload,
			sanguis::messages::client::start_shooting,
			sanguis::messages::client::stop_shooting,
			sanguis::messages::client::unpause
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
