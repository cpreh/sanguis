#ifndef SANGUIS_LOAD_RESOURCE_ANIMATIONS_HPP_INCLUDED
#define SANGUIS_LOAD_RESOURCE_ANIMATIONS_HPP_INCLUDED

#include "textures_fwd.hpp"
#include <sge/sprite/animation/series.hpp>
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
class animations {
	SGE_NONCOPYABLE(animations)
public:
	sge::sprite::animation::series const
	load(
		sge::filesystem::path const &
	) const;
private:
	sge::sprite::animation::series const
	do_load(
		sge::filesystem::path const &
	) const;

	sge::texture::const_part_ptr const
	load_texture(
		sge::filesystem::path const &
	) const;
	
	sge::sprite::animation::series const
	load_without_frames_file(
		sge::filesystem::path const &
	) const;

	friend class context;

	explicit animations(
		textures &);

	typedef std::map<
		sge::filesystem::path,
		sge::sprite::animation::series
	> animation_map;
	
	textures     &textures_;
	mutable animation_map animations_;
};

}
}
}

#endif
