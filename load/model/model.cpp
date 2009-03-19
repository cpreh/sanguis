#include "model.hpp"
#include "split_first_slash.hpp"
#include "get_entry.hpp"
#include "../../exception.hpp"
#include "../resource/context.hpp"
#include "../resource/textures.hpp"
#include "../log.hpp"
#include <sge/filesystem/directory_iterator.hpp>
#include <sge/filesystem/is_directory.hpp>
#include <sge/filesystem/stem.hpp>
#include <sge/filesystem/extension.hpp>
#include <sge/math/dim/basic_impl.hpp>
#include <sge/log/headers.hpp>
#include <sge/parse/ini/parse.hpp>
#include <sge/fstream.hpp>
#include <sge/text.hpp>
#include <boost/foreach.hpp>
#include <utility>
#include <functional>
#include <algorithm>
#include <string>

// TODO: split this stuff!

namespace
{

sge::string const header_name(
	SGE_TEXT("header")
);

bool header_equal(
	sge::parse::ini::section const &seq)
{
	SGE_LOG_DEBUG(
		sanguis::load::log(),
		sge::log::_1
			<< seq.header
	);
	return seq.header == header_name;
}

// FIXME: make this work with wide strings, too!
typedef sge::ifstream ifstream;

typedef std::basic_string<
	ifstream::char_type
> string;

sge::parse::ini::grammar<
	string::const_iterator
> parser;

string const
read_file(
	ifstream &ifs)
{
	string ret;

	string::value_type ch;
	while(ifs.get(ch))
		ret.push_back(ch);
	return ret;
}

sge::renderer::dim_type const
load_dim(
	sge::filesystem::path const &path)
{
	sge::filesystem::path const ini_file(
		path / SGE_TEXT("global.ini")
	);

	ifstream ifs(
		ini_file,
		std::ios_base::binary
	);

	if(!ifs.is_open())
		throw sanguis::exception(
			SGE_TEXT("Failed to open ini file: ")
			+ ini_file.string()
		);

	string const ret(
		read_file(
			ifs
		)
	);

	string::const_iterator beg(
		ret.begin()
	);

	sge::parse::ini::section_vector sections;

	if(
		!sge::parse::ini::parse(
			beg,
			ret.end(),	
			sections
		)
	)
	{
		SGE_LOG_WARNING(
			sanguis::load::log(),
			sge::log::_1
				<< ini_file.string()
				<< SGE_TEXT(" contains errors!")
			);
	}
	
	sge::parse::ini::section_vector::const_iterator const header_it(
		std::find_if(
			sections.begin(),
			sections.end(),
			std::ptr_fun(
				header_equal
			)
		)
	);

	if(header_it == sections.end())
		throw sanguis::exception(
			SGE_TEXT("header subsection not found in ")
			+ ini_file.string()
		);

	sge::parse::ini::section const header(
		*header_it
	);

	BOOST_FOREACH(
		sge::parse::ini::entry_vector::const_reference r,
		header.entries
	)
		SGE_LOG_DEBUG(
			sanguis::load::log(),
			sge::log::_1
				<< r.name
		);


	try
	{
		return sge::renderer::dim_type(
			static_cast<sge::renderer::size_type>(
				sanguis::load::model::get_entry<int>(
					header.entries,
					SGE_TEXT("cell_width")
				)
			),
			static_cast<sge::renderer::size_type>(
				sanguis::load::model::get_entry<int>(
					header.entries,
					SGE_TEXT("cell_height")
				)
			)
		);
	}
	catch(sanguis::exception const &e)
	{
		SGE_LOG_ERROR(
			sanguis::load::log(),
			sge::log::_1
				<< SGE_TEXT("In ")
				<< path
				<< SGE_TEXT(": ")
				<< e.what()
		);
		throw;
	}
}

}

sanguis::load::model::model::model(
	sge::filesystem::path const &path,
	resource::context const &ctx)
:
	path(path),
	parts()
{
	sge::renderer::dim_type const cell_size(
		load_dim(
			path
		)
	);

	for(sge::filesystem::directory_iterator beg(path), end; beg != end; ++beg)
	{
		sge::filesystem::path const &file(
			beg->path()
		);

		if(sge::filesystem::is_directory(*beg))
		{
			SGE_LOG_WARNING(
				log(),
				sge::log::_1
					<< file.string()
					<< SGE_TEXT(" is a directory!"));
			continue;
		}
		
		if(sge::filesystem::extension(file) == SGE_TEXT(".ini"))
			continue;

		sge::texture::part_ptr const tex(
			ctx.textures().load(
				file
			)
		);


		sge::filesystem::path const ini_file(
			path / (sge::filesystem::stem(file) + SGE_TEXT(".ini"))
		);

		ifstream ifs(
			ini_file,
			std::ios_base::binary
		);

		if(!ifs.is_open())
		{
			SGE_LOG_WARNING(
				log(),
				sge::log::_1
					<< SGE_TEXT("Failed to open ini file: ")
					<< ini_file.string()
			);

			continue;
		}

		string const ret(
			read_file(
				ifs
			)
		);

		string::const_iterator beg(
			ret.begin()
		);

		sge::parse::ini::section_vector sections;

		if(
			!sge::parse::ini::parse(
				beg,
				ret.end(),
				sections
			)
		)
		{
			SGE_LOG_WARNING(
				log(),
				sge::log::_1
					<< ini_file.string()
					<< SGE_TEXT(" contains errors!")
				);
		}

		BOOST_FOREACH(
			sge::parse::ini::section_vector::const_reference section,
			sections
		)
		{	
			split_pair const names(
				split_first_slash(
					section.header
				)
			);

			part_map::iterator it(
				parts.find(
					names.first
				)
			);

			SGE_LOG_DEBUG(
				log(),
				sge::log::_1
					<< SGE_TEXT("Adding category ")
					<< names.first
					<< SGE_TEXT(" in ")
					<< path
					<< SGE_TEXT(". Rest: ")
					<< names.second
			);

			if(it == parts.end())
			{
				std::pair<part_map::iterator, bool> const ret(
					parts.insert(
						std::make_pair(
							names.first,	
							part(
								tex,
								cell_size
							)
						)
					)
				);
				
				it = ret.first;
			}

			it->second.add(
				section.entries,
				names.second
			);
		}
	}
}

sanguis::load::model::part const &
sanguis::load::model::model::operator[](
	sge::string const &name) const
{
	part_map::const_iterator const it(
		parts.find(
			name
		)
	);

	if(it == parts.end())
		throw exception(
			SGE_TEXT("Category \"")
			+ name
			+ SGE_TEXT("\" not found in ")
			+ path.string()
		);
	
	return it->second;
}

sanguis::load::model::model::const_iterator
sanguis::load::model::model::begin() const
{
	return parts.begin();
}

sanguis::load::model::model::const_iterator
sanguis::load::model::model::end() const
{
	return parts.end();
} 
sanguis::load::model::model::size_type
sanguis::load::model::model::size() const
{
	return parts.size();
}
