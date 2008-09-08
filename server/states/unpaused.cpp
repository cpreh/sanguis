#include "unpaused.hpp"
#include "paused.hpp"
#include "waiting.hpp"
#include "../entities/player.hpp"
#include "../message_functor.hpp"
#include "../message_converter.hpp"
#include "../entities/entity.hpp"
#include "../../truncation_check_cast.hpp"
#include "../../dispatch_type.hpp"
#include "../../log_headers.hpp"
#include "../../angle_vector.hpp"
#include "../../random.hpp"
#include "../../messages/assign_id.hpp"
#include "../../messages/disconnect.hpp"
#include "../../messages/experience.hpp"
#include "../../messages/level_up.hpp"
#include "../../messages/player_rotation.hpp"
#include "../../messages/player_start_shooting.hpp"
#include "../../messages/player_stop_shooting.hpp"
#include "../../messages/player_change_weapon.hpp"
#include "../../messages/player_direction.hpp"
#include "../../messages/player_pause.hpp"
#include "../../messages/player_unpause.hpp"
#include "../../messages/give_weapon.hpp"
#include "../../messages/speed.hpp"
#include "../../messages/change_weapon.hpp"
#include "../../messages/pause.hpp"

#include <sge/math/constants.hpp>
#include <sge/math/angle.hpp>
#include <sge/iconv.hpp>

#include <boost/lexical_cast.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/bind.hpp>
#include <ostream>

sanguis::server::states::unpaused::unpaused()
:
	send_timer(
		SGE_TEXT("send_timer"),
		sge::su(0.1))
{}

boost::statechart::result
sanguis::server::states::unpaused::handle_default_msg(
	net::id_type id,
	messages::base const &m)
{
	SGE_LOG_WARNING(
		log(),
		sge::log::_1
			<< SGE_TEXT("server: received unexpected message from id ")
			<< id
			<< SGE_TEXT(" of type ")
			<< sge::iconv(typeid(m).name()));
	return discard_event();
}

boost::statechart::result
sanguis::server::states::unpaused::operator()(
	net::id_type const id,
	messages::player_change_weapon const &e)
{
	running::player_map::iterator const it(context<running>().players().find(id));
	if (it == context<running>().players().end())
	{
		SGE_LOG_WARNING(
			log(),
			sge::log::_1
				<< SGE_TEXT("server: got player_change_weapon from spectator ")
				<< id);
		return discard_event();
	}

	entities::player &player_(*it->second);

	if (e.weapon() > weapon_type::size)
		throw sge::exception("got invalid weapon type in player_change_weapon");

	const weapon_type::type type(static_cast<weapon_type::type>(e.weapon()));

	player_.change_weapon(type);

	send(
		messages::auto_ptr(
			new messages::change_weapon(
				player_.id(),
				e.weapon())));
	return discard_event();
}

boost::statechart::result
sanguis::server::states::unpaused::operator()(
	net::id_type const id,
	messages::player_rotation const &e)
{
	running::player_map::iterator const it(context<running>().players().find(id));
	if (it == context<running>().players().end())
	{
		SGE_LOG_WARNING(
			log(),
			sge::log::_1
				<< SGE_TEXT("server: got rotation_event from spectator ")
				<< id);
		return discard_event();
	}

	entities::player &player_(*it->second);

	// FIXME: we should really transport the target point over the network
	player_.target(
		player_.pos()
		+ angle_to_vector(player_.direction()) * 100);

	player_.angle(e.angle());
	send(message_convert<messages::rotate>(player_));
	return discard_event();
}

boost::statechart::result
sanguis::server::states::unpaused::operator()(
	net::id_type const id,
	messages::player_start_shooting const &)
{
	if (context<running>().players().find(id) == context<running>().players().end())
	{
		SGE_LOG_WARNING(
			log(),
			sge::log::_1
				<< SGE_TEXT("server: got shooting event from spectator ")
				<< id);
		return discard_event();
	}

	context<running>().players()[id]->aggressive(true);
	return discard_event();
}

boost::statechart::result
sanguis::server::states::unpaused::operator()(
	net::id_type const id,
	messages::player_stop_shooting const &)
{
	if (context<running>().players().find(id) == context<running>().players().end())
	{
		SGE_LOG_WARNING(
			log(),
			sge::log::_1
				<< SGE_TEXT("server: got player_stop_shooting from spectator ")
				<< id);
		return discard_event();
	}

	context<running>().players()[id]->aggressive(false);
	return discard_event();
}

boost::statechart::result
sanguis::server::states::unpaused::operator()(
	net::id_type const id,
	messages::player_direction const &e)
{
	running::player_map::iterator const it(context<running>().players().find(id));
	if (it == context<running>().players().end())
	{
		SGE_LOG_WARNING(
			log(),
			sge::log::_1
				<< SGE_TEXT("server: got direction_event from spectator ")
				<< id);
		return discard_event();
	}

	entities::player &player_(*it->second);

	if (e.dir().is_null())
		player_.get_property(entities::property::type::movement_speed).current(messages::mu(0));
	else
	{
		player_.get_property(entities::property::type::movement_speed).set_current_to_max();
		player_.direction(*sge::math::angle_to<messages::space_unit>(e.dir()));
	}

	send(message_convert<messages::speed>(player_));
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
			<< SGE_TEXT("server: received superfluous unpause!"));
	return discard_event();
}

boost::statechart::result
sanguis::server::states::unpaused::operator()(
	net::id_type,
	messages::player_pause const &)
{
	send(
		messages::auto_ptr(
			new messages::pause()));
	
	return transit<paused>();
}

boost::statechart::result
sanguis::server::states::unpaused::operator()(
	net::id_type const id,
	messages::disconnect const &) 
{
	// FIXME: this should be handled once and not in every state
	if (context<running>().players().find(id) == context<running>().players().end())
	{
		SGE_LOG_WARNING(
			log(),
			sge::log::_1
				<< SGE_TEXT("server: spectator ")
				<< id
				<< SGE_TEXT(" disconnected"));
		return discard_event();
	}

	SGE_LOG_WARNING(
		log(),
		sge::log::_1
			<< SGE_TEXT("server: disconnected"));
	
	return transit<waiting>();
}

void sanguis::server::states::unpaused::get_player_exp(const sge::con::arg_list &)
{
	// FIXME
	/*context<running>().console_print(
		SGE_TEXT("player experience is: ")+
			boost::lexical_cast<sge::string>(
				context<running>().players().begin()->second->exp()));*/
}

boost::statechart::result sanguis::server::states::unpaused::react(const tick_event &t)
{
	time_type const delta = t.delta();

	context<running>().process(delta);

	// should we send position updates?
	bool const update_pos = send_timer.v().update_b();

	entities::container &entities = context<running>().entities();

	for (entities::container::iterator i = entities.begin(); i != entities.end();)
	{
		if (i->dead())
		{
			if(i->type() != entity_type::indeterminate)
			{
				send(message_convert<messages::health>(*i));
				send(message_convert<messages::remove>(*i));
			}
			i = entities.erase(i);
			continue;
		}

		i->update(
			static_cast<time_type>(delta),
			entities);

		if (i->type() != entity_type::indeterminate && update_pos)
		{
			send(message_convert<messages::move>(*i));
			send(message_convert<messages::speed>(*i));
			send(message_convert<messages::rotate>(*i));
			send(message_convert<messages::health>(*i)); // FIXME: this should be elsewhere
		}

		++i;
	}
	return discard_event();
}

boost::statechart::result
sanguis::server::states::unpaused::react(
	message_event const &m)
{
	message_functor<unpaused,boost::statechart::result> mf(
		*this,
		m.id);

	return dispatch_type<
		boost::mpl::vector<
			messages::disconnect,
			messages::player_rotation,
			messages::player_start_shooting,
			messages::player_stop_shooting,
			messages::player_change_weapon,
			messages::player_unpause,
			messages::player_pause,
			messages::player_direction
		>,
		boost::statechart::result>(
			mf,
			*m.message,
			boost::bind(&unpaused::handle_default_msg, this, m.id, _1));
}

sanguis::server::environment const
sanguis::server::states::unpaused::get_environment()
{
	return context<running>().get_environment();
}

void sanguis::server::states::unpaused::send(
	messages::auto_ptr m)
{
	get_environment().send(m);
}
