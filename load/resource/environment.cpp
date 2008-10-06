#include "environment.hpp"
#include <sge/texture/default_creator_impl.hpp>
#include <sge/texture/no_fragmented.hpp>
#include <sge/random/uniform.hpp>
#include <boost/bind.hpp>
#include <ctime>
#include <cstdlib>

namespace
{
template<
	typename Key, 
	typename Mapped, 
	typename Comp, 
	typename Alloc, 
	typename Fun>
Mapped& map_get_or_create(
	std::map<Key, Mapped, Comp, Alloc>& map, 
	Key const& key, 
	Fun const& creator)
{
	typename std::map<Key, Mapped, Comp, Alloc>::iterator it = map.find(key);
	return it != map.end() 
		? it->second 
		: map.insert(std::make_pair(key, creator(key))).first->second;
}
}

sanguis::load::resource::environment *&sanguis::load::resource::global_env()
{
	static environment *ptr = 0;
	return ptr;
}

sanguis::load::resource::environment::environment(
	sge::image::loader_ptr const il,
	sge::renderer::device_ptr const r,
	sge::audio::multi_loader &ml,
	sge::audio::player_ptr const player) 
: rend(r),
  il(il),
	ml(ml),
	player(player),
  texman(
  	rend,
	sge::texture::default_creator<sge::texture::no_fragmented>(
		rend,
		sge::renderer::linear_filter))
{
	load_textures();
}

sge::sprite::animation_series const
sanguis::load::resource::environment::load_animation(
	sge::path const& dir)
{
	return map_get_or_create(
		animations, 
		dir, 
		boost::bind(&environment::do_load_animation,this,_1));
}


sge::audio::sound_ptr const sanguis::load::resource::environment::load_sound(
	sge::path const &dir)
{
	sound_container &s = map_get_or_create(
		sounds, 
		dir, 
		boost::bind(&environment::do_load_sound,this,_1));
	
	static sge::random::uniform<sound_container::size_type> 
		rng(
			static_cast<sound_container::size_type>(0),
			s.size());
	return s[rng()];
}

sge::texture::part_ptr const sanguis::load::resource::environment::load_texture(
	sanguis::load::resource::identifier_type const&id)
{
	return map_get_or_create(
		textures, 
		id, 
		boost::bind(&environment::do_load_texture,this,_1));
}
