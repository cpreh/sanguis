#include "running.hpp"
#include "unpaused.hpp"
#include "../global/context.hpp"
#include "../message_functor.hpp"
#include "../message_event.hpp"
#include "../log.hpp"
#include "../make_unicast_callback.hpp"
#include "../make_send_callback.hpp"
#include "../../connect_state.hpp"
#include "../../messages/call/object.hpp"
#include "../../messages/serialization/convert_string_vector.hpp"
#include "../../messages/create.hpp"
#include "../../cast_enum.hpp"
#include "../../tick_event.hpp"
#include "../../to_console_arg_list.hpp"
#include <fcppt/container/map_impl.hpp>
#include <fcppt/log/parameters/inherited.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/utf8/convert.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/text.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <boost/foreach.hpp>
#include <algorithm>
#include <ostream>

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
			context<machine>().collision_system(),
			context<machine>().resources(),
			fcppt::ref(
				console_
			)
		)
	)
{
	FCPPT_LOG_DEBUG(
		running::log(),
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
	message_event const &_message
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
		boost::mpl::vector5<
			messages::client_info,
			messages::console_command,
			messages::disconnect,
			messages::player_cheat,
			messages::player_choose_perk
		>,
		functor_type
	> dispatcher;

	return
		dispatcher(
			*_message.message(),
			functor,
			std::tr1::bind(
				&running::handle_default_msg,
				this,
				_message.id(),
				std::tr1::placeholders::_1
			)
		);
}

boost::statechart::result
sanguis::server::states::running::operator()(
	net::id const _id,
	messages::client_info const &_message
)
{
	FCPPT_LOG_DEBUG(
		running::log(),
		fcppt::log::_
			<< FCPPT_TEXT("client sent client_info")
	)

	global_context_->insert_player(
		0, // FIXME: which world id?
		_id,
		fcppt::utf8::convert(
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
	net::id const _id,
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
		running::log(),
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
			running::log(),
			fcppt::log::_
				<< _error.string()
		);
	}
		
	return discard_event();
}

boost::statechart::result
sanguis::server::states::running::operator()(
	net::id const _id,
	messages::disconnect const &
)
{
	FCPPT_LOG_INFO(
		running::log(),
		fcppt::log::_
			<< FCPPT_TEXT("client with id ")
			<< _id
			<< FCPPT_TEXT(" disconnected")
	);

	global_context_->player_disconnect(
		_id
	);

	return discard_event();
}

boost::statechart::result
sanguis::server::states::running::operator()(
	net::id const _id,
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
	net::id const _id,
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
	net::id const,
	messages::base const &
)
{
	return discard_event();
}

fcppt::log::object &
sanguis::server::states::running::log()
{
	static fcppt::log::object my_logger(
		fcppt::log::parameters::inherited(
			server::log(),
			FCPPT_TEXT("running")
		)
	);

	return my_logger;
}
