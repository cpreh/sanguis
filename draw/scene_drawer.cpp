#include "scene_drawer.hpp"
#include "client_factory.hpp"
#include "factory.hpp"
#include "player.hpp"
#include "coord_transform.hpp"
#include "decay_time.hpp"
#include "../dispatch_type.hpp"
#include "../messages/add.hpp"
#include "../messages/add_weapon.hpp"
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

sanguis::draw::scene_drawer::scene_drawer(
	const sge::renderer_ptr rend,
	sge::font &font)
: ss(rend),
  hud_(font),
  player_(0)
{}

void sanguis::draw::scene_drawer::process_message(const messages::base& m)
{
	dispatch_type<
		boost::mpl::vector<
			messages::add,
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
			messages::speed,
			messages::add_weapon
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
	sprites.clear();

	for(entity_map::iterator it(entities.begin()); it != entities.end(); ++it)
	{
		entity& e = *it->second;
		
		e.update(delta);

		if(e.may_be_removed())
		{
			entities.erase(it);
			continue;
		}

		const entity::sprite_vector& s(e.to_sprites());
		std::copy(s.begin(), s.end(), std::back_inserter(sprites));
	}

	ss.render(sprites.begin(), sprites.end());

	hud_.update(delta);
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
	const std::pair<entity_map::iterator, bool> ret(
		entities.insert(
			m.id(),
			factory::create_entity(
				m.id(),
				m.type())));
//				ss.get_renderer()->screen_size())));

	entity& e(*ret.first->second);

	if(ret.second == false)
		throw sge::exception(SGE_TEXT("Object with id already in entity list!"));
	if(m.type() == entity_type::player)
	{
		if(player_)
			throw sge::exception(SGE_TEXT("Player already exists in scene_drawer!"));
		player_ = dynamic_cast<player*>(&e);
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

void sanguis::draw::scene_drawer::operator()(const messages::add_weapon& m)
{
	sge::cout << SGE_TEXT("client: got new weapon!\n");
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
		client_factory::create_entity(
			m,
			ss.get_renderer()->screen_size())).second == false)
		throw sge::exception(SGE_TEXT("Client object with id already in entity list!"));
}

sanguis::draw::entity& sanguis::draw::scene_drawer::get_entity(const entity_id id)
{
	const entity_map::iterator it = entities.find(id);
	if(it == entities.end())
		throw sge::exception(SGE_TEXT("Object not in entity map!"));
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
