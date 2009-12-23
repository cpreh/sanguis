#ifndef SANGUIS_LOAD_MODEL_OPTIONAL_DELAY_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_OPTIONAL_DELAY_HPP_INCLUDED

#include <sge/time/unit.hpp>
#include <fcppt/optional_fwd.hpp>

namespace sanguis
{
namespace load
{
namespace model
{

typedef fcppt::optional<
	sge::time::unit
> optional_delay;

}
}
}

#endif
