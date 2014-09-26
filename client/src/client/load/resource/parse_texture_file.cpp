#include <sanguis/exception.hpp>
#include <sanguis/client/load/log.hpp>
#include <sanguis/client/load/resource/parse_texture_file.hpp>
#include <sanguis/client/load/resource/texture_identifier.hpp>
#include <sanguis/client/load/resource/texture_name_map.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/io/ifstream.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/filesystem/path.hpp>
#include <iosfwd>
#include <string>
#include <fcppt/config/external_end.hpp>


sanguis::client::load::resource::texture_name_map
sanguis::client::load::resource::parse_texture_file(
	boost::filesystem::path const &_path,
	sanguis::client::load::resource::texture_name_map &&_result
)
{
	// TODO: Write a proper parser for this
	fcppt::io::ifstream file(
		_path
	);

	if(
		!file.is_open()
	)
		throw sanguis::exception(
			FCPPT_TEXT("error opening id file \"")
			+ fcppt::filesystem::path_to_string(
				_path
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
				sanguis::client::load::log(),
				fcppt::log::_
					<< FCPPT_TEXT("Error in .id file \")")
					<< fcppt::filesystem::path_to_string(
						_path
					)
					<< FCPPT_TEXT("\" in line ")
					<< line_num
					<< FCPPT_TEXT('!'));
			continue;
		}

		_result[
			sanguis::client::load::resource::texture_identifier(
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

	return
		_result;
}
