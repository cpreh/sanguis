#include <sanguis/exception.hpp>
#include <sanguis/player_name.hpp>
#include <sanguis/string_vector.hpp>
#include <sanguis/world_id.hpp>
#include <sanguis/messages/call/result.hpp>
#include <sanguis/messages/client/base_fwd.hpp>
#include <sanguis/messages/client/cheat.hpp>
#include <sanguis/messages/client/choose_perk.hpp>
#include <sanguis/messages/client/console_command.hpp>
#include <sanguis/messages/client/info.hpp>
#include <sanguis/messages/convert/from_string_vector.hpp>
#include <sanguis/messages/roles/console_command.hpp>
#include <sanguis/messages/roles/player_name.hpp>
#include <sanguis/server/dispatch.hpp>
#include <sanguis/server/dispatch_default_function.hpp>
#include <sanguis/server/machine.hpp>
#include <sanguis/server/make_send_callback.hpp>
#include <sanguis/server/make_unicast_callback.hpp>
#include <sanguis/server/player_id.hpp>
#include <sanguis/server/player_id_from_net.hpp>
#include <sanguis/server/to_console_arg_list.hpp>
#include <sanguis/server/events/disconnect.hpp>
#include <sanguis/server/events/message.hpp>
#include <sanguis/server/events/tick.hpp>
#include <sanguis/server/global/context.hpp>
#include <sanguis/server/states/log_location.hpp>
#include <sanguis/server/states/paused.hpp>
#include <sanguis/server/states/running.hpp>
#include <sanguis/server/states/unpaused.hpp>
#include <sge/charconv/utf8_string_to_fcppt.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/reference.hpp>
#include <fcppt/string.hpp>
#include <fcppt/strong_typedef_output.hpp>
#include <fcppt/text.hpp>
#include <fcppt/container/maybe_front.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/log/error.hpp>
#include <fcppt/log/info.hpp>
#include <fcppt/log/name.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/log/out.hpp>
#include <fcppt/log/parameters_no_function.hpp>
#include <fcppt/log/warning.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/optional/to_exception.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/record/get.hpp>
#include <fcppt/config/external_begin.hpp>
#include <metal.hpp>
#include <boost/statechart/result.hpp>
#include <fcppt/config/external_end.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

sanguis::server::states::running::running(
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
		fcppt::log::parameters_no_function(
			fcppt::log::name{
				FCPPT_TEXT("running")
			}
		)
	},
	console_(
		sanguis::server::make_send_callback(
			fcppt::make_ref(
				this->context<
					sanguis::server::machine
				>()
			)
		),
		sanguis::server::make_unicast_callback(
			fcppt::make_ref(
				this->context<
					sanguis::server::machine
				>()
			)
		)
	),
	global_context_(
		fcppt::make_unique_ptr<
			sanguis::server::global::context
		>(
			this->context<
				sanguis::server::machine
			>().log_context(),
			sanguis::server::make_unicast_callback(
				fcppt::make_ref(
					this->context<
						sanguis::server::machine
					>()
				)
			),
			fcppt::make_cref(
				this->context<
					sanguis::server::machine
				>().resources()
			),
			fcppt::make_ref(
				console_
			)
		)
	)
{
	FCPPT_LOG_DEBUG(
		log_,
		fcppt::log::out
			<< FCPPT_TEXT("constructor, listening")
	)

	this->context<
		sanguis::server::machine
	>().listen();
}

FCPPT_PP_POP_WARNING

sanguis::server::states::running::~running()
= default;

boost::statechart::result
sanguis::server::states::running::react(
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
				this->discard_event();
		}
	);

	return
		sanguis::server::dispatch<
			metal::list<
				sanguis::messages::client::info,
				sanguis::messages::client::cheat,
				sanguis::messages::client::choose_perk,
				sanguis::messages::client::console_command
			>
		>(
			*this,
			_message,
			sanguis::server::dispatch_default_function{
				handle_default_msg
			}
		);
}

boost::statechart::result
sanguis::server::states::running::react(
	sanguis::server::events::disconnect const &_message
)
{
	FCPPT_LOG_INFO(
		log_,
		fcppt::log::out
			<< FCPPT_TEXT("Client with id ")
			<< _message.id()
			<< FCPPT_TEXT(" disconnected.")
	)

	global_context_->player_disconnect(
		sanguis::server::player_id_from_net(
			_message.id()
		)
	);

	return
		this->discard_event();
}

sanguis::messages::call::result
sanguis::server::states::running::operator()(
	sanguis::server::player_id const _id,
	sanguis::messages::client::info const &_message
)
{
	if(
		this->global_context().has_player(
			_id
		)
	)
	{
		FCPPT_LOG_WARNING(
			log_,
			fcppt::log::out
				<< FCPPT_TEXT("Got multiple client infos")
		)

		return
			sanguis::messages::call::result(
				this->discard_event()
			);
	}

	FCPPT_LOG_DEBUG(
		log_,
		fcppt::log::out
			<< FCPPT_TEXT("client sent info")
	)

	global_context_->insert_player(
		sanguis::world_id(
			0U // FIXME: which world id?
		),
		_id,
		sanguis::player_name(
			// FIXME
			fcppt::optional::to_exception(
				sge::charconv::utf8_string_to_fcppt(
					fcppt::record::get<
						sanguis::messages::roles::player_name
					>(
						_message.get()
					)
				),
				[]{
					return
						sanguis::exception{
							FCPPT_TEXT("Failed to convert player name!")
						};
				}
			)
		)
	);

	return
		sanguis::messages::call::result(
			this->discard_event()
		);
}

sanguis::messages::call::result
sanguis::server::states::running::operator()(
	sanguis::server::player_id const _id,
	sanguis::messages::client::console_command const &_message
)
{
	sanguis::string_vector const command(
		sanguis::messages::convert::from_string_vector(
			fcppt::record::get<
				sanguis::messages::roles::console_command
			>(
				_message.get()
			)
		)
	);

	return
		fcppt::optional::maybe(
			fcppt::container::maybe_front(
				command
			),
			[
				this
			]{
				return
					sanguis::messages::call::result(
						this->discard_event()
					);
			},
			[
				this,
				_id,
				&command
			](
				fcppt::reference<
					fcppt::string const
				> const _command_name
			)
			{
				FCPPT_LOG_DEBUG(
					log_,
					fcppt::log::out
						<<
						FCPPT_TEXT("Received console command: ")
						<<
						_command_name.get()
				)

				try
				{
					console_.eval(
						_id,
						sanguis::server::to_console_arg_list(
							command
						)
					);
				}
				catch(
					fcppt::exception const &_error
				)
				{
					FCPPT_LOG_ERROR(
						log_,
						fcppt::log::out
							<< _error.string()
					)
				}

				return
					sanguis::messages::call::result(
						this->discard_event()
					);
			}
		);
}

sanguis::messages::call::result
sanguis::server::states::running::operator()(
	sanguis::server::player_id const _id,
	sanguis::messages::client::cheat const &_message
)
{
	global_context_->player_cheat(
		_id,
		_message.get()
	);

	return
		sanguis::messages::call::result(
			this->discard_event()
		);
}

sanguis::messages::call::result
sanguis::server::states::running::operator()(
	sanguis::server::player_id const _id,
	sanguis::messages::client::choose_perk const &_message
)
{
	global_context_->player_choose_perk(
		_id,
		_message.get()
	);

	return
		sanguis::messages::call::result(
			this->discard_event()
		);
}

sanguis::server::global::context &
sanguis::server::states::running::global_context()
{
	return
		*global_context_;
}
