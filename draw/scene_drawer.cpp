#include "scene_drawer.hpp"
#include "factory.hpp"
#include "player.hpp"
#include "virtual_to_screen.hpp"
#include "../dispatch_type.hpp"
#include "../messages/base.hpp"
#include "../messages/add.hpp"
#include "../messages/move.hpp"
#include "../messages/player_state.hpp"
#include "../messages/remove.hpp"
#include "../messages/rotate.hpp"
#include "../messages/speed.hpp"

#include <sge/exception.hpp>
#include <sge/iostream.hpp>
#include <sge/iconv.hpp>
#include <sge/string.hpp>
#include <sge/sprite/system_impl.hpp>

#include <boost/foreach.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/bind.hpp>

#include <algorithm>
#include <functional>
#include <typeinfo>

sanguis::draw::scene_drawer::scene_drawer(const sge::renderer_ptr rend)
: ss(rend),
  player_(0)
{}

void sanguis::draw::scene_drawer::process_message(const messages::base& m)
{
	dispatch_type<
		boost::mpl::vector<
			messages::add,
			messages::move,
			messages::player_state,
			messages::remove,
			messages::rotate,
			messages::speed
			>,
		void>(
		*this,
		m,
		boost::bind(&scene_drawer::process_default_msg, this, _1));
}

void sanguis::draw::scene_drawer::draw(const tick_data &t)
{
	sprites.clear();

	const sge::timer::frames_type diff_time = t.diff_time;
	BOOST_FOREACH(entity_map::value_type val, entities)
	{
		entity& e = *val.second;
		e.update(diff_time);
		const entity::sprite_vector& s(e.to_sprites());
		std::copy(s.begin(), s.end(), std::back_inserter(sprites));
	}

	ss.render(sprites.begin(), sprites.end());
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
	if(entities.insert(m.id(), factory::create_entity(m,ss.get_renderer()->screen_size())).second == false)
		throw sge::exception(SGE_TEXT("Object with id already in entity list!"));
	if(m.type() == entity_type::player)
	{
		if(player_)
			throw sge::exception(SGE_TEXT("Player already exists in scene_drawer!"));
		const entity_map::iterator it(entities.find(m.id()));
		// TODO: maybe take the address of the auto_ptr directly?
		player_ = dynamic_cast<player*>(it->second);
	}
}

void sanguis::draw::scene_drawer::operator()(const messages::move& m)
{
	get_entity(m.id()).pos(virtual_to_screen(ss.get_renderer()->screen_size(),m.pos()));
}

void sanguis::draw::scene_drawer::operator()(const messages::player_state& m)
{
}

void sanguis::draw::scene_drawer::operator()(const messages::remove& m)
{
	if(entities.erase(m.id()) == 0)
		throw sge::exception(SGE_TEXT("Object with id not in entity list!"));
}

void sanguis::draw::scene_drawer::operator()(const messages::rotate& m)
{
	get_entity(m.id()).orientation(m.rot());
}

void sanguis::draw::scene_drawer::operator()(const messages::speed& m)
{
	get_entity(m.id()).speed(m.get());
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
