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
#include <sge/renderer/filter/linear.hpp>
#include <sge/renderer/resource_flags_none.hpp>
#include <sge/image2d/multi_loader.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/filesystem/directory_iterator.hpp>
#include <fcppt/filesystem/extension.hpp>
#include <fcppt/filesystem/is_regular.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/io/ifstream.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/text.hpp>
#include <fcppt/string.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/spirit/home/phoenix/object/construct.hpp>
#include <boost/spirit/home/phoenix/object/new.hpp>

namespace
{

sge::renderer::filter::texture const
filter(
	sge::renderer::filter::linear
);

}

sge::texture::part_ptr const
sanguis::load::resource::textures::load(
	texture_identifier const &_id
) const
{
	return
		this->map_get_or_create(
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
			this->map_get_or_create(
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

void
sanguis::load::resource::textures::cleanup(
	time_type const _delta
) const
{
	for(
		unnamed_texture_map::iterator it(
			unnamed_textures_.begin()
		), next(it); 
		it != unnamed_textures_.end(); 
		it = next) 
	{ 
		++next; 

		it->second->tick(
			_delta
		);

		if(
			it->second->decayed()
		)
			unnamed_textures_.erase(
				it
			);
	}
}

sanguis::load::resource::textures::textures(
	sge::renderer::device_ptr const _renderer,
	sge::image2d::multi_loader &_image_loader
)
:
	texture_manager_(
		_renderer,
		boost::phoenix::construct<
			sge::texture::fragmented_unique_ptr
		>(
			boost::phoenix::new_<
				sge::texture::no_fragmented
			>(
				_renderer,
				sge::image::color::format::rgba8,
				filter
			)
		)
	),
	image_loader_(
		_mage_loader
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
			iti->path()
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
		== texture_names.end()
	)
		throw sanguis::exception(
			FCPPT_TEXT("no texture for id \"")
			+ id
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
			texture_manager_.renderer(),
			std::tr1::ref(
				image_loader_
			),
			filter
		);
}

sge::texture::part_ptr const
sanguis::load::resource::textures::do_load_inner(
	fcppt::filesystem::path const &_path
) const
{
	return
		sge::texture::add_image(
			texture_manageR_,
			image_loader_.load(
				_path
			)
		);
}
