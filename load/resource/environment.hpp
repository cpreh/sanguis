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
class environment : boost::noncopyable
{
	public:
	environment(
		sge::image::loader_ptr,
		sge::renderer::device_ptr,
		sge::audio::multi_loader const &,
		sge::audio::player_ptr);

	sge::texture::part_ptr const load_texture(
		sanguis::load::resource::identifier_type const &);
	sge::audio::part_ptr const load_sound(
		sge::path const &);
	sge::sprite::animation_series const load_animation(
		sge::path const &);

	private:
	sge::renderer::device_ptr const rend;
	sge::image::loader_ptr const il;
	sge::audio::multi_loader const ml;
	sge::audio::player_ptr const player;
	sge::texture::manager texman;
	std::map<sge::string,sge::string> textures;

	typedef std::map<sanguis::load::resource::identifier_type,
									 sge::texture::part_ptr>
		texture_map;

	typedef std::map<sge::path,
									 sge::sprite::animation_series>
		animation_map;

	typedef std::map<sge::path,
									 sge::audio::file_ptr>
		sound_map;
	
	texture_map textures;
	animation_map animations;
	sound_map sounds;

	// internal functions
	sge::texture::part_ptr const do_load_texture(
		sanguis::load::resource::identifier_type const &);
	sge::audio::part_ptr const do_load_sound(
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
