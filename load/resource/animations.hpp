#ifndef SANGUIS_LOAD_RESOURCE_ANIMATIONS_HPP_INCLUDED
#define SANGUIS_LOAD_RESOURCE_ANIMATIONS_HPP_INCLUDED

#include <sge/sprite/animation_series.hpp>
#include <sge/texture/part_fwd.hpp>
#include <sge/path.hpp>
#include <boost/noncopyable.hpp>
#include <map>

namespace sanguis
{
namespace load
{
namespace resource
{

class textures;

class animations : boost::noncopyable {
public:
	sge::sprite::animation_series const
	load(
		sge::path const &);
private:
	sge::sprite::animation_series const
	do_load(
		sge::path const &);

	sge::texture::const_part_ptr const
	load_texture(
		sge::path const &) const;

	friend class context;

	explicit animations(
		textures &);

	typedef std::map<
		sge::path,
		sge::sprite::animation_series
	> animation_map;
	
	textures     &textures_;
	animation_map animations_;
};

}
}
}

#endif
