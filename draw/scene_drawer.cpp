#include "scene_drawer.hpp"
#include "factory/client.hpp"
#include "factory/enemy.hpp"
#include "factory/entity.hpp"
#include "factory/pickup.hpp"
#include "factory/weapon_pickup.hpp"
#include "player.hpp"
#include "coord_transform.hpp"
#include "decay_time.hpp"
#include "reaper.hpp"
#include "../server/get_dim.hpp"
#include "../dispatch_type.hpp"
#include "../messages/add.hpp"
#include "../messages/add_enemy.hpp"
#include "../messages/add_pickup.hpp"
#include "../messages/add_weapon_pickup.hpp"
#include "../messages/base.hpp"
#include "../messages/change_weapon.hpp"
#include "../messages/experience.hpp"
#include "../messages/health.hpp"
#include "../messages/max_health.hpp"
#include "../messages/move.hpp"
#include "../messages/remove.hpp"
#include "../messages/resize.hpp"
#include "../messages/rotate.hpp"
#include "../messages/start_attacking.hpp"
#include "../messages/stop_attacking.hpp"
#include "../messages/speed.hpp"
#include "../client_messages/add.hpp"
#include "../client/next_id.hpp"

#include <sge/exception.hpp>
#include <sge/iostream.hpp>
#include <sge/iconv.hpp>
#include <sge/string.hpp>
#include <sge/sprite/system_impl.hpp>

#include <boost/mpl/vector.hpp>
#include <boost/bind.hpp>

#include <algorithm>
#include <functional>
#include <typeinfo>
#include <ostream>

sanguis::draw::scene_drawer::scene_drawer(
	const sge::renderer::device_ptr rend,
	sge::font::font &font)
: ss(rend),
  hud_(font),
  player_(0),
  paused(false)
{}

void sanguis::draw::scene_drawer::process_message(const messages::base& m)
{
	dispatch_type<
		boost::mpl::vector<
			messages::add,
			messages::add_enemy,
			messages::add_pickup,
			messages::add_weapon_pickup,
			messages::change_weapon,
			messages::experience,
			messages::health,
			messages::max_health,
			messages::move,
			messages::remove,
			messages::resize,
			messages::rotate,
			messages::start_attacking,
			messages::stop_attacking,
			messages::speed
			>,
		void>(
		*this,
		m,
		boost::bind(&scene_drawer::process_default_msg, this, _1));
}

void sanguis::draw::scene_drawer::process_message(const client_messages::base& m)
{
	dispatch_type<
		boost::mpl::vector<
			client_messages::add
			>,
		void>(
		*this,
		m,
		boost::bind(&scene_drawer::process_default_client_msg, this, _1));
}

void sanguis::draw::scene_drawer::draw(const time_type delta)
{
	for(entity_map::iterator it(entities.begin()), next(it); it != entities.end(); it = next)
	{
		entity& e = *it->second;
		++next;

		e.update(
			paused
			? 0
			: delta);

		if(e.may_be_removed())
			entities.erase(it);
	}

	ss.render();

	hud_.update(delta);
}

void sanguis::draw::scene_drawer::pause(
	bool const p)
{
	sge::clog << SGE_TEXT("client: drawer::pause: ") << p << SGE_TEXT('\n');
	paused = p;
}

sanguis::draw::player const &
sanguis::draw::scene_drawer::get_player() const
{
	if(!player_)
		throw sge::exception(SGE_TEXT("scene_drawer::get_player(): no player available!"));
	return *player_;
}

void sanguis::draw::scene_drawer::operator()(const messages::add& m)
{
	configure_new_object(
		factory::entity(
			m.id(),
			get_system(),
			m.type()),
		m);
}

void sanguis::draw::scene_drawer::operator()(const messages::add_enemy& m)
{
	configure_new_object(
		factory::enemy(
			m.id(),
			get_system(),
			m.etype()),
		m);
}

void sanguis::draw::scene_drawer::operator()(const messages::add_pickup& m)
{
	configure_new_object(
		factory::pickup(
			m.id(),
			get_system(),
			m.ptype()),
		m);
}

void sanguis::draw::scene_drawer::operator()(const messages::add_weapon_pickup& m)
{
	configure_new_object(
		factory::weapon_pickup(
			m.id(),
			get_system(),
			m.wtype()),
		m);
}

void sanguis::draw::scene_drawer::operator()(const messages::change_weapon& m)
{
	const messages::enum_type value(m.weapon());
	if(value >= static_cast<messages::enum_type>(weapon_type::size))
	{
		sge::clog << SGE_TEXT("Invalid change_weapon message: Value out of range!\n");
		return;
	}
		
	get_entity(m.id()).weapon(static_cast<weapon_type::type>(m.weapon()));
}

void sanguis::draw::scene_drawer::operator()(const messages::experience& m)
{
	hud_.experience(m.exp());
}

void sanguis::draw::scene_drawer::operator()(const messages::health& m)
{
	get_entity(m.id()).health(m.value());
}

void sanguis::draw::scene_drawer::operator()(const messages::max_health& m)
{
	get_entity(m.id()).max_health(m.value());
}

void sanguis::draw::scene_drawer::operator()(const messages::move& m)
{
	get_entity(m.id()).pos(virtual_to_screen(ss.get_renderer()->screen_size(), m.pos()));
}

void sanguis::draw::scene_drawer::operator()(const messages::remove& m)
{
	const entity_map::iterator it(entities.find(m.id()));
	if(it == entities.end())
		throw sge::exception(SGE_TEXT("Object not in entity map, can't remove it!"));
	entity &e(*it->second);
	if(typeid(e) == typeid(player)) // TODO: this is plain ugly
		player_ = 0;
	e.decay();
}

void sanguis::draw::scene_drawer::operator()(const messages::resize& m)
{
	//get_entity(m.id()).dim(virtual_to_screen(ss.get_renderer()->screen_size(), m.dim()));
	get_entity(m.id()).dim(sge::math::structure_cast<sge::sprite::unit>(m.dim()));
}

void sanguis::draw::scene_drawer::operator()(const messages::rotate& m)
{
	get_entity(m.id()).orientation(m.rot());
}

void sanguis::draw::scene_drawer::operator()(const messages::speed& m)
{
	get_entity(m.id()).speed(
		sge::math::structure_cast<sge::space_unit>(
			virtual_to_screen(ss.get_renderer()->screen_size(),
			m.get())));
}

void sanguis::draw::scene_drawer::operator()(const messages::start_attacking& m)
{
	get_entity(m.id()).start_attacking();
}

void sanguis::draw::scene_drawer::operator()(const messages::stop_attacking& m)
{
	get_entity(m.id()).stop_attacking();
}

void sanguis::draw::scene_drawer::operator()(const client_messages::add& m)
{
	if(entities.insert(
		m.id(),
		factory::client(
			m,
			get_system(),
			get_system().get_renderer()->screen_size())).second == false)
		throw sge::exception(SGE_TEXT("Client object with id already in entity list!"));
	// FIXME: configure the object here, too!
}

void sanguis::draw::scene_drawer::configure_new_object(
	factory::entity_ptr e_ptr,
	messages::add const &m)
{
	const std::pair<entity_map::iterator, bool> ret(
		entities.insert(
			m.id(),
			e_ptr));

	entity& e(*ret.first->second);

	if(ret.second == false)
		throw sge::exception(SGE_TEXT("Object with id already in entity list!"));

	// TODO: this does not belong here!
	if(m.type() == entity_type::player)
	{
		if(player_)
			throw sge::exception(SGE_TEXT("Player already exists in scene_drawer!"));
		player_ = dynamic_cast<player*>(&e);

		const entity_id reaper_id = client::next_id();

		const std::pair<entity_map::iterator, bool> reaper_ret(
			entities.insert(
				reaper_id,
				factory::entity_ptr(
					new reaper(
						reaper_id,
						get_system(),
						*player_))));

		process_message(messages::resize(reaper_id, server::get_dim("reaper","default")));
		process_message(messages::max_health(reaper_id, messages::mu(1)));
		process_message(messages::health(reaper_id, messages::mu(1)));

		if (reaper_ret.second == false)
			throw sge::exception(SGE_TEXT("couldn't insert reaper"));
	}

	// configure the object
	process_message(messages::max_health(m.id(), m.max_health()));
	process_message(messages::health(m.id(), m.health()));
	process_message(messages::move(m.id(), m.pos()));
	process_message(messages::resize(m.id(), m.dim()));
	process_message(messages::rotate(m.id(), m.angle()));
	process_message(messages::speed(m.id(), m.speed()));

	e.decay_time(
		decay_time(
			m.type()));

}

sanguis::draw::entity& sanguis::draw::scene_drawer::get_entity(const entity_id id)
{
	const entity_map::iterator it = entities.find(id);
	if(it == entities.end())
	{
		sge::cerr << "client: called get_entity with object id " << id << "\n";
		throw sge::exception(SGE_TEXT("Object not in entity map!"));
	}
	return *it->second;
}

sanguis::draw::entity const &
sanguis::draw::scene_drawer::get_entity(const entity_id id) const
{
	return const_cast<entity const&>(
		const_cast<scene_drawer&>(*this).get_entity(id));
}

void sanguis::draw::scene_drawer::process_default_msg(const messages::base& m)
{
	sge::clog << SGE_TEXT("Invalid message event in scene_drawer: ") << sge::iconv(typeid(m).name()) << SGE_TEXT('\n');
}

void sanguis::draw::scene_drawer::process_default_client_msg(
	const client_messages::base&)
{
}

sanguis::draw::system &
sanguis::draw::scene_drawer::get_system()
{
	return ss;
}
