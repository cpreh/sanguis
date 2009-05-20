#include "unpaused.hpp"
#include "paused.hpp"
#include "../entities/player.hpp"
#include "../entities/entity.hpp"
#include "../entities/property.hpp"
#include "../message_functor.hpp"
#include "../message_convert/speed.hpp"
#include "../message_convert/rotate.hpp"
#include "../message_convert/remove.hpp"
#include "../message_convert/move.hpp"
#include "../message_convert/health.hpp"
#include "../log.hpp"
#include "../../truncation_check_cast.hpp"
#include "../../random.hpp"
#include "../../messages/pause.hpp"
#include "../../messages/base.hpp"
#include "../../messages/unwrap.hpp"
#include "../../messages/create.hpp"
#include "../../exception.hpp"

#include <sge/math/vector/to_angle.hpp>
#include <sge/math/vector/arithmetic.hpp>
#include <sge/math/vector/basic_impl.hpp>
#include <sge/math/vector/is_null.hpp>
#include <sge/container/map_impl.hpp>
#include <sge/collision/world.hpp>
#include <sge/log/headers.hpp>
#include <sge/format.hpp>
#include <sge/text.hpp>
#include <sge/time/resolution.hpp>
#include <sge/time/second_f.hpp>

#include <boost/lexical_cast.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/bind.hpp>
#include <ostream>

sanguis::server::states::unpaused::unpaused()
:
	send_timer(
		sge::time::second_f(static_cast<sge::time::funit>(0.5)))
{
	SGE_LOG_DEBUG(
		log(),
		sge::log::_1
			<< SGE_TEXT("constructor"));
}

boost::statechart::result
sanguis::server::states::unpaused::handle_default_msg(
	net::id_type,
	messages::base const &)
{
	return forward_event();
}

boost::statechart::result
sanguis::server::states::unpaused::operator()(
	net::id_type const id,
	messages::player_attack_dest const &e)
{
	context<running>().player(
		id
	).target(
		e.get<messages::roles::attack_dest>()
	);

	return discard_event();
}

boost::statechart::result
sanguis::server::states::unpaused::operator()(
	net::id_type const id,
	messages::player_change_weapon const &e)
{
	weapon_type::type const wt(
		static_cast<
			weapon_type::type
		>(
			e.get<messages::roles::weapon>()
		)
	);

	if (wt > weapon_type::size)
		throw exception(
			SGE_TEXT("got invalid weapon type in player_change_weapon")
		);

	context<running>().player(
		id
	).change_weapon(
		wt
	);

	return discard_event();
}

boost::statechart::result
sanguis::server::states::unpaused::operator()(
	net::id_type const id,
	messages::player_rotation const &e)
{
	entities::player &player_(
		context<running>().player(
			id
		)
	);

	player_.angle(
		e.get<messages::roles::angle>()
	);

	send(
		message_convert::rotate(
			player_
		)
	);

	return discard_event();
}

boost::statechart::result
sanguis::server::states::unpaused::operator()(
	net::id_type const id,
	messages::player_start_shooting const &)
{
	context<running>().player(
		id
	).aggressive(
		true
	);

	return discard_event();
}

boost::statechart::result
sanguis::server::states::unpaused::operator()(
	net::id_type const id,
	messages::player_stop_shooting const &)
{
	context<running>().player(
		id
	).aggressive(
		false
	);

	return discard_event();
}

boost::statechart::result
sanguis::server::states::unpaused::operator()(
	net::id_type const id,
	messages::player_direction const &e)
{
	entities::player &player_(
		context<running>().player(
			id
		)
	);

	pos_type const dir(
		e.get<messages::roles::direction>()
	);

	if (is_null(dir))
		player_.property(
			entities::property_type::movement_speed
		).current(
			static_cast<space_unit>(0)
		);
	else
	{
		player_.property(
			entities::property_type::movement_speed
		).current_to_max();

		player_.direction(
			*sge::math::vector::to_angle<space_unit>(dir)
		);
	}

	send(
		message_convert::speed(
			player_
		)
	);

	return discard_event();
}

boost::statechart::result
sanguis::server::states::unpaused::operator()(
	net::id_type,
	messages::player_unpause const &) 
{
	SGE_LOG_WARNING(
		log(),
		sge::log::_1 
			<< SGE_TEXT("received superfluous unpause!"));
	return discard_event();
}

boost::statechart::result
sanguis::server::states::unpaused::operator()(
	net::id_type,
	messages::player_pause const &)
{
	send(
		messages::create(
			messages::pause()
		)
	);
	
	return transit<paused>();
}

boost::statechart::result
sanguis::server::states::unpaused::react(
	tick_event const &t)
{
	time_type const delta = t.delta();

	context<running>().process(delta);

	// should we send position updates?
	bool const update_pos = send_timer.update_b();

	entities::container &entities = context<running>().entities();

	context<machine>().collision()->update(static_cast<sge::time::funit>(delta));

	for (entities::container::iterator i = entities.begin(); i != entities.end();)
	{
		if (i->dead())
		{
			if(i->type() != entity_type::indeterminate)
			{
				send(message_convert::health(*i));
				send(message_convert::remove(*i));
			}
			
			// we have to remove the player link as well
			if(i->type() == entity_type::player)
				context<running>().players().erase(
					dynamic_cast<entities::player &>(*i).net_id()
				);

			i = entities.erase(i);
			continue;
		}

		i->update(
			static_cast<time_type>(delta),
			entities
		);

		if (i->type() != entity_type::indeterminate && update_pos)
		{
			send(message_convert::move(*i));
			send(message_convert::speed(*i));
			send(message_convert::rotate(*i));
			if(i->update_health())
				send(
					message_convert::health(
						*i
					)
				);
		}

		++i;
	}
	return discard_event();
}

boost::statechart::result
sanguis::server::states::unpaused::react(
	message_event const &m)
{
	message_functor<unpaused, boost::statechart::result> mf(
		*this,
		m.id()
	);

	return messages::unwrap<
		boost::mpl::vector<
			messages::player_attack_dest,
			messages::player_rotation,
			messages::player_start_shooting,
			messages::player_stop_shooting,
			messages::player_change_weapon,
			messages::player_unpause,
			messages::player_pause,
			messages::player_direction
		>,
		boost::statechart::result
	>(
		mf,
		*m.message(),
		boost::bind(
			&unpaused::handle_default_msg,
			this,
			m.id(),
			_1
		)
	);
}

sanguis::server::environment const
sanguis::server::states::unpaused::environment()
{
	return context<running>().environment();
}

void sanguis::server::states::unpaused::send(
	messages::auto_ptr m)
{
	environment().send()(m);
}

sge::log::logger &
sanguis::server::states::unpaused::log()
{
	static sge::log::logger log_(
		server::log(),
		SGE_TEXT("unpaused: "),
		true
	);
	return log_;
}
