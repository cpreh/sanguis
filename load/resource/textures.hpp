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
	sge::texture::part_ptr const
	load(
		texture_identifier const &);
private:
	friend class context;

	sge::texture::part_ptr const
	do_load_texture(
		texture_identifier const &);

	sge::texture::part_ptr const
	do_load_inner(
		sge::path const &);

	textures(
		sge::renderer::device_ptr,
		sge::image::loader_ptr);
	~textures();

	typedef std::map<
		texture_identifier,
		sge::texture::part_ptr
	> texture_map;

	sge::texture::manager texman;
	sge::image::loader_ptr const il;
	texture_map textures;
};

}
}
}

#endif
