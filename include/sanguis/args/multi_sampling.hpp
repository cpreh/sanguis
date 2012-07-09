#ifndef SANGUIS_ARGS_MULTI_SAMPLING_HPP_INCLUDED
#define SANGUIS_ARGS_MULTI_SAMPLING_HPP_INCLUDED

#include <sge/renderer/multi_samples.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/program_options/variables_map.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace args
{

sge::renderer::multi_samples const
multi_sampling(
	boost::program_options::variables_map const &
);

}
}

#endif
