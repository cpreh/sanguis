#ifndef SANGUIS_LOAD_RESOURCE_TEXTURES_HPP_INCLUDED
#define SANGUIS_LOAD_RESOURCE_TEXTURES_HPP_INCLUDED

#include "texture_identifier.hpp"
#include "texture_context_fwd.hpp"
#include "texture_context.hpp"
#include <sge/texture/part_fwd.hpp>
#include <sge/texture/manager.hpp>
#include <sge/renderer/device_fwd.hpp>
#include <sge/image/loader_fwd.hpp>
#include <sge/filesystem/path.hpp>
#include <sge/noncopyable.hpp>
#include <map>

namespace sanguis
{
namespace load
{
namespace resource
{

class textures {
	SGE_NONCOPYABLE(textures)
public:
	sge::texture::part_ptr const
	load(
		texture_identifier const &) const;

	texture_context const
	load(
		sge::filesystem::path const &) const;
	
	void cleanup() const;
	
	~textures();
private:
	friend class context;
	friend class animations;

	sge::texture::part_ptr const
	do_load(
		texture_identifier const &) const;
	
	texture_context_impl_ptr const
	do_load_unnamed(
		sge::filesystem::path const &) const;

	sge::texture::part_ptr const
	do_load_inner(
		sge::filesystem::path const &) const;

	textures(
		sge::renderer::device_ptr,
		sge::image::loader_ptr);

	typedef std::map<
		texture_identifier,
		sge::texture::part_ptr
	> texture_map;

	typedef std::map<
		sge::filesystem::path,
		texture_context_impl_ptr
	> unnamed_texture_map;

	typedef std::map<
		texture_identifier,
		texture_identifier
	> texture_name_map;

	mutable sge::texture::manager texman;
	sge::image::loader_ptr const il;
	mutable texture_map textures_;
	mutable unnamed_texture_map unnamed_textures;
	mutable texture_name_map texture_names;
};

}
}
}

#endif
