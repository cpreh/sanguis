#include <sanguis/clock.hpp>
#include <sanguis/log_parameters.hpp>
#include <sanguis/weapon_type.hpp>
#include <sanguis/messages/call/result.hpp>
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
#include <sanguis/messages/roles/attack_dest.hpp>
#include <sanguis/messages/roles/direction.hpp>
#include <sanguis/messages/roles/slowdown.hpp>
#include <sanguis/messages/server/create.hpp>
#include <sanguis/messages/server/pause.hpp>
#include <sanguis/messages/server/slowdown.hpp>
#include <sanguis/server/dispatch.hpp>
#include <sanguis/server/dispatch_default_function.hpp>
#include <sanguis/server/machine.hpp>
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
#include <alda/message/init_record.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unit.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/log/name.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/log/out.hpp>
#include <fcppt/log/warning.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/record/get.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/statechart/result.hpp>
#include <brigand/sequences/list.hpp>
#include <fcppt/config/external_end.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

sanguis::server::states::unpaused::unpaused(
	my_context _ctx
)
:
	my_base(
		_ctx
	),
	log_{
		this->context<
			sanguis::server::machine
		>().log_context(),
		sanguis::server::states::log_location(),
		sanguis::log_parameters(
			fcppt::log::name{
				FCPPT_TEXT("unpaused")
			}
		)
	},
	slowdown_{
		sanguis::clock()
	}
{
	FCPPT_LOG_DEBUG(
		log_,
		fcppt::log::out
			<< FCPPT_TEXT("create")
	)
}

FCPPT_PP_POP_WARNING

sanguis::server::states::unpaused::~unpaused()
{
	FCPPT_LOG_DEBUG(
		log_,
		fcppt::log::out
			<< FCPPT_TEXT("destroy")
	)
}

boost::statechart::result
sanguis::server::states::unpaused::react(
	sanguis::server::events::tick const &_event
)
{
	slowdown_.set(
		_event.slowdown()
	);

	if(
		this->context<
			sanguis::server::machine
		>().process_overflow()
	)
		return
			this->discard_event();

	this->context<
		sanguis::server::states::running
	>().global_context().update(
		_event.delta()
	);

	if(
		slowdown_.update()
	)
		this->context<
			sanguis::server::machine
		>().send_to_all(
			sanguis::messages::server::create(
				alda::message::init_record<
					sanguis::messages::server::slowdown
				>(
					sanguis::messages::roles::slowdown{} =
						_event.slowdown().get()
				)
			)
		);

	return
		this->discard_event();
}

boost::statechart::result
sanguis::server::states::unpaused::react(
	sanguis::server::events::message const &_message
)
{
	auto const handle_default_msg(
		[
			this
		](
			sanguis::server::player_id,
			sanguis::messages::client::base const &
		)
		{
			return
				this->forward_event();
		}
	);

	return
		sanguis::server::dispatch<
			brigand::list<
				sanguis::messages::client::attack_dest,
				sanguis::messages::client::change_world,
				sanguis::messages::client::direction,
				sanguis::messages::client::drop_or_pickup_weapon,
				sanguis::messages::client::pause,
				sanguis::messages::client::reload,
				sanguis::messages::client::start_shooting,
				sanguis::messages::client::stop_shooting,
				sanguis::messages::client::unpause
			>
		>(
			*this,
			_message,
			sanguis::server::dispatch_default_function{
				handle_default_msg
			}
		);
}

sanguis::messages::call::result
sanguis::server::states::unpaused::operator()(
	sanguis::server::player_id const _id,
	sanguis::messages::client::attack_dest const &_message
)
{
	this->context<
		sanguis::server::states::running
	>().global_context().player_target(
		_id,
		fcppt::record::get<
			sanguis::messages::roles::attack_dest
		>(
			_message.get()
		)
	);

	return
		sanguis::messages::call::result(
			this->discard_event()
		);
}

sanguis::messages::call::result
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
		sanguis::messages::call::result(
			this->discard_event()
		);
}

sanguis::messages::call::result
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
			fcppt::record::get<
				sanguis::messages::roles::direction
			>(
				_message.get()
			)
		)
	);

	return
		sanguis::messages::call::result(
			this->discard_event()
		);
}

sanguis::messages::call::result
sanguis::server::states::unpaused::operator()(
	sanguis::server::player_id const _id,
	sanguis::messages::client::drop_or_pickup_weapon const &_message
)
{
	this->context<
		sanguis::server::states::running
	>().global_context().player_drop_or_pickup_weapon(
		_id,
		_message.get()
	);

	return
		sanguis::messages::call::result(
			this->discard_event()
		);
}

sanguis::messages::call::result
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
			sanguis::messages::call::result(
				this->discard_event()
			);

	this->context<
		sanguis::server::machine
	>().send_to_all(
		sanguis::messages::server::create(
			sanguis::messages::server::pause{
				fcppt::unit{}
			}
		)
	);

	return
		sanguis::messages::call::result(
			this->transit<
				sanguis::server::states::paused
			>()
		);
}

sanguis::messages::call::result
sanguis::server::states::unpaused::operator()(
	sanguis::server::player_id const _id,
	sanguis::messages::client::reload const &_message
)
{
	this->context<
		sanguis::server::states::running
	>().global_context().player_reload(
		_id,
		_message.get()
	);

	return
		sanguis::messages::call::result(
			this->discard_event()
		);
}

sanguis::messages::call::result
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
		_message.get()
	);

	return
		sanguis::messages::call::result(
			this->discard_event()
		);
}

sanguis::messages::call::result
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
		_message.get()
	);

	return
		sanguis::messages::call::result(
			this->discard_event()
		);
}

sanguis::messages::call::result
sanguis::server::states::unpaused::operator()(
	sanguis::server::player_id,
	sanguis::messages::client::unpause const &
)
{
	FCPPT_LOG_WARNING(
		log_,
		fcppt::log::out
			<< FCPPT_TEXT("received superfluous unpause!")
	)

	return
		sanguis::messages::call::result(
			this->discard_event()
		);
}
