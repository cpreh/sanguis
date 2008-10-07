#ifndef SANGUIS_LOAD_RESOURCE_ENVIRONMENT_HPP_INCLUDED
#define SANGUIS_LOAD_RESOURCE_ENVIRONMENT_HPP_INCLUDED

#include "factory.hpp"
#include <sge/renderer/device_fwd.hpp>
#include <sge/image/loader_fwd.hpp>
#include <sge/audio/multi_loader.hpp>
#include <sge/audio/player_fwd.hpp>
#include <sge/texture/manager.hpp>
#include <sge/string.hpp>
#include <sge/path.hpp>
#include <boost/noncopyable.hpp>
#include <map>

namespace sanguis
{
namespace load
{
namespace resource
{
/*
 * what's all this about? well, the functions in factory.hpp are global, so
 * accessible everywhere and without a specific object attached to them.
 * internally, however, we have to use an object which has all the loaders in it
 * to load those files. so we create something like a singleton which is created
 * by creating a connection object. if you create more than one connection
 * object, you get an exception. this connection object updates the "global_env"
 * pointer to point to a valid environment object. it also releases the pointer
 * and sets it to 0 when it's destroyed.
 */
class environment : boost::noncopyable
{
	public:
	environment(
		sge::image::loader_ptr,
		sge::renderer::device_ptr,
		sge::audio::multi_loader &,
		sge::audio::player_ptr);

	sge::texture::part_ptr const load_texture(
		sanguis::load::resource::identifier_type const &);
	sge::audio::sound_ptr const load_sound(
		sge::path const &);
	sge::sprite::animation_series const load_animation(
		sge::path const &);

	private:
	sge::renderer::device_ptr const rend;
	sge::image::loader_ptr const il;
	sge::audio::multi_loader &ml;
	sge::audio::player_ptr const player;
	sge::texture::manager texman;
	std::map<identifier_type,identifier_type> texture_names;

	typedef std::map<sanguis::load::resource::identifier_type,
									 sge::texture::part_ptr>
		texture_map;

	typedef std::map<sge::path,
									 sge::sprite::animation_series>
		animation_map;
	
	typedef std::vector<sge::audio::file_ptr> sound_container;

	typedef std::map<sge::path,
									 sound_container>
		sound_map;
	
	texture_map textures;
	animation_map animations;
	sound_map sounds;

	// internal functions
	sge::texture::part_ptr const do_load_texture(
		sanguis::load::resource::identifier_type const &);
	sound_container const do_load_sound(
		sge::path const &);
	sge::sprite::animation_series const do_load_animation(
		sge::path const &);

	// helper functions
	void load_textures();
	sge::texture::part_ptr const do_load_texture_inner(
		sge::path const &);
};

environment *&global_env();
}
}
}

#endif
