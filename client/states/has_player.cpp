#include "has_player.hpp"
//#include "gameover.hpp"
#include "../control/input_translator.hpp"
#include "../control/action_handler.hpp"
#include "../events/action.hpp"
#include "../events/menu.hpp"
#include "../events/message.hpp"
#include "../events/tick.hpp"
#include "../perk_cast.hpp"
#include "../perk_chooser.hpp"
#include "../../messages/call/object.hpp"
#include "../../messages/create.hpp"
#include "../../messages/player_choose_perk.hpp"
#include "../../cast_enum.hpp"
#include <sge/console/gfx.hpp>
#include <fcppt/container/raw_vector_impl.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <boost/mpl/vector/vector10.hpp>

sanguis::client::states::has_player::has_player(
	my_context _ctx
)
:
	my_base(_ctx),
	input_translator_(
		fcppt::make_unique_ptr<
			control::input_translator
		>(
			context<machine>().input_system(),
			std::tr1::bind(
				&states::has_player::handle_player_action,
				this,
				std::tr1::placeholders::_1
			)
		)
	),
	action_handler_(
		fcppt::make_unique_ptr<
			control::action_handler
		>(
			std::tr1::bind(
				&machine::send,
				&context<machine>(),
				std::tr1::placeholders::_1
			),
			std::tr1::ref(
				context<running>().control_environment()
			),
			std::tr1::ref(
				context<machine>().console().gfx().object()
			)
		)
	),
	perk_chooser_(
		fcppt::make_unique_ptr<
			client::perk_chooser
		>(
			context<machine>().renderer(),
			context<machine>().input_system(),
			std::tr1::ref(
				context<machine>().image_loader()
			),
			context<machine>().font_metrics(),
			std::tr1::bind(
				&has_player::send_perk_choose,
				this,
				std::tr1::placeholders::_1
			),
			context<machine>().cursor()
		)
	)
{}

sanguis::client::states::has_player::~has_player()
{
}

boost::statechart::result
sanguis::client::states::has_player::react(
	events::message const &_event
)
{
	static sanguis::messages::call::object<
		boost::mpl::vector4<
			sanguis::messages::remove_id,
			sanguis::messages::give_weapon,
			sanguis::messages::available_perks,
			sanguis::messages::level_up
		>,
		has_player
	> dispatcher;

	return
		dispatcher(
			*_event.value(),
			*this,
			std::tr1::bind(
				&has_player::handle_default_msg,
				this,
				std::tr1::placeholders::_1
			)
		);
}

boost::statechart::result
sanguis::client::states::has_player::react(
	events::action const &_event
)
{
	action_handler_->handle_player_action(
		_event.value()
	);

	return discard_event();
}

boost::statechart::result
sanguis::client::states::has_player::operator()(
	sanguis::messages::give_weapon const &_message
)
{
	action_handler_->give_player_weapon(
		SANGUIS_CAST_ENUM(
			weapon_type,
			_message.get<sanguis::messages::roles::weapon>()
		)
	);

	return discard_event();
}

boost::statechart::result
sanguis::client::states::has_player::operator()(
	messages::remove_id const &
)
{
	return discard_event(); //transit<gameover>();
}

boost::statechart::result
sanguis::client::states::has_player::operator()(
	sanguis::messages::available_perks const &_message
)
{
	perk_chooser_->perks(
		client::perk_cast(
			_message.get<sanguis::messages::perk_list>()
		)
	);

	return discard_event();
}

boost::statechart::result
sanguis::client::states::has_player::operator()(
	sanguis::messages::level_up const &_message
)
{
	perk_chooser_->level_up(
		static_cast<
			level_type
		>(
			_message.get<sanguis::messages::level_type>()
		)
	);

	return forward_event();
}

sanguis::client::perk_chooser &
sanguis::client::states::has_player::perk_chooser()
{
	return *perk_chooser_;
}

void
sanguis::client::states::has_player::handle_player_action(
	control::player_action const &_action
)
{
	post_event(
		events::action(
			_action
		)
	);
}

void
sanguis::client::states::has_player::send_perk_choose(
	perk_type::type const _perk_type
)
{
	context<machine>().send(
		sanguis::messages::create(
			sanguis::messages::player_choose_perk(
				_perk_type
			)
		)
	);
}

boost::statechart::result
sanguis::client::states::has_player::handle_default_msg(
	sanguis::messages::base const &
)
{
	return forward_event();
}
