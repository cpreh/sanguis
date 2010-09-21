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
#include <sge/image/multi_loader.hpp>
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
	texture_identifier const &id) const
{
	return map_get_or_create(
		textures_,
		id, 
		std::tr1::bind(
			&textures::do_load,
			this,
			std::tr1::placeholders::_1
		)
	);
}

sanguis::load::resource::texture_context const
sanguis::load::resource::textures::load(
	fcppt::filesystem::path const &path) const
{
	return 
		texture_context(
			map_get_or_create(
				unnamed_textures,
				path,
				std::tr1::bind(
					&textures::do_load_unnamed,
					this,
					std::tr1::placeholders::_1
				)
			)
		);
}

void sanguis::load::resource::textures::cleanup(
	time_type const delta) const
{
	for(
		unnamed_texture_map::iterator it(unnamed_textures.begin()), next(it); 
		it != unnamed_textures.end(); 
		it = next) 
	{ 
		++next; 
		it->second->tick(
			delta);
		if (it->second->decayed())
			unnamed_textures.erase(
				it);
	}
}

sanguis::load::resource::textures::~textures()
{}

sge::texture::part_ptr const
sanguis::load::resource::textures::do_load(
	texture_identifier const &id
) const
{
	if(
		texture_names.find(id) == texture_names.end()
	)
		throw exception(
			FCPPT_TEXT("no texture for id \"")
			+ id
			+ FCPPT_TEXT("\" found")
		);

	return do_load_inner(
		sanguis::media_path()
		/ texture_names[id]
	);
}

sanguis::load::resource::texture_context_impl_ptr const
sanguis::load::resource::textures::do_load_unnamed(
	fcppt::filesystem::path const &path
) const
{
	return 
		fcppt::make_shared_ptr<
			texture_context_impl
		>(
			path,
			texman.renderer(),
			std::tr1::ref(
				il
			),
			filter
		);
}

sge::texture::part_ptr const
sanguis::load::resource::textures::do_load_inner(
	fcppt::filesystem::path const &p
) const
{
	return sge::texture::add_image(
		texman,
		il.load(p)
	);
}

sanguis::load::resource::textures::textures(
	sge::renderer::device_ptr const _rend,
	sge::image::multi_loader &_il
)
:
	texman(
		_rend,
		boost::phoenix::construct<
			sge::texture::fragmented_unique_ptr
		>(
			boost::phoenix::new_<
				sge::texture::no_fragmented
			>(
				_rend,
				sge::image::color::format::rgba8,
				filter
			)
		)
	),
	il(
		_il
	)
{
	// look for .tex files
	for (fcppt::filesystem::directory_iterator i(sanguis::media_path()), end; i != end; ++i)
	{
		fcppt::filesystem::path const &p = i->path();
		if (!fcppt::filesystem::is_regular(p) || fcppt::filesystem::extension(p) != FCPPT_TEXT(".tex"))
			continue;
		
		// and parse line by line
		fcppt::io::ifstream file(p);
		if (!file.is_open())
			throw exception(
				FCPPT_TEXT("error opening id file \"")
				+ fcppt::filesystem::path_to_string(
					p
				)
				+ FCPPT_TEXT('"'));

		std::streamsize line_num(0);
		fcppt::string line;
		while (std::getline(file,line))
		{
			++line_num;

			boost::algorithm::trim(line);

			if (line.empty())
				continue;

			fcppt::string::size_type const equal
				= line.find(
					FCPPT_TEXT("="));

			if(equal == fcppt::string::npos)
			{
				FCPPT_LOG_WARNING(
					sanguis::load::log(),
					fcppt::log::_
						<< FCPPT_TEXT("Error in .id file \")")
						<< fcppt::filesystem::path_to_string(
							p
						)
						<< FCPPT_TEXT("\" in line ")
						<< line_num
						<< FCPPT_TEXT('!'));
				continue;
			}
			texture_names[line.substr(0,equal)] = line.substr(equal+1);
		}
	}
}
