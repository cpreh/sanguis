#ifndef SANGUIS_CLIENT_ARGS_MULTI_SAMPLING_HPP_INCLUDED
#define SANGUIS_CLIENT_ARGS_MULTI_SAMPLING_HPP_INCLUDED

#include <sge/renderer/pixel_format/optional_multi_samples_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/program_options/variables_map.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace client
{
namespace args
{

sge::renderer::pixel_format::optional_multi_samples
multi_sampling(
	boost::program_options::variables_map const &
);

}
}
}

#endif
