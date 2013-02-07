#ifndef SANGUIS_LOAD_RESOURCE_TEXTURES_HPP_INCLUDED
#define SANGUIS_LOAD_RESOURCE_TEXTURES_HPP_INCLUDED

#include <sanguis/load/resource/texture_identifier.hpp>
#include <sanguis/load/resource/texture_name_map.hpp>
#include <sge/image2d/system_fwd.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <sge/texture/const_part_shared_ptr.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <map>
#include <fcppt/config/external_end.hpp>


namespace sanguis
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
	sge::texture::const_part_shared_ptr const
	load(
		sanguis::load::resource::texture_identifier const &
	) const;

	sge::texture::const_part_shared_ptr const
	load(
		boost::filesystem::path const &
	) const;

	textures(
		sge::renderer::device::core &,
		sge::image2d::system &
	);

	~textures();
private:
	friend class animations;

	sge::texture::const_part_shared_ptr const
	do_load(
		sanguis::load::resource::texture_identifier const &
	) const;

	sge::texture::const_part_shared_ptr const
	do_load_inner(
		boost::filesystem::path const &
	) const;

	typedef std::map<
		sanguis::load::resource::texture_identifier,
		sge::texture::const_part_shared_ptr
	> texture_map;

	typedef std::map<
		boost::filesystem::path,
		sge::texture::const_part_shared_ptr
	> unnamed_texture_map;

	sge::renderer::device::core &renderer_;

	sge::image2d::system &image_loader_;

	mutable sanguis::load::resource::texture_name_map texture_names_;

	mutable texture_map textures_;

	mutable unnamed_texture_map unnamed_textures_;
};

}
}
}

#endif
