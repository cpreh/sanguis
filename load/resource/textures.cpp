#include "textures.hpp"
#include "texture_context.hpp"
#include "texture_context_impl.hpp"
#include "map_get_or_create.hpp"
#include "../log.hpp"
#include "../../exception.hpp"
#include "../../media_path.hpp"
#include <sge/log/headers.hpp>
#include <sge/texture/add_image.hpp>
#include <sge/texture/default_creator_impl.hpp>
#include <sge/texture/no_fragmented.hpp>
#include <sge/texture/part_raw.hpp>
#include <sge/renderer/filter/linear.hpp>
#include <sge/renderer/resource_flags_none.hpp>
#include <sge/filesystem/directory_iterator.hpp>
#include <sge/filesystem/extension.hpp>
#include <sge/filesystem/is_regular.hpp>
#include <sge/image/loader.hpp>
#include <sge/image/create_texture.hpp>
#include <sge/text.hpp>
#include <sge/fstream.hpp>
#include <sge/string.hpp>
#include <sge/make_shared_ptr.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <tr1/functional>

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
	sge::filesystem::path const &path) const
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
	texture_identifier const &id) const
{
	if (texture_names.find(id) == texture_names.end())
		throw exception(
			SGE_TEXT("no texture for id \"")
			+ id
			+ SGE_TEXT("\" found"));
	return do_load_inner(
		sanguis::media_path()
		/ texture_names[id]);
}

sanguis::load::resource::texture_context_impl_ptr const
sanguis::load::resource::textures::do_load_unnamed(
	sge::filesystem::path const &path) const
{
	return 
		sge::make_shared_ptr<texture_context_impl>(
			path,
			texman.renderer(),
			il,
			filter);
}

sge::texture::part_ptr const
sanguis::load::resource::textures::do_load_inner(
	sge::filesystem::path const &p) const
{
	return sge::texture::add_image(
		texman,
		il->load(p)
	);
}

sanguis::load::resource::textures::textures(
	sge::renderer::device_ptr const rend,
	sge::image::loader_ptr const il)
:
	texman(
		rend,
		sge::texture::default_creator<
			sge::texture::no_fragmented
		>(
			rend,
			sge::image::color::format::rgba8,
			filter
		)
	),
	il(
		il)
{
	// look for .tex files
	for (sge::filesystem::directory_iterator i(sanguis::media_path()), end; i != end; ++i)
	{
		sge::filesystem::path const &p = i->path();
		if (!sge::filesystem::is_regular(p) || sge::filesystem::extension(p) != SGE_TEXT(".tex"))
			continue;
		
		// and parse line by line
		sge::ifstream file(p);
		if (!file.is_open())
			throw exception(
				SGE_TEXT("error opening id file \"")
				+ p.string()
				+ SGE_TEXT('"'));

		std::streamsize line_num(0);
		sge::string line;
		while (std::getline(file,line))
		{
			++line_num;

			boost::algorithm::trim(line);

			if (line.empty())
				continue;

			sge::string::size_type const equal
				= line.find(
					SGE_TEXT("="));

			if(equal == sge::string::npos)
			{
				SGE_LOG_WARNING(
					sanguis::load::log(),
					sge::log::_1
						<< SGE_TEXT("Error in .id file \")")
						<< p.string()
						<< SGE_TEXT("\" in line ")
						<< line_num
						<< SGE_TEXT('!'));
				continue;
			}
			texture_names[line.substr(0,equal)] = line.substr(equal+1);
		}
	}
}
