#include "running_state.hpp"
#include "waiting_state.hpp"
#include "get_unique_id.hpp"
#include "../messages/player_rotation_event.hpp"
#include "../messages/player_direction_event.hpp"
#include "../messages/player_start_shooting.hpp"
#include "../messages/player_stop_shooting.hpp"
#include "../messages/player_change_weapon.hpp"
#include "../messages/add.hpp"
#include "../messages/change_weapon.hpp"
#include "../messages/remove.hpp"
#include "../messages/game_state.hpp"
#include "../messages/client_info.hpp"
#include "../messages/rotate.hpp"
#include "../messages/disconnect.hpp"
#include "../messages/move.hpp"
#include "../messages/speed.hpp"
#include "../entity_type.hpp"
#include "../game_state.hpp"
#include "../dispatch_type.hpp"
#include "../truncation_check_cast.hpp"
#include "../resolution.hpp"
#include "../truncation_check_structure_cast.hpp"
#include "../angle_vector.hpp"
#include "message_functor.hpp"
#include "player.hpp"
#include "zombie.hpp"
#include "bullet.hpp"
#include "converter.hpp"
#include "collision.hpp"

#include <sge/iostream.hpp>
#include <sge/su.hpp>
#include <sge/string.hpp>
#include <sge/math/vector.hpp>
#include <sge/math/rect.hpp>
#include <sge/math/rect_impl.hpp>
#include <sge/math/rect_util.hpp>
#include <sge/math/angle.hpp>
#include <sge/math/random.hpp>
#include <sge/math/constants.hpp>

#include <boost/bind.hpp>
#include <boost/mpl/vector.hpp>

#include <cmath>
#include <cassert>


sanguis::server::running_state::running_state()
	: send_timer(SGE_TEXT("message_freq"),sge::su(0.1)),
		enemy_timer(SGE_TEXT("enemy_timer"),sge::su(2))
{
	sge::clog << SGE_TEXT("server: entering running state\n");
}

void sanguis::server::running_state::ai_hook(entity &e,const entity::time_type diff)
{
	switch (e.ai_type())
	{
		case ai_type::none:
			e.pos(e.pos() + e.abs_speed() * diff);
		break;
		case ai_type::simple:
		{
			const messages::pos_type diffvec = (player_->center() - e.center());
			if (!diffvec.is_null())
			{
				const messages::space_unit angle = *sge::math::angle_to<messages::space_unit>(diffvec);
				e.pos(e.pos() + sge::math::normalize(diffvec) * e.max_speed() * diff);
				e.angle(angle);
				e.direction(angle);
			}
		}
		break;
	}
}


boost::statechart::result sanguis::server::running_state::react(const tick_event&t) 
{
	const sge::timer::frames_type delta = t.data.diff_time;

	if (enemy_timer.v().update_b())
		add_enemy();

	for (entity_container::iterator i = entities.begin(); i != entities.end(); ++i)
		i->colliding(false);

	const bool update_pos = send_timer.v().update_b();
	for (entity_container::iterator i = entities.begin(); i != entities.end();)
	{
		ai_hook(*i,delta);

		//bool colliding = false;
		const bool attacking_prior_i = i->attacking();
		/*for (entity_container::iterator j = entities.begin(); j != entities.end(); ++j)
		{
			if (!collides(*i,*j))
				continue;
			colliding = true;
			i->attack(*j);
			context<machine>().send(message_convert<messages::health>(*i));
		}*/

		if(i->attacking())
		{
			if (!attacking_prior_i)
				context<machine>().send(message_convert<messages::start_attacking>(*i));
/*			else if(!colliding)
			{
				context<machine>().send(message_convert<messages::stop_attacking>(*i));
				i->attacking(false);
			}*/
		}
		if (i->type() == entity_type::player && dynamic_cast<server::player &>(*i).spawn_bullet())
			add_bullet();

		if (i->health() <= messages::mu(0))
		{
			if (i->type() == entity_type::player)
			{
				sge::cout << "server: player's dead!\n";
			}
			else
			{
				//context<machine>().send(message_convert<messages::remove>(*i));
				i = entities.erase(i);
				continue;
			}
		}

		if (update_pos && i->type() != entity_type::bullet)
		{
			context<machine>().send(message_convert<messages::move>(*i));
			context<machine>().send(message_convert<messages::speed>(*i));
			context<machine>().send(message_convert<messages::rotate>(*i));
		}

		++i;
	}

	return discard_event();
}

void sanguis::server::running_state::create_game(const net::id_type net_id,const messages::client_info &m)
{
	assert(!entities.size());

	const entity_id player_id = get_unique_id(); entity &raw_player = insert_entity(new server::player(
			player_id,
			net_id,
			messages::pos_type(
				messages::mu(resolution().w()/2),
				messages::mu(resolution().h()/2)),
			messages::mu(0),
			messages::mu(0),
			messages::mu(0),
			messages::mu(100),
			messages::mu(100),
			m.name()));
	
	player_ = &dynamic_cast<player &>(raw_player);

	sge::clog << SGE_TEXT("server: sending game messages\n");

	//context<machine>().send(new messages::change_weapon(player_id,static_cast<messages::enum_type>(weapon_type::pistol)));
	context<machine>().send(new messages::game_state(game_state(truncation_check_cast<boost::uint32_t>(0))));
	context<machine>().send(message_convert<messages::add>(*player_));

	enemy_timer.v().reset();
}

boost::statechart::result sanguis::server::running_state::operator()(const net::id_type,const messages::player_change_weapon &e)
{
	context<machine>().send(new messages::change_weapon(player_->id(),e.weapon()));
	return discard_event();
}

boost::statechart::result sanguis::server::running_state::operator()(const net::id_type id,const messages::player_rotation_event &e)
{
	if (player_->net_id() != id)
	{
		sge::clog << SGE_TEXT("server: got rotation_event from spectator ") << id << SGE_TEXT("\n");
		return discard_event();
	}

	player_->angle(e.angle());
	context<machine>().send(message_convert<messages::rotate>(*player_));
	return discard_event();
}

sanguis::server::entity &sanguis::server::running_state::insert_entity(entity *ptr)
{
	entities.push_back(ptr);
	return entities.back();
}

void sanguis::server::running_state::add_enemy()
{
	const entity_id id = get_unique_id();

	const messages::space_unit rand_angle = sge::math::random(messages::mu(0),
					messages::mu(2)*sge::math::pi<messages::space_unit>());
	const messages::space_unit radius = messages::mu(std::max(resolution().w(),resolution().h()))/messages::mu(2);
	const messages::space_unit scale = messages::mu(1.5);

	const messages::pos_type screen_center = messages::pos_type(messages::mu(resolution().w()),messages::mu(resolution().h()))/messages::mu(2);
	const messages::pos_type center = scale * radius * angle_to_vector(rand_angle);
	
	boost::optional<messages::space_unit> oa = sge::math::angle_to<messages::space_unit>(player_->center() - center);
	const messages::space_unit angle = oa ? *oa : messages::mu(0);

	const messages::pos_type pos = center + screen_center;

	zombie &b = dynamic_cast<zombie &>(
		insert_entity(new zombie(id,pos,angle,messages::mu(1),angle,messages::mu(50),messages::mu(50))));

	context<machine>().send(message_convert<messages::add>(b));
}

void sanguis::server::running_state::add_bullet()
{
	const entity_id bullet_id = get_unique_id();

	bullet &b = dynamic_cast<bullet &>(
		insert_entity(new bullet(bullet_id,player_->center(),player_->angle(),player_->angle())));

	context<machine>().send(message_convert<messages::add>(b));
}

boost::statechart::result sanguis::server::running_state::operator()(const net::id_type id,const messages::player_start_shooting &)
{
	if (player_->net_id() != id)
	{
		sge::clog << SGE_TEXT("server: got shooting event from spectator ") << id << SGE_TEXT("\n");
		return discard_event();
	}

	player_->shooting(true);
	add_bullet();
	return discard_event();
}

boost::statechart::result sanguis::server::running_state::operator()(const net::id_type id,const messages::player_stop_shooting &)
{
	if (player_->net_id() != id)
		return discard_event();

	player_->shooting(false);
	return discard_event();
}

boost::statechart::result sanguis::server::running_state::operator()(const net::id_type id,const messages::player_direction_event &e)
{
	if (player_->id() != id)
	{
		sge::clog << SGE_TEXT("server: got direction_event from spectator ") << id << SGE_TEXT("\n");
		return discard_event();
	}

	if (e.dir().is_null())
	{
		player_->speed(messages::mu(0));
	}
	else
	{
		player_->speed(messages::mu(1));
		player_->direction(*sge::math::angle_to<messages::space_unit>(e.dir()));
	}

	context<machine>().send(message_convert<messages::speed>(*player_));
	return discard_event();
}

boost::statechart::result sanguis::server::running_state::operator()(const net::id_type id,const messages::client_info&m) 
{
	sge::clog << SGE_TEXT("server: received client info from ") << id << SGE_TEXT("\n");
	create_game(id,m);
	return discard_event();
}

boost::statechart::result sanguis::server::running_state::operator()(const net::id_type id,const messages::disconnect&) 
{
	if (player_->id() != id)
	{
		sge::clog << SGE_TEXT("server: spectator ") << id << SGE_TEXT(" disconnected\n");
		return discard_event();
	}
	sge::clog << SGE_TEXT("server: disconnected\n");
	return transit<waiting_state>();
}

boost::statechart::result sanguis::server::running_state::handle_default_msg(const net::id_type id,const messages::base&m) 
{
	sge::clog << SGE_TEXT("server: received unexpected message ") << typeid(m).name() << SGE_TEXT(" from id ") << id << SGE_TEXT("\n");
	return discard_event();
}

boost::statechart::result sanguis::server::running_state::react(const message_event&m) 
{
	message_functor<running_state> mf(*this,m.id);

	return dispatch_type<
		boost::mpl::vector<
			messages::disconnect,
			messages::client_info,
			messages::player_rotation_event,
			messages::player_start_shooting,
			messages::player_stop_shooting,
			messages::player_change_weapon,
			messages::player_direction_event
		>,
		boost::statechart::result>(
		mf,
		*m.message,
		boost::bind(&running_state::handle_default_msg, this, m.id, _1));
}
