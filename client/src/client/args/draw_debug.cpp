#include <sanguis/client/args/draw_debug.hpp>
#include <sanguis/client/draw/debug.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/program_options/variables_map.hpp>
#include <fcppt/config/external_end.hpp>


sanguis::client::draw::debug
sanguis::client::args::draw_debug(
	boost::program_options::variables_map const &_vm
)
{
	return
		sanguis::client::draw::debug{
			_vm["draw-debug"].as<
				bool
			>()
		};
}
