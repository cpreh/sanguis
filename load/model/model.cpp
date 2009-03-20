#include "model.hpp"
#include "split_first_slash.hpp"
#include "get_entry.hpp"
#include "optional_delay.hpp"
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
#include <sge/parse/ini/parse_file.hpp>
#include <sge/parse/ini/section.hpp>
#include <sge/parse/ini/section_vector.hpp>
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

sge::renderer::dim_type const
load_dim(
	sge::parse::ini::entry_vector const &entries)
{
	return sge::renderer::dim_type(
		static_cast<sge::renderer::size_type>(
			sanguis::load::model::get_entry<int>(
				entries,
				SGE_TEXT("cell_width")
			)
		),
		static_cast<sge::renderer::size_type>(
			sanguis::load::model::get_entry<int>(
				entries,
				SGE_TEXT("cell_height")
			)
		)
	);
}

sanguis::load::model::optional_delay const
load_delay(
	sge::parse::ini::entry_vector const &entries)
{
	try
	{
		return sanguis::load::model::get_entry<int>(
			entries,
			SGE_TEXT("delay")
		);
	}
	catch(sanguis::exception const &e)
	{
		return sanguis::load::model::optional_delay();
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
	sge::filesystem::path const global_ini(
		path / SGE_TEXT("global.ini")
	);

	sge::parse::ini::section_vector global_entries;
	
	if(
		!sge::parse::ini::parse_file(
			global_ini,
			global_entries
		)
	)
	{
		SGE_LOG_WARNING(
			sanguis::load::log(),
			sge::log::_1
				<< global_ini
				<< SGE_TEXT(" contains errors!")
			);
	}

	sge::parse::ini::section_vector::const_iterator const header_it(
		std::find_if(
			global_entries.begin(),
			global_entries.end(),
			std::ptr_fun(
				header_equal
			)
		)
	);

	if(header_it == global_entries.end())
		throw sanguis::exception(
			SGE_TEXT("header subsection not found in ")
			+ global_ini.string()
		);

	sge::parse::ini::section const header(
		*header_it
	);

	sge::renderer::dim_type const cell_size(
		load_dim(
			header.entries
		)
	);

	optional_delay const opt_delay(
		load_delay(
			header.entries
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

		sge::parse::ini::section_vector sections;
		
		if(
			!sge::parse::ini::parse_file(
				ini_file,
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
								global_parameters(
									cell_size,
									opt_delay
								)
							)
						)
					)
				);
				
				it = ret.first;
			}

			it->second.add(
				section.entries,
				names.second,
				tex
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
