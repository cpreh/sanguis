#include <sanguis/args/options.hpp>
#include <sanguis/net/port.hpp>
#include <sge/console/output_line_limit.hpp>
#include <sge/renderer/multi_sample_type.hpp>
#include <sge/renderer/no_multi_sampling.hpp>
#include <sge/renderer/screen_unit.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <fcppt/config/external_end.hpp>

boost::program_options::options_description const
sanguis::args::options()
{
	namespace po = boost::program_options;

	po::options_description desc("allowed options");

	desc.add_options()
		(
			"help",
			"produce help message"
		)
		(
			"history-size",
			po::value<
				sge::console::output_line_limit
			>()->default_value(
				static_cast<
					sge::console::output_line_limit
				>(8000)
			),
			"Size of the console output history"
		)
		(
			"log",
			po::value<
				std::string
			>()->default_value(
				std::string("warning")
			),
			"sets the maximum logging level (one of debug, info, warning, error, fatal in that order)"
		)
		(
			"width",
			po::value<
				sge::renderer::screen_unit
			>(),
			"sets the display width"
		)
		(
			"height",
			po::value<
				sge::renderer::screen_unit
			>(),
			"sets the display height"
		)
		(
			"fullscreen",
			po::value<
				bool
			>()->default_value(
				false
			),
			"start in fullscreen mode"
		)
		(
			"multisamples",
			po::value<
				sge::renderer::multi_sample_type
			>()->default_value(
				sge::renderer::no_multi_sampling
			),
			"sets the number of samples done for anti aliasing"
		)
		(
			"serveronly",
			po::value<
				bool
			>()->default_value(
				false
			),
			"only start a server"
		)
		(
			"serverport",
			po::value<
				net::port
			>()->default_value(
				31337
			),
			"the server port"
		);

	return desc;
}
