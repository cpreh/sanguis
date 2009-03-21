#ifndef SANGUIS_LOAD_RESOURCE_ANIMATIONS_HPP_INCLUDED
#define SANGUIS_LOAD_RESOURCE_ANIMATIONS_HPP_INCLUDED

#include <sge/sprite/animation_series.hpp>
#include <sge/texture/part_fwd.hpp>
#include <sge/filesystem/path.hpp>
#include <sge/noncopyable.hpp>
#include <map>

namespace sanguis
{
namespace load
{
namespace resource
{

class textures;

class animations {
	SGE_NONCOPYABLE(animations)
public:
	sge::sprite::animation_series const
	load(
		sge::filesystem::path const &) const;
private:
	sge::sprite::animation_series const
	do_load(
		sge::filesystem::path const &) const;

	sge::texture::const_part_ptr const
	load_texture(
		sge::filesystem::path const &) const;
	
	sge::sprite::animation_series const
	load_without_frames_file(
		sge::filesystem::path const &) const;

	friend class context;

	explicit animations(
		textures &);

	typedef std::map<
		sge::filesystem::path,
		sge::sprite::animation_series
	> animation_map;
	
	textures     &textures_;
	mutable animation_map animations_;
};

}
}
}

#endif
