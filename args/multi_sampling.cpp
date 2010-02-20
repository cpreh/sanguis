#include "multi_sampling.hpp"

sge::renderer::multi_sample_type
sanguis::args::multi_sampling(
	boost::program_options::variables_map const &vm
)
{
	return
		vm["multisamples"].as<
			sge::renderer::multi_sample_type
		>();
}
