#include <sanguis/client/args/history_size.hpp>
#include <sge/console/gfx/output_line_limit.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/program_options/variables_map.hpp>
#include <fcppt/config/external_end.hpp>


sge::console::gfx::output_line_limit const
sanguis::client::args::history_size(
	boost::program_options::variables_map const &_variables_map
)
{
	return
		sge::console::gfx::output_line_limit(
			_variables_map[
				"history-size"
			].as<
				sge::console::gfx::output_line_limit::value_type
			>()
		);
}
