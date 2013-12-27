#include <sanguis/connect_state.hpp>
#include <sanguis/log_parameters.hpp>
#include <sanguis/string_vector.hpp>
#include <sanguis/to_console_arg_list.hpp>
#include <sanguis/world_id.hpp>
#include <sanguis/messages/base_fwd.hpp>
#include <sanguis/messages/client_info.hpp>
#include <sanguis/messages/console_command.hpp>
#include <sanguis/messages/create.hpp>
#include <sanguis/messages/player_cheat.hpp>
#include <sanguis/messages/player_choose_perk.hpp>
#include <sanguis/messages/adapted_types/string.hpp>
#include <sanguis/messages/adapted_types/string_vector.hpp>
#include <sanguis/messages/call/object.hpp>
#include <sanguis/messages/roles/cheat.hpp>
#include <sanguis/messages/roles/perk.hpp>
#include <sanguis/messages/serialization/convert_string_vector.hpp>
#include <sanguis/server/machine.hpp>
#include <sanguis/server/make_unicast_callback.hpp>
#include <sanguis/server/make_send_callback.hpp>
#include <sanguis/server/message_functor.hpp>
#include <sanguis/server/player_id.hpp>
#include <sanguis/server/player_id_from_net.hpp>
#include <sanguis/server/events/disconnect.hpp>
#include <sanguis/server/events/message.hpp>
#include <sanguis/server/events/tick.hpp>
#include <sanguis/server/global/context.hpp>
#include <sanguis/server/states/paused.hpp>
#include <sanguis/server/states/running.hpp>
#include <sanguis/server/states/unpaused.hpp>
#include <sanguis/server/states/log_location.hpp>
#include <sge/charconv/utf8_string_to_fcppt.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/log/error.hpp>
#include <fcppt/log/info.hpp>
#include <fcppt/log/location.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/log/parameters/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <boost/statechart/result.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


namespace
{

fcppt::log::object logger(
	sanguis::log_parameters(
		sanguis::server::states::log_location()
		/
		FCPPT_TEXT("running")
	)
);

}

sanguis::server::states::running::running(
	my_context _ctx
)
:
	my_base(
		_ctx
	),
	console_(
		sanguis::server::make_send_callback(
			this->context<
				sanguis::server::machine
			>()
		),
		sanguis::server::make_unicast_callback(
			this->context<
				sanguis::server::machine
			>()
		)
	),
	global_context_(
		fcppt::make_unique_ptr<
			sanguis::server::global::context
		>(
			sanguis::server::make_unicast_callback(
				this->context<
					sanguis::server::machine
				>()
			),
			this->context<
				sanguis::server::machine
			>().resources(),
			console_
		)
	)
{
	FCPPT_LOG_DEBUG(
		::logger,
		fcppt::log::_
			<< FCPPT_TEXT("constructor, listening")
	);

	this->context<
		sanguis::server::machine
	>().listen();
}

sanguis::server::states::running::~running()
{
}

boost::statechart::result
sanguis::server::states::running::react(
	sanguis::server::events::message const &_message
)
{
	typedef sanguis::server::message_functor<
		sanguis::server::states::running,
		boost::statechart::result
	> functor_type;

	functor_type functor(
		*this,
		_message.id()
	);

	static sanguis::messages::call::object<
		boost::mpl::vector4<
			sanguis::messages::client_info,
			sanguis::messages::console_command,
			sanguis::messages::player_cheat,
			sanguis::messages::player_choose_perk
		>,
		functor_type
	> dispatcher;

	return
		dispatcher(
			*_message.get(),
			functor,
			std::bind(
				&sanguis::server::states::running::handle_default_msg,
				this,
				_message.id(),
				std::placeholders::_1
			)
		);
}

boost::statechart::result
sanguis::server::states::running::react(
	sanguis::server::events::disconnect const &_message
)
{
	FCPPT_LOG_INFO(
		::logger,
		fcppt::log::_
			<< FCPPT_TEXT("client with id ")
			<< _message.id()
			<< FCPPT_TEXT(" disconnected")
	);

	// We would have to disconnect all players associated with that connection here
	global_context_->player_disconnect(
		sanguis::server::player_id_from_net(
			_message.id()
		)
	);

	return
		this->discard_event();
}

boost::statechart::result
sanguis::server::states::running::operator()(
	sanguis::server::player_id const _id,
	sanguis::messages::client_info const &_message
)
{
	if(
		this->global_context().has_player(
			_id
		)
	)
		return
			this->discard_event();

	FCPPT_LOG_DEBUG(
		::logger,
		fcppt::log::_
			<< FCPPT_TEXT("client sent client_info")
	)

	global_context_->insert_player(
		sanguis::world_id(
			0u // FIXME: which world id?
		),
		_id,
		sge::charconv::utf8_string_to_fcppt(
			_message.get<
				sanguis::messages::adapted_types::string
			>()
		),
		this->state_cast<
			sanguis::server::states::unpaused const *
		>()
		?
			sanguis::connect_state::unpaused
		:
			sanguis::connect_state::paused
	);

	return
		this->discard_event();
}

boost::statechart::result
sanguis::server::states::running::operator()(
	sanguis::server::player_id const _id,
	sanguis::messages::console_command const &_message
)
{
	if(
		!this->global_context().has_player(
			_id
		)
	)
		return
			this->discard_event();

	sanguis::string_vector const command(
		sanguis::messages::serialization::convert_string_vector(
			_message.get<
				sanguis::messages::adapted_types::string_vector
			>()
		)
	);

	if(
		command.empty()
	)
		return
			this->discard_event();

	FCPPT_LOG_DEBUG(
		::logger,
		fcppt::log::_
			<< FCPPT_TEXT("Received console command: ")
			<< command[0]
	);

	try
	{
		console_.eval(
			_id,
			sanguis::to_console_arg_list(
				command
			)
		);
	}
	catch(
		fcppt::exception const &_error
	)
	{
		FCPPT_LOG_ERROR(
			::logger,
			fcppt::log::_
				<< _error.string()
		);
	}

	return
		this->discard_event();
}

boost::statechart::result
sanguis::server::states::running::operator()(
	sanguis::server::player_id const _id,
	sanguis::messages::player_cheat const &_message
)
{
	global_context_->player_cheat(
		_id,
		_message.get<
			sanguis::messages::roles::cheat
		>()
	);

	return
		this->discard_event();
}

boost::statechart::result
sanguis::server::states::running::operator()(
	sanguis::server::player_id const _id,
	sanguis::messages::player_choose_perk const &_message
)
{
	global_context_->player_choose_perk(
		_id,
		_message.get<
			sanguis::messages::roles::perk
		>()
	);

	return
		this->discard_event();
}

sanguis::server::global::context &
sanguis::server::states::running::global_context()
{
	return
		*global_context_;
}

boost::statechart::result
sanguis::server::states::running::handle_default_msg(
	sanguis::server::player_id const,
	sanguis::messages::base const &
)
{
	return
		this->discard_event();
}
