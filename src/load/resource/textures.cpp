#include "textures.hpp"
#include "texture_context.hpp"
#include "texture_context_impl.hpp"
#include "map_get_or_create.hpp"
#include "../log.hpp"
#include "../../exception.hpp"
#include "../../media_path.hpp"
#include <sge/texture/add_image.hpp>
#include <sge/texture/no_fragmented.hpp>
#include <sge/texture/part_raw.hpp>
#include <sge/renderer/texture/mipmap/off.hpp>
#include <sge/renderer/resource_flags_none.hpp>
#include <sge/image2d/multi_loader.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/filesystem/directory_iterator.hpp>
#include <fcppt/filesystem/extension.hpp>
#include <fcppt/filesystem/is_regular.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/io/ifstream.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/spirit/home/phoenix/object/construct.hpp>
#include <boost/spirit/home/phoenix/object/new.hpp>

sge::texture::part_ptr const
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
	fcppt::filesystem::path const &_path
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
	sge::renderer::device &_renderer,
	sge::image2d::multi_loader &_image_loader
)
:
	renderer_(
		_renderer
	),
	texture_manager_(
		boost::phoenix::construct<
			sge::texture::fragmented_unique_ptr
		>(
			boost::phoenix::new_<
				sge::texture::no_fragmented
			>(
				fcppt::ref(
					_renderer
				),
				sge::image::color::format::rgba8,
				sge::renderer::texture::mipmap::off(),
				sge::renderer::texture::address_mode2(
					sge::renderer::texture::address_mode::repeat
				)
			)
		)
	),
	image_loader_(
		_image_loader
	)
{
	// look for .tex files
	for(
		fcppt::filesystem::directory_iterator it(
			sanguis::media_path()
		), end;
		it != end;
		++it
	)
	{
		fcppt::filesystem::path const &path(
			it->path()
		);

		if(
			!fcppt::filesystem::is_regular(
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

sge::texture::part_ptr const
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
	fcppt::filesystem::path const &_path
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

sge::texture::part_ptr const
sanguis::load::resource::textures::do_load_inner(
	fcppt::filesystem::path const &_path
) const
{
	return
		sge::texture::add_image(
			texture_manager_,
			*image_loader_.load(
				_path
			)
		);
}
