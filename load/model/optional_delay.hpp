#ifndef SANGUIS_LOAD_MODEL_OPTIONAL_DELAY_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_OPTIONAL_DELAY_HPP_INCLUDED

#include <sge/time/unit.hpp>
#include <boost/optional.hpp>

namespace sanguis
{
namespace load
{
namespace model
{

typedef boost::optional<
	sge::time::unit
> optional_delay;

}
}
}

#endif
