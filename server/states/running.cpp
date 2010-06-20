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
#include "../../messages/highscore.hpp"
#include "../../messages/create.hpp"
#include "../../cast_enum.hpp"
#include <fcppt/container/map_impl.hpp>
#include <fcppt/log/parameters/inherited.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/utf8/convert.hpp>
#include <fcppt/text.hpp>
#include <fcppt/exception.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <boost/foreach.hpp>
#include <algorithm>
#include <ostream>

sanguis::server::states::running::running(
	my_context ctx
)
:
	my_base(ctx),
	console_(
		server::make_send_callback(
			context<machine>()
		),
		server::make_unicast_callback(
			context<machine>()
		)
	),
	global_context_(
		new global::context(
			server::make_unicast_callback(
				context<machine>()
			),
			context<machine>().collision_system(),
			context<machine>().resources(),
			console_
		)
	)
{
	FCPPT_LOG_DEBUG(
		log(),
		fcppt::log::_
			<< FCPPT_TEXT("constructor, listening")
	);

	context<machine>().listen();
}

sanguis::server::states::running::~running()
{}

boost::statechart::result
sanguis::server::states::running::react(
	message_event const &m
)
{
	typedef message_functor<
		running,
		boost::statechart::result
	> functor_type;
	
	functor_type mf(
		*this,
		m.id()
	);

	static messages::call::object<
		boost::mpl::vector6<
			messages::client_info,
			messages::connect,
			messages::console_command,
			messages::disconnect,
			messages::player_cheat,
			messages::player_choose_perk
		>,
		functor_type
	> dispatcher;

	return dispatcher(
		*m.message(),
		mf,
		std::tr1::bind(
			&running::handle_default_msg,
			this,
			m.id(),
			std::tr1::placeholders::_1
		)
	);
}

boost::statechart::result
sanguis::server::states::running::operator()(
	net::id_type const net_id,
	messages::client_info const &m
)
{
	global_context_->insert_player(
		0, // FIXME: which world id?
		net_id,
		fcppt::utf8::convert(
			m.get<
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
	net::id_type const id,
	messages::connect const &
)
{
	FCPPT_LOG_INFO(
		log(),
		fcppt::log::_
			<< FCPPT_TEXT("client ")
			<< id
			<< FCPPT_TEXT(" connected")
	);

	return discard_event();
}

boost::statechart::result
sanguis::server::states::running::operator()(
	net::id_type const id,
	messages::console_command const &msg
)
{
	sanguis::string_vector const command(
		messages::serialization::convert_string_vector(
			msg.get<
				messages::string_vector
			>()
		)
	);

	if(
		command.empty()
	)
		return discard_event();

	FCPPT_LOG_DEBUG(
		log(),
		fcppt::log::_
			<< FCPPT_TEXT("Received console command: ")
			<< command[0]
	);

	try
	{
		console_.eval(
			id,
			command
		);
	}
	catch(
		fcppt::exception const &e
	)
	{
		FCPPT_LOG_ERROR(
			log(),
			fcppt::log::_
				<< e.string()
		);
	}
		
	return discard_event();
}

boost::statechart::result
sanguis::server::states::running::operator()(
	net::id_type const id,
	messages::disconnect const &
)
{
	FCPPT_LOG_INFO(
		log(),
		fcppt::log::_
			<< FCPPT_TEXT("client with id ")
			<< id
			<< FCPPT_TEXT(" disconnected")
	);

	global_context_->player_disconnect(
		id
	);

	return discard_event();
}

boost::statechart::result
sanguis::server::states::running::operator()(
	net::id_type const id,
	messages::player_cheat const &p
)
{
	global_context_->player_cheat(
		id,
		SANGUIS_CAST_ENUM(
			cheat_type,
			p.get<
				messages::roles::cheat
			>()
		)
	);

	return discard_event();
}

boost::statechart::result
sanguis::server::states::running::operator()(
	net::id_type const id,
	messages::player_choose_perk const &p
)
{
	global_context_->player_choose_perk(
		id,
		SANGUIS_CAST_ENUM(
			perk_type,
			p.get<
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
	net::id_type const,
	messages::base const &
)
{
	return discard_event();
}

fcppt::log::object &
sanguis::server::states::running::log()
{
	static fcppt::log::object log_(
		fcppt::log::parameters::inherited(
			server::log(),
			FCPPT_TEXT("running")
		)
	);
	return log_;
}
