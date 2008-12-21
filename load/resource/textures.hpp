#ifndef SANGUIS_LOAD_RESOURCE_TEXTURES_HPP_INCLUDED
#define SANGUIS_LOAD_RESOURCE_TEXTURES_HPP_INCLUDED

#include "texture_identifier.hpp"
#include <sge/texture/part_fwd.hpp>
#include <sge/texture/manager.hpp>
#include <sge/renderer/device_fwd.hpp>
#include <sge/image/loader_fwd.hpp>
#include <sge/path.hpp>
#include <boost/noncopyable.hpp>
#include <map>

namespace sanguis
{
namespace load
{
namespace resource
{

class textures : boost::noncopyable {
public:
	sge::texture::const_part_ptr const
	load(
		texture_identifier const &) const;

	~textures();
private:
	friend class context;
	friend class animations;

	sge::texture::const_part_ptr const
	do_load(
		texture_identifier const &) const;

	sge::texture::const_part_ptr const
	do_load_inner(
		sge::path const &) const;

	textures(
		sge::renderer::device_ptr,
		sge::image::loader_ptr);

	typedef std::map<
		texture_identifier,
		sge::texture::const_part_ptr
	> texture_map;

	typedef std::map<
		texture_identifier,
		texture_identifier
	> texture_name_map;

	mutable sge::texture::manager texman;
	sge::image::loader_ptr const il;
	mutable texture_map textures_;
	mutable texture_name_map texture_names;
};

}
}
}

#endif
