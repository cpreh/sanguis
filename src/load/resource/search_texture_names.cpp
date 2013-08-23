#include <sanguis/exception.hpp>
#include <sanguis/media_path.hpp>
#include <sanguis/load/resource/search_texture_names.hpp>
#include <sanguis/load/resource/texture_identifier.hpp>
#include <sanguis/load/resource/texture_name_map.hpp>
#include <sanguis/load/log.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/filesystem/extension.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/io/ifstream.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <iosfwd>
#include <string>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::load::resource::texture_name_map
sanguis::load::resource::search_texture_names()
{
	sanguis::load::resource::texture_name_map names;

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

			names[
				sanguis::load::resource::texture_identifier(
					line.substr(
						0,
						equal
					)
				)
			] =
				line.substr(
					equal + 1
				);
		}
	}

	return
		std::move(
			names
		);
}
