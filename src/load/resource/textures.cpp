#include <sanguis/load/resource/textures.hpp>
#include <sanguis/load/resource/texture_context.hpp>
#include <sanguis/load/resource/texture_context_impl.hpp>
#include <sanguis/load/resource/map_get_or_create.hpp>
#include <sanguis/load/log.hpp>
#include <sanguis/exception.hpp>
#include <sanguis/media_path.hpp>
#include <sge/image2d/file.hpp>
#include <sge/image2d/system.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/texture/create_planar_from_path.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <sge/renderer/texture/mipmap/off.hpp>
#include <sge/texture/part_raw_ptr.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/filesystem/extension.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/io/ifstream.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>

sge::texture::const_part_shared_ptr const
sanguis::load::resource::textures::load(
	texture_identifier const &_id
) const
{
	return
		resource::map_get_or_create(
			textures_,
			_id,
			std::tr1::bind(
				&textures::do_load,
				this,
				std::tr1::placeholders::_1
			)
		);
}

sanguis::load::resource::texture_context const
sanguis::load::resource::textures::load(
	boost::filesystem::path const &_path
) const
{
	return
		resource::texture_context(
			resource::map_get_or_create(
				unnamed_textures_,
				_path,
				std::tr1::bind(
					&textures::do_load_unnamed,
					this,
					std::tr1::placeholders::_1
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
	)
{
	// look for .tex files
	for(
		boost::filesystem::directory_iterator it(
			sanguis::media_path()
		), end;
		it != end;
		++it
	)
	{
		boost::filesystem::path const &path(
			it->path()
		);

		if(
			!boost::filesystem::is_regular_file(
				path
			)
			||
			fcppt::filesystem::extension(
				path
			)
			!= FCPPT_TEXT(".tex")
		)
			continue;

		// and parse line by line
		fcppt::io::ifstream file(
			path
		);

		if(
			!file.is_open()
		)
			throw sanguis::exception(
				FCPPT_TEXT("error opening id file \"")
				+ fcppt::filesystem::path_to_string(
					path
				)
				+ FCPPT_TEXT('"')
			);

		std::streamsize line_num(0);

		fcppt::string line;

		while(
			std::getline(
				file,
				line
			)
		)
		{
			++line_num;

			boost::algorithm::trim(
				line
			);

			if (line.empty())
				continue;

			fcppt::string::size_type const equal(
				line.find(
					FCPPT_TEXT("=")
				)
			);

			if(
				equal == fcppt::string::npos
			)
			{
				FCPPT_LOG_WARNING(
					sanguis::load::log(),
					fcppt::log::_
						<< FCPPT_TEXT("Error in .id file \")")
						<< fcppt::filesystem::path_to_string(
							path
						)
						<< FCPPT_TEXT("\" in line ")
						<< line_num
						<< FCPPT_TEXT('!'));
				continue;
			}

			texture_names_[
				line.substr(
					0,
					equal
				)
			] =
				line.substr(
					equal + 1
				);
		}
	}
}

sanguis::load::resource::textures::~textures()
{
}

sge::texture::const_part_shared_ptr const
sanguis::load::resource::textures::do_load(
	texture_identifier const &_id
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
			+ _id
			+ FCPPT_TEXT("\" found")
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

sanguis::load::resource::texture_context_impl_ptr const
sanguis::load::resource::textures::do_load_unnamed(
	boost::filesystem::path const &_path
) const
{
	return
		fcppt::make_shared_ptr<
			texture_context_impl
		>(
			_path,
			fcppt::ref(
				renderer_
			),
			fcppt::ref(
				image_loader_
			)
		);
}

sge::texture::const_part_shared_ptr const
sanguis::load::resource::textures::do_load_inner(
	boost::filesystem::path const &_path
) const
{
	return
		sge::texture::const_part_shared_ptr(
			fcppt::make_unique_ptr<
				sge::texture::part_raw_ptr
			>(
				sge::renderer::texture::create_planar_from_path(
					_path,
					renderer_,
					image_loader_,
					sge::renderer::texture::mipmap::off(),
					sge::renderer::resource_flags_field::null()
				)
			)
		);
}
