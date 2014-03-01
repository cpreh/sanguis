#include <sanguis/args/options.hpp>
#include <sge/console/output_line_limit.hpp>
#include <sge/renderer/pixel_format/multi_samples_value.hpp>
#include <sge/renderer/screen_unit.hpp>
#include <alda/net/port.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/program_options/options_description.hpp>
#include <string>
#include <fcppt/config/external_end.hpp>


boost::program_options::options_description const
sanguis::args::options()
{
	namespace po = boost::program_options;

	po::options_description desc(
		"allowed options"
	);

	std::string const log_description(
		"(one of verbose, debug, info, warning, error, fatal (in that order))"
	);

	desc.add_options()
		(
			"help",
			"produce help message"
		)
		(
			"history-size",
			po::value<
				sge::console::output_line_limit::value_type
			>()->default_value(
				fcppt::literal<
					sge::console::output_line_limit::value_type
				>(
					1000
				)
			),
			"Size of the console output history"
		)
		(
			"log",
			po::value<
				std::string
			>()->default_value(
				std::string("info")
			),
			(
				"sets the maximum logging level "
				+
				log_description
			).c_str()
		)
		(
			"sge-log",
			po::value<
				std::string
			>()->default_value(
				std::string("warning")
			),
			(
				"sets the maximum logging level for SGE "
				+
				log_description
			).c_str()
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
				sge::renderer::pixel_format::multi_samples_value
			>()->default_value(
				0u
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
				alda::net::port::value_type
			>()->default_value(
				31337
			),
			"the server port"
		);

	return desc;
}
