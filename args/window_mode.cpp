#include "window_mode.hpp"

sge::renderer::window_mode::type
sanguis::args::window_mode(
	boost::program_options::variables_map const &vm
)
{
	return
		vm["fullscreen"].as<
			bool
		>()
		?
			sge::renderer::window_mode::fullscreen
		:
			sge::renderer::window_mode::windowed;
}
