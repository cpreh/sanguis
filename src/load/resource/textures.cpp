#include <sanguis/exception.hpp>
#include <sanguis/media_path.hpp>
#include <sanguis/load/resource/search_texture_names.hpp>
#include <sanguis/load/resource/texture_identifier.hpp>
#include <sanguis/load/resource/textures.hpp>
#include <sanguis/load/resource/map_get_or_create.hpp>
#include <sge/image2d/file.hpp>
#include <sge/image2d/system.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <sge/renderer/texture/create_planar_from_path.hpp>
#include <sge/renderer/texture/emulate_srgb.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <sge/renderer/texture/mipmap/off.hpp>
#include <sge/texture/const_part_shared_ptr.hpp>
#include <sge/texture/part_raw_ptr.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


sge::texture::const_part_shared_ptr const
sanguis::load::resource::textures::load(
	sanguis::load::resource::texture_identifier const &_id
) const
{
	return
		sanguis::load::resource::map_get_or_create(
			textures_,
			_id,
			std::bind(
				&sanguis::load::resource::textures::do_load,
				this,
				std::placeholders::_1
			)
		);
}

sge::texture::const_part_shared_ptr const
sanguis::load::resource::textures::load(
	boost::filesystem::path const &_path
) const
{
	return
		sge::texture::const_part_shared_ptr(
			sanguis::load::resource::map_get_or_create(
				unnamed_textures_,
				_path,
				std::bind(
					&sanguis::load::resource::textures::do_load_inner,
					this,
					std::placeholders::_1
				)
			)
		);
}

sanguis::load::resource::textures::textures(
	sge::renderer::device::core &_renderer,
	sge::image2d::system &_image_loader
)
:
	renderer_(
		_renderer
	),
	image_loader_(
		_image_loader
	),
	texture_names_(
		sanguis::load::resource::search_texture_names()
	),
	textures_(),
	unnamed_textures_()
{
}

sanguis::load::resource::textures::~textures()
{
}

sge::texture::const_part_shared_ptr const
sanguis::load::resource::textures::do_load(
	sanguis::load::resource::texture_identifier const &_id
) const
{
	if(
		texture_names_.find(
			_id
		)
		== texture_names_.end()
	)
		throw sanguis::exception(
			FCPPT_TEXT("no texture for id \"")
			+
			_id.get()
			+
			FCPPT_TEXT("\" found")
		);

	return
		this->do_load_inner(
			sanguis::media_path()
			/
			texture_names_[
				_id
			]
		);
}

sge::texture::const_part_shared_ptr const
sanguis::load::resource::textures::do_load_inner(
	boost::filesystem::path const &_path
) const
{
	return
		sge::texture::const_part_shared_ptr(
			fcppt::make_shared_ptr<
				sge::texture::part_raw_ptr
			>(
				sge::renderer::texture::create_planar_from_path(
					_path,
					renderer_,
					image_loader_,
					sge::renderer::texture::mipmap::off(),
					sge::renderer::resource_flags_field::null(),
					sge::renderer::texture::emulate_srgb::yes
				)
			)
		);
}
