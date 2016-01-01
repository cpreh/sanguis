#include <sanguis/exception.hpp>
#include <sanguis/media_path.hpp>
#include <sanguis/client/load/log.hpp>
#include <sanguis/client/load/resource/make_missing_texture.hpp>
#include <sanguis/client/load/resource/search_texture_names.hpp>
#include <sanguis/client/load/resource/texture_identifier.hpp>
#include <sanguis/client/load/resource/textures.hpp>
#include <sge/image/size_type.hpp>
#include <sge/image/color/predef.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/image2d/file.hpp>
#include <sge/image2d/system.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <sge/renderer/texture/create_planar_from_path.hpp>
#include <sge/renderer/texture/emulate_srgb.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <sge/renderer/texture/mipmap/off.hpp>
#include <sge/texture/const_optional_part_ref.hpp>
#include <sge/texture/const_part_unique_ptr.hpp>
#include <sge/texture/part.hpp>
#include <sge/texture/part_raw_ptr.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/unique_ptr_to_const.hpp>
#include <fcppt/container/find_opt_mapped.hpp>
#include <fcppt/container/get_or_insert.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/error.hpp>
#include <fcppt/optional/to_exception.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


sge::texture::part const &
sanguis::client::load::resource::textures::load(
	sanguis::client::load::resource::texture_identifier const &_id
) const
{
	return
		*fcppt::container::get_or_insert(
			textures_,
			_id,
			std::bind(
				&sanguis::client::load::resource::textures::do_load,
				this,
				std::placeholders::_1
			)
		);
}

sge::texture::part const &
sanguis::client::load::resource::textures::load(
	boost::filesystem::path const &_path
) const
{
	return
		*fcppt::container::get_or_insert(
			unnamed_textures_,
			_path,
			std::bind(
				&sanguis::client::load::resource::textures::do_load_inner,
				this,
				std::placeholders::_1
			)
		);
}

sge::texture::const_optional_part_ref
sanguis::client::load::resource::textures::load_opt(
	boost::filesystem::path const &_path
) const
try
{
	// TODO: This should be the other way around (exception from optional)
	return
		sge::texture::const_optional_part_ref{
			this->load(
				_path
			)
		};
}
catch(
	fcppt::exception const &_error
)
{
	FCPPT_LOG_ERROR(
		sanguis::client::load::log(),
		fcppt::log::_
			<<
			FCPPT_TEXT("Failed to load ")
			<<
			fcppt::filesystem::path_to_string(
				_path
			)
			<<
			FCPPT_TEXT(": ")
			<<
			_error.string()
	);

	return
		sge::texture::const_optional_part_ref();
}

sge::texture::part const &
sanguis::client::load::resource::textures::missing_texture() const
{
	return
		*missing_texture_;
}

sge::image2d::system &
sanguis::client::load::resource::textures::image_system() const
{
	return
		image_loader_;
}

sge::renderer::device::core &
sanguis::client::load::resource::textures::renderer() const
{
	return
		renderer_;
}

sanguis::client::load::resource::textures::textures(
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
		sanguis::client::load::resource::search_texture_names()
	),
	textures_(),
	unnamed_textures_(),
	missing_texture_(
		sanguis::client::load::resource::make_missing_texture(
			renderer_,
			fcppt::literal<
				sge::image::size_type
			>(
				64
			),
			sge::image::color::predef::magenta(),
			sge::image::color::predef::black()
		)
	)
{
}

sanguis::client::load::resource::textures::~textures()
{
}

sge::texture::const_part_unique_ptr
sanguis::client::load::resource::textures::do_load(
	sanguis::client::load::resource::texture_identifier const &_id
) const
{
	return
		this->do_load_inner(
			sanguis::media_path()
			/
			fcppt::optional::to_exception(
				fcppt::container::find_opt_mapped(
					texture_names_,
					_id
				),
				[
					_id
				]
				{
					return
						sanguis::exception{
							FCPPT_TEXT("no texture for id \"")
							+
							_id.get()
							+
							FCPPT_TEXT("\" found")
						};
				}
			)
		);
}

sge::texture::const_part_unique_ptr
sanguis::client::load::resource::textures::do_load_inner(
	boost::filesystem::path const &_path
) const
{
	return
		fcppt::unique_ptr_to_const(
			fcppt::unique_ptr_to_base<
				sge::texture::part
			>(
				fcppt::make_unique_ptr<
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
			)
		);
}
