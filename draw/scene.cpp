#include "scene.hpp"
#include "entity.hpp"
#include "background.hpp"
#include "factory/client.hpp"
#include "factory/enemy.hpp"
#include "factory/entity.hpp"
#include "factory/pickup.hpp"
#include "factory/projectile.hpp"
#include "factory/decoration.hpp"
#include "factory/weapon_pickup.hpp"
#include "coord_transform.hpp"
#include "log.hpp"
#include "environment.hpp"
#include "../messages/add.hpp"
#include "../messages/add_decoration.hpp"
#include "../messages/add_enemy.hpp"
#include "../messages/add_pickup.hpp"
#include "../messages/add_projectile.hpp"
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
#include "../messages/start_reloading.hpp"
#include "../messages/stop_reloading.hpp"
#include "../messages/speed.hpp"
#include "../client_messages/add.hpp"
#include "../client/invalid_id.hpp"
#include "../dispatch_type.hpp"
#include "../exception.hpp"

#include <sge/make_auto_ptr.hpp>
#include <sge/iconv.hpp>
#include <sge/text.hpp>
#include <sge/format.hpp>
#include <sge/log/headers.hpp>
#include <sge/renderer/device.hpp>

#include <boost/mpl/vector.hpp>
#include <boost/bind.hpp>
#include <boost/foreach.hpp>

#include <utility>
#include <typeinfo>
#include <ostream>

sanguis::draw::scene::scene(
	load::context const &resources_,
	sge::renderer::device_ptr const rend,
	sge::font::font &font)
:
	ss(rend),
	hud_(font),
	paused(false),
	env(
		boost::bind(
			&scene::insert,
			this,
			_1),
		resources_,
		system()),
	background_id(
		client::invalid_id)
{
	/*
	entity_auto_ptr p(
		sge::make_auto_ptr<
			draw::background
		>(
			environment()));
	background_id = p->id();
	insert(p);*/
}

sanguis::draw::scene::~scene()
{}

void sanguis::draw::scene::process_message(
	messages::base const &m)
{
	dispatch_type<
		boost::mpl::vector<
			messages::add,
			messages::add_decoration,
			messages::add_enemy,
			messages::add_pickup,
			messages::add_projectile,
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
			messages::start_reloading,
			messages::stop_reloading,
			messages::speed
		>,
		void
	>(
		*this,
		m,
		boost::bind(
			&scene::process_default_msg,
			this,
			_1));
}

void sanguis::draw::scene::process_message(
	client_messages::base const &m)
{
	dispatch_type<
		boost::mpl::vector<
			client_messages::add
		>,
		void
	>(
		*this,
		m,
		boost::bind(
			&scene::process_default_client_msg,
			this,
			_1));
}

void sanguis::draw::scene::draw(
	time_type const delta)
{
	time_type const real_delta =
		paused
		? 0
		: delta;
	
	for(entity_map::iterator it(entities.begin()), next(it); it != entities.end(); it = next)
	{
		draw::entity &e = *it->second;
		++next;

		e.update(real_delta);

		if(e.may_be_removed())
		{
			e.on_remove();
			if(e.remove_action() == draw::remove_action::render_dead)
				dead_list.transfer(
					it,
					entities);
			else
				entities.erase(it);
		}
	}

	BOOST_FOREACH(entity_map::reference r, dead_list)
		r.second->update(real_delta);
	
	if(dead_list.size() > 5)
		render_dead();
	
	system().render();

	hud_.update(delta);
}

void sanguis::draw::scene::pause(
	bool const p)
{
	paused = p;
}

void sanguis::draw::scene::operator()(
	messages::add const &m)
{
	configure_new_object(
		factory::entity(
			environment(),
			m.id(),
			m.type()),
		m);
}

void sanguis::draw::scene::operator()(
	messages::add_enemy const &m)
{
	configure_new_object(
		factory::enemy(
			environment(),
			m.id(),
			m.etype()),
		m);
}

void sanguis::draw::scene::operator()(
	messages::add_decoration const &m)
{
	SGE_LOG_DEBUG(
		log(),
		sge::log::_1 << SGE_TEXT("received add_decoration message"));
	
	configure_new_object(
		factory::decoration(
			environment(),
			m.id(),
			m.ptype()),
		m);
}

void sanguis::draw::scene::operator()(
	messages::add_pickup const &m)
{
	configure_new_object(
		factory::pickup(
			environment(),
			m.id(),
			m.ptype()),
		m);
}

void sanguis::draw::scene::operator()(
	messages::add_projectile const &m)
{
	configure_new_object(
		factory::projectile(
			environment(),
			m.id(),
			m.ptype()),
		m);
}

void sanguis::draw::scene::operator()(
	messages::add_weapon_pickup const &m)
{
	configure_new_object(
		factory::weapon_pickup(
			environment(),
			m.id(),
			m.wtype()),
		m);
}

void sanguis::draw::scene::operator()(
	messages::change_weapon const &m)
{
	messages::enum_type const value(
		m.weapon());
	
	if(value >= static_cast<messages::enum_type>(weapon_type::size))
	{
		SGE_LOG_WARNING(
			log(),
			sge::log::_1 << SGE_TEXT("Invalid change_weapon message: Value out of range!"));
		return;
	}
	
	entity(m.id()).weapon(
		static_cast<weapon_type::type>(
			m.weapon()));
}

void sanguis::draw::scene::operator()(
	messages::experience const &m)
{
	hud_.experience(m.exp());
}

void sanguis::draw::scene::operator()(
	messages::health const &m)
{
	entity(m.id()).health(m.value());
}

void sanguis::draw::scene::operator()(
	messages::max_health const &m)
{
	entity(m.id()).max_health(m.value());
}

void sanguis::draw::scene::operator()(
	messages::move const &m)
{
	entity(m.id()).pos(
		virtual_to_screen(
			ss.renderer()->screen_size(), m.pos()));
}

void sanguis::draw::scene::operator()(
	messages::remove const &m)
{
	entity_map::iterator const it(entities.find(m.id()));
	if(it == entities.end())
		throw exception(
			SGE_TEXT("Object not in entity map, can't remove it!"));
	draw::entity &e(*it->second);
	e.decay();
}

void sanguis::draw::scene::operator()(
	messages::resize const &m)
{
	//entity(m.id()).dim(virtual_to_screen(ss.renderer()->screen_size(), m.dim()));
	entity(m.id()).dim(sge::math::structure_cast<sge::sprite::unit>(m.dim()));
}

void sanguis::draw::scene::operator()(
	messages::rotate const &m)
{
	entity(m.id()).orientation(m.rot());
}

void sanguis::draw::scene::operator()(
	messages::speed const &m)
{
	entity(m.id()).speed(
		sge::math::structure_cast<funit>(
			virtual_to_screen(
				ss.renderer()->screen_size(),
				m.get())));
}

void sanguis::draw::scene::operator()(
	messages::start_attacking const &m)
{
	entity(m.id()).start_attacking();
}

void sanguis::draw::scene::operator()(
	messages::stop_attacking const &m)
{
	entity(m.id()).stop_attacking();
}

void sanguis::draw::scene::operator()(
	messages::start_reloading const &m)
{
	entity(m.id()).start_reloading();
}

void sanguis::draw::scene::operator()(
	messages::stop_reloading const &m)
{
	entity(m.id()).stop_reloading();
}

void sanguis::draw::scene::operator()(
	client_messages::add const &m)
{
	if(entities.insert(
		m.id(),
		factory::client(
			environment(),
			m,
			system().renderer()->screen_size())).second
	== false)
		throw exception(SGE_TEXT("Client object with id already in entity list!"));
	// FIXME: configure the object here, too!
}

void sanguis::draw::scene::configure_new_object(
	entity_auto_ptr e_ptr,
	messages::add const &m)
{
	std::pair<entity_map::iterator, bool> const ret(
		entities.insert(
			m.id(),
			e_ptr));

	if(ret.second == false)
	{
		SGE_LOG_WARNING(
			log(),
			sge::log::_1
				<< SGE_TEXT("Object with id ")
				<< m.id()
				<< SGE_TEXT(" already in entity list!"));
		return;
	//	throw exception(
	//		SGE_TEXT("Object with id already in entity list!"));
	}

	// configure the object
	process_message(messages::max_health(m.id(), m.max_health()));
	process_message(messages::health(m.id(), m.health()));
	process_message(messages::move(m.id(), m.pos()));
	process_message(messages::resize(m.id(), m.dim()));
	process_message(messages::rotate(m.id(), m.angle()));
	process_message(messages::speed(m.id(), m.speed()));
}

void sanguis::draw::scene::render_dead()
{
	sge::renderer::device_ptr const rend(
		system().renderer());

	draw::system temp_sys(rend);
	
	BOOST_FOREACH(entity_map::reference r, dead_list)
		r.second->transfer(
			temp_sys);
	
	/*
	background().paint_dead(
		temp_sys);*/
	
	dead_list.clear();
}

sanguis::draw::background &
sanguis::draw::scene::background()
{
	return dynamic_cast<
		draw::background &
	>(
		entity(
			background_id));
}

sanguis::draw::environment const &
sanguis::draw::scene::environment()
{
	return env;
}

void sanguis::draw::scene::insert(
	entity_auto_ptr e)
{
	entity_id const id(
		e->id());
	
	if(!entities.insert(
		id,
		e).second
	)
		throw exception(
			SGE_TEXT("scene::insert(): failed to insert!"));
	
}

sanguis::draw::entity &
sanguis::draw::scene::entity(
	entity_id const id)
{
	entity_map::iterator const it = entities.find(id);
	if(it == entities.end())
		throw exception(
			(sge::format(
				SGE_TEXT("Object with id %1% not in entity map!"))
				% id).str());
	return *it->second;
}

sanguis::draw::entity const &
sanguis::draw::scene::entity(
	entity_id const id) const
{
	return const_cast<draw::entity const &>(
		const_cast<scene &>(*this).entity(id));
}

void sanguis::draw::scene::process_default_msg(
messages::base const &m)
{
	SGE_LOG_WARNING(
		log(),
		sge::log::_1
			<< SGE_TEXT("Invalid message event in scene: ")
			<< sge::iconv(typeid(m).name()));
}

void sanguis::draw::scene::process_default_client_msg(
	client_messages::base const &m)
{
	SGE_LOG_WARNING(
		log(),
		sge::log::_1
			<< SGE_TEXT("Invalid client message event in scene: ")
			<< sge::iconv(typeid(m).name()));
}

sanguis::draw::system &
sanguis::draw::scene::system()
{
	return ss;
}

sge::log::logger &
sanguis::draw::scene::log()
{
	static sge::log::logger log_(
		draw::log(),
		SGE_TEXT("scene: "));
	return log_;
}
