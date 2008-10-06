#include "environment.hpp"
#include "../log.hpp"
#include "../../media_path.hpp"
#include "../../exception.hpp"
#include <sge/fstream.hpp>
#include <sge/texture/util.hpp>
#include <sge/image/loader.hpp>
#include <sge/log/headers.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/algorithm/string/trim.hpp>

sge::texture::part_ptr const sanguis::load::resource::environment::do_load_texture(
	sanguis::load::resource::identifier_type const&id)
{
	if (texture_names.find(id) == texture_names.end())
		throw exception(SGE_TEXT("no texture for id \"")+id+SGE_TEXT("\" found"));
	return do_load_texture_inner(sanguis::media_path()/texture_names[id]);
}

void sanguis::load::resource::environment::load_textures()
{
	// look for .tex files
	for (boost::filesystem::basic_directory_iterator<sge::path> i(sanguis::media_path()),end; i != end; ++i)
	{
		const sge::path &p = i->path();
		if (!boost::filesystem::is_regular(p) || !boost::algorithm::ends_with(p.leaf(),SGE_TEXT(".tex")))
			continue;
		
		// and parse line by line
		sge::ifstream file(p);
		if (!file.is_open())
			throw exception(SGE_TEXT("error opening id file \"")+p.string()+SGE_TEXT("\""));

		std::streamsize line_num(0);
		sge::string line;
		while (std::getline(file,line))
		{
			++line_num;

			boost::algorithm::trim(line);

			if (line.empty())
				continue;

			const sge::string::size_type equal = line.find(SGE_TEXT("="));
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

sge::texture::part_ptr const sanguis::load::resource::environment::do_load_texture_inner(
	sge::path const &p)
{
	return sge::texture::add(texman,il->load(p));
}
