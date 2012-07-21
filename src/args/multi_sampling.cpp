#include <sanguis/args/multi_sampling.hpp>
#include <sge/renderer/pixel_format/multi_samples.hpp>
#include <sge/renderer/pixel_format/multi_samples_value.hpp>
#include <sge/renderer/pixel_format/optional_multi_samples.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/program_options/variables_map.hpp>
#include <fcppt/config/external_end.hpp>


sge::renderer::pixel_format::optional_multi_samples const
sanguis::args::multi_sampling(
	boost::program_options::variables_map const &_vm
)
{
	sge::renderer::pixel_format::multi_samples_value const value(
		_vm["multisamples"].as<
			sge::renderer::pixel_format::multi_samples_value
		>()
	);

	return
		value == 0u
		?
			sge::renderer::pixel_format::optional_multi_samples()
		:
			sge::renderer::pixel_format::optional_multi_samples(
				sge::renderer::pixel_format::multi_samples(
					value
				)
			)
		;
}
