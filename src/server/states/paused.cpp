#include "paused.hpp"
#include "unpaused.hpp"
#include "log_location.hpp"
#include "../events/disconnect.hpp"
#include "../events/message.hpp"
#include "../events/tick.hpp"
#include "../message_functor.hpp"
#include "../player_id_from_net.hpp"
#include "../../messages/call/object.hpp"
#include "../../messages/unpause.hpp"
#include "../../messages/create.hpp"
#include "../../messages/base.hpp"
#include "../../log_parameters.hpp"
#include <fcppt/log/parameters/all.hpp>
#include <fcppt/log/location.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/log/output.hpp>
#include <fcppt/log/warning.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/text.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <ostream>

namespace
{

fcppt::log::object logger(
	sanguis::log_parameters(
		sanguis::server::states::log_location()
		/
		FCPPT_TEXT("paused")
	)
);

}

sanguis::server::states::paused::paused()
{
}

sanguis::server::states::paused::~paused()
{
}

boost::statechart::result
sanguis::server::states::paused::react(
	events::message const &_message
)
{
	typedef message_functor<
		paused,
		boost::statechart::result
	> functor_type;

	functor_type functor(
		*this,
		_message.id()
	);

	static messages::call::object<
		boost::mpl::vector2<
			messages::player_pause,
			messages::player_unpause
		>,
		functor_type
	> dispatcher;

	return
		dispatcher(
			*_message.get(),
			functor,
			std::tr1::bind(
				&paused::handle_default_msg,
				this,
				server::player_id_from_net(
					_message.id()
				),
				std::tr1::placeholders::_1
			)
		);
}

boost::statechart::result
sanguis::server::states::paused::operator()(
	server::player_id,
	messages::player_unpause const &
)
{
	context<machine>().send_to_all(
		messages::create(
			messages::unpause()
		)
	);

	return transit<unpaused>();
}

boost::statechart::result
sanguis::server::states::paused::operator()(
	server::player_id,
	messages::player_pause const &
)
{
	FCPPT_LOG_WARNING(
		::logger,
		fcppt::log::_
			<< FCPPT_TEXT("got superfluous pause")
	);

	return discard_event();
}

boost::statechart::result
sanguis::server::states::paused::handle_default_msg(
	server::player_id,
	messages::base const &
)
{
	return forward_event();
}
