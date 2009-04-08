#include "paused.hpp"
#include "unpaused.hpp"
#include "../from_perk_type.hpp"
#include "../perk_cast.hpp"
#include "../../media_path.hpp"
#include "../../messages/unpause.hpp"
#include "../../resolution.hpp"
#include "../../messages/player_choose_perk.hpp"
#include "../../messages/available_perks.hpp"
#include "../../messages/create.hpp"
#include "../../messages/unwrap.hpp"
#include <sge/gui/skins/standard.hpp>
#include <sge/gui/unit.hpp>
#include <sge/gui/make_image.hpp>
#include <sge/gui/layouts/vertical.hpp>
#include <sge/image/loader.hpp>
#include <sge/systems/instance.hpp>
#include <sge/make_shared_ptr.hpp>
#include <sge/container/raw_vector_impl.hpp>
#include <sge/cerr.hpp>
#include <boost/bind.hpp>
#include <boost/foreach.hpp>
#include <boost/ref.hpp>

sanguis::client::states::paused::paused(my_context ctx)
	: my_base(ctx),
		chooser_activation_(
			context<running>().perk_chooser())
{
	context<running>().pause(true);
}

boost::statechart::result
sanguis::client::states::paused::react(
	tick_event const &t)
{
	context<running>().process(t.delta());
	context<running>().draw(t.delta());
	return discard_event();
}

boost::statechart::result
sanguis::client::states::paused::react(
	message_event const &m)
{
	return messages::unwrap<
		boost::mpl::vector<
			messages::unpause
		>,
		boost::statechart::result
	>(
		*this,
		*m.message(),
		boost::bind(
			&paused::handle_default_msg,
			this,
			_1
		)
	);
}

boost::statechart::result sanguis::client::states::paused::operator()(
	messages::unpause const &)
{
	return transit<unpaused>();
}

boost::statechart::result sanguis::client::states::paused::handle_default_msg(
	messages::base const &)
{
	return forward_event();
}
