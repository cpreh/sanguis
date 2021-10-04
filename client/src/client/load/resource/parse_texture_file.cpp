#include <sanguis/exception.hpp>
#include <sanguis/client/load/resource/parse_texture_file.hpp>
#include <sanguis/client/load/resource/texture_identifier.hpp>
#include <sanguis/client/load/resource/texture_name_map.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/filesystem/ifstream.hpp>
#include <fcppt/filesystem/open_exn.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/log/out.hpp>
#include <fcppt/log/warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <filesystem>
#include <ios>
#include <string>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::client::load::resource::texture_name_map
sanguis::client::load::resource::parse_texture_file(
	fcppt::log::object &_log,
	std::filesystem::path const &_path,
	sanguis::client::load::resource::texture_name_map &&_result
)
{
	// TODO(philipp): Write a proper parser for this
	auto file(
		fcppt::filesystem::open_exn<
			fcppt::filesystem::ifstream,
			sanguis::exception
		>(
			_path,
			std::ios_base::openmode{}
		)
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
		{
			continue;
		}

		fcppt::string::size_type const equal(
			line.find(
				'='
			)
		);

		if(
			equal == fcppt::string::npos
		)
		{
			FCPPT_LOG_WARNING(
				_log,
				fcppt::log::out
					<< FCPPT_TEXT("Error in .id file \")")
					<< fcppt::filesystem::path_to_string(
						_path
					)
					<< FCPPT_TEXT("\" in line ")
					<< line_num
					<< FCPPT_TEXT('!')
			)

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
			std::filesystem::path{
				line.substr(
					equal + 1
				)
			};
	}

	return
		std::move(
			_result
		);
}
