#ifndef SANGUIS_CREATOR_AUX_GENERATOR_FUNCTION_HPP_INCLUDED
#define SANGUIS_CREATOR_AUX_GENERATOR_FUNCTION_HPP_INCLUDED

#include <sanguis/creator/aux/parameters_fwd.hpp>
#include <sanguis/creator/aux/result_fwd.hpp>


namespace sanguis
{
namespace creator
{
namespace aux
{

typedef
sanguis::creator::aux::result
(
	*generator_function
)(
	sanguis::creator::aux::parameters const &
);

}
}
}

#endif
