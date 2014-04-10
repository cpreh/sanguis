#include <sanguis/client/args/sge_log_level.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/log/level.hpp>
#include <fcppt/log/level_from_string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/program_options/variables_map.hpp>
#include <string>
#include <fcppt/config/external_end.hpp>


fcppt::log::level
sanguis::client::args::sge_log_level(
	boost::program_options::variables_map const &_vm
)
{
	return
		fcppt::log::level_from_string(
			fcppt::from_std_string(
				_vm["sge-log"].as<
					std::string
				>()
			)
		);
}
