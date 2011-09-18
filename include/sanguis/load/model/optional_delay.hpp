#ifndef SANGUIS_LOAD_MODEL_OPTIONAL_DELAY_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_OPTIONAL_DELAY_HPP_INCLUDED

#include <sanguis/duration.hpp>
#include <fcppt/optional_fwd.hpp>

namespace sanguis
{
namespace load
{
namespace model
{

typedef fcppt::optional<
	sanguis::duration
> optional_delay;

}
}
}

#endif
