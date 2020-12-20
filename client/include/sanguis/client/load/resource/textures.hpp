#ifndef SANGUIS_CLIENT_LOAD_RESOURCE_TEXTURES_HPP_INCLUDED
#define SANGUIS_CLIENT_LOAD_RESOURCE_TEXTURES_HPP_INCLUDED

#include <sanguis/client/load/resource/texture_identifier.hpp>
#include <sanguis/client/load/resource/texture_name_map.hpp>
#include <sge/image/size_type.hpp>
#include <sge/image/color/any/object_fwd.hpp>
#include <sge/image2d/system_fwd.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <sge/texture/const_optional_part_ref_fwd.hpp>
#include <sge/texture/const_part_unique_ptr.hpp>
#include <sge/texture/part_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/log/context_reference_fwd.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <map>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace client
{
namespace load
{
namespace resource
{

class textures
{
	FCPPT_NONCOPYABLE(
		textures
	);
public:
	sge::texture::part const &
	load(
		sanguis::client::load::resource::texture_identifier const &
	) const;

	sge::texture::part const &
	load(
		std::filesystem::path const &
	) const;

	sge::texture::const_optional_part_ref
	load_opt(
		std::filesystem::path const &
	) const;

	sge::texture::part const &
	missing_texture() const;

	// TODO: Remove this
	sge::image2d::system &
	image_system() const;

	// TODO: Remove this
	sge::renderer::device::core &
	renderer() const;

	textures(
		fcppt::log::context_reference,
		sge::renderer::device::core &,
		sge::image2d::system &
	);

	~textures();
private:
	sge::texture::const_part_unique_ptr
	do_load(
		sanguis::client::load::resource::texture_identifier const &
	) const;

	sge::texture::const_part_unique_ptr
	do_load_inner(
		std::filesystem::path const &
	) const;

	using
	texture_map
	=
	std::map<
		sanguis::client::load::resource::texture_identifier,
		sge::texture::const_part_unique_ptr
	>;

	using
	unnamed_texture_map
	=
	std::map<
		std::filesystem::path,
		sge::texture::const_part_unique_ptr
	>;

	mutable fcppt::log::object log_;

	sge::renderer::device::core &renderer_;

	sge::image2d::system &image_loader_;

	mutable sanguis::client::load::resource::texture_name_map texture_names_;

	mutable texture_map textures_;

	mutable unnamed_texture_map unnamed_textures_;

	sge::texture::const_part_unique_ptr const missing_texture_;
};

}
}
}
}

#endif
