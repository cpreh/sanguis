#ifndef SANGUIS_ARGS_MULTI_SAMPLING_HPP_INCLUDED
#define SANGUIS_ARGS_MULTI_SAMPLING_HPP_INCLUDED

#include <sge/renderer/multi_sample_type.hpp>
#include <boost/program_options/variables_map.hpp>

namespace sanguis
{
namespace args
{

sge::renderer::multi_sample_type
multi_sampling(
	boost::program_options::variables_map const &
);

}
}

#endif
