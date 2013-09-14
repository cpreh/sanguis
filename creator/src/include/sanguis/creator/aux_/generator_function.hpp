#ifndef SANGUIS_CREATOR_AUX__GENERATOR_FUNCTION_HPP_INCLUDED
#define SANGUIS_CREATOR_AUX__GENERATOR_FUNCTION_HPP_INCLUDED

#include <sanguis/creator/aux_/parameters_fwd.hpp>
#include <sanguis/creator/aux_/result_fwd.hpp>


namespace sanguis
{
namespace creator
{
namespace aux_
{

typedef
sanguis::creator::aux_::result
(
	*generator_function
)(
	sanguis::creator::aux_::parameters const &
);

}
}
}

#endif
