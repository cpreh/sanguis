#include <sanguis/args/multi_sampling.hpp>
#include <sge/renderer/multi_samples.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/program_options/variables_map.hpp>
#include <fcppt/config/external_end.hpp>


sge::renderer::multi_samples const
sanguis::args::multi_sampling(
	boost::program_options::variables_map const &_vm
)
{
	return
		sge::renderer::multi_samples(
			_vm["multisamples"].as<
				sge::renderer::multi_samples::value_type
			>()
		);
}
