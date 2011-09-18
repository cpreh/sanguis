#include <sanguis/args/multi_sampling.hpp>
#include <sge/renderer/multi_sample_type.hpp>

sge::renderer::multi_sample_type
sanguis::args::multi_sampling(
	boost::program_options::variables_map const &_vm
)
{
	return
		_vm["multisamples"].as<
			sge::renderer::multi_sample_type
		>();
}
