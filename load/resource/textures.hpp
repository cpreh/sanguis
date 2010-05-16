#ifndef SANGUIS_LOAD_RESOURCE_TEXTURES_HPP_INCLUDED
#define SANGUIS_LOAD_RESOURCE_TEXTURES_HPP_INCLUDED

#include "../../time_type.hpp"
#include "texture_identifier.hpp"
#include "texture_context_fwd.hpp"
#include "texture_context.hpp"
#include <sge/texture/part_ptr.hpp>
#include <sge/texture/manager.hpp>
#include <sge/renderer/device_ptr.hpp>
#include <sge/image/multi_loader_fwd.hpp>
#include <fcppt/filesystem/path.hpp>
#include <fcppt/noncopyable.hpp>
#include <map>

namespace sanguis
{
namespace load
{
namespace resource
{

class textures {
	FCPPT_NONCOPYABLE(textures)
public:
	sge::texture::part_ptr const
	load(
		texture_identifier const &
	) const;

	texture_context const
	load(
		fcppt::filesystem::path const &
	) const;
	
	void
	cleanup(
		time_type
	) const;
	
	~textures();
private:
	friend class context;
	friend class animations;

	sge::texture::part_ptr const
	do_load(
		texture_identifier const &
	) const;
	
	texture_context_impl_ptr const
	do_load_unnamed(
		fcppt::filesystem::path const &
	) const;

	sge::texture::part_ptr const
	do_load_inner(
		fcppt::filesystem::path const &
	) const;

	textures(
		sge::renderer::device_ptr,
		sge::image::multi_loader const &
	);

	typedef std::map<
		texture_identifier,
		sge::texture::part_ptr
	> texture_map;

	typedef std::map<
		fcppt::filesystem::path,
		texture_context_impl_ptr
	> unnamed_texture_map;

	typedef std::map<
		texture_identifier,
		texture_identifier
	> texture_name_map;

	mutable sge::texture::manager texman;

	sge::image::multi_loader const &il;

	mutable texture_map textures_;

	mutable unnamed_texture_map unnamed_textures;

	mutable texture_name_map texture_names;
};

}
}
}

#endif
