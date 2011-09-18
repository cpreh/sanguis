#include <sanguis/server/states/running.hpp>
#include <sanguis/server/states/unpaused.hpp>
#include <sanguis/server/states/log_location.hpp>
#include <sanguis/server/events/disconnect.hpp>
#include <sanguis/server/events/message.hpp>
#include <sanguis/server/events/tick.hpp>
#include <sanguis/server/global/context.hpp>
#include <sanguis/server/message_functor.hpp>
#include <sanguis/server/make_unicast_callback.hpp>
#include <sanguis/server/make_send_callback.hpp>
#include <sanguis/server/player_id_from_net.hpp>
#include <sanguis/connect_state.hpp>
#include <sanguis/messages/call/object.hpp>
#include <sanguis/messages/serialization/convert_string_vector.hpp>
#include <sanguis/messages/create.hpp>
#include <sanguis/cast_enum.hpp>
#include <sanguis/log_parameters.hpp>
#include <sanguis/to_console_arg_list.hpp>
#include <fcppt/container/map_impl.hpp>
#include <fcppt/log/parameters/all.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/log/error.hpp>
#include <fcppt/log/info.hpp>
#include <fcppt/log/location.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/log/output.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/utf8/to_fcppt_string.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
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
		server::make_send_callback(
			context<machine>()
		),
		server::make_unicast_callback(
			context<machine>()
		)
	),
	global_context_(
		fcppt::make_unique_ptr<
			global::context
		>(
			server::make_unicast_callback(
				context<machine>()
			),
			fcppt::cref(
				context<machine>().resources()
			),
			fcppt::ref(
				console_
			)
		)
	)
{
	FCPPT_LOG_DEBUG(
		::logger,
		fcppt::log::_
			<< FCPPT_TEXT("constructor, listening")
	);

	context<machine>().listen();
}

sanguis::server::states::running::~running()
{
}

boost::statechart::result
sanguis::server::states::running::react(
	events::message const &_message
)
{
	typedef message_functor<
		running,
		boost::statechart::result
	> functor_type;

	functor_type functor(
		*this,
		_message.id()
	);

	static messages::call::object<
		boost::mpl::vector4<
			messages::client_info,
			messages::console_command,
			messages::player_cheat,
			messages::player_choose_perk
		>,
		functor_type
	> dispatcher;

	return
		dispatcher(
			*_message.get(),
			functor,
			std::tr1::bind(
				&running::handle_default_msg,
				this,
				server::player_id_from_net(
					_message.id()
				),
				std::tr1::placeholders::_1
			)
		);
}

boost::statechart::result
sanguis::server::states::running::react(
	events::disconnect const &_message
)
{
	FCPPT_LOG_INFO(
		::logger,
		fcppt::log::_
			<< FCPPT_TEXT("client with id ")
			<< _message.id()
			<< FCPPT_TEXT(" disconnected")
	);

	global_context_->player_disconnect(
		server::player_id_from_net(
			_message.id()
		)
	);

	return discard_event();
}

boost::statechart::result
sanguis::server::states::running::operator()(
	server::player_id const _id,
	messages::client_info const &_message
)
{
	FCPPT_LOG_DEBUG(
		::logger,
		fcppt::log::_
			<< FCPPT_TEXT("client sent client_info")
	)

	global_context_->insert_player(
		sanguis::world_id(
			0 // FIXME: which world id?
		),
		_id,
		fcppt::utf8::to_fcppt_string(
			_message.get<
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
	server::player_id const _id,
	messages::console_command const &_message
)
{
	sanguis::string_vector const command(
		messages::serialization::convert_string_vector(
			_message.get<
				messages::string_vector
			>()
		)
	);

	if(
		command.empty()
	)
		return discard_event();

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

	return discard_event();
}

boost::statechart::result
sanguis::server::states::running::operator()(
	server::player_id const _id,
	messages::player_cheat const &_message
)
{
	global_context_->player_cheat(
		_id,
		SANGUIS_CAST_ENUM(
			cheat_type,
			_message.get<
				messages::roles::cheat
			>()
		)
	);

	return discard_event();
}

boost::statechart::result
sanguis::server::states::running::operator()(
	server::player_id const _id,
	messages::player_choose_perk const &_message
)
{
	global_context_->player_choose_perk(
		_id,
		SANGUIS_CAST_ENUM(
			perk_type,
			_message.get<
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
	server::player_id const,
	messages::base const &
)
{
	return discard_event();
}
