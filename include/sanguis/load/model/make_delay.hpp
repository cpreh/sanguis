#ifndef SANGUIS_LOAD_MODEL_MAKE_DELAY_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_MAKE_DELAY_HPP_INCLUDED

#include <sanguis/duration.hpp>
#include <sanguis/load/model/optional_delay_fwd.hpp>
#include <sge/parse/json/object_fwd.hpp>


namespace sanguis
{
namespace load
{
namespace model
{

sanguis::duration const
make_delay(
	sge::parse::json::object const &,
	sanguis::load::model::optional_delay const &
);

}
}
}

#endif
