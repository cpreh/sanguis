#ifndef SANGUIS_LOAD_MODEL_LOAD_DELAY_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_LOAD_DELAY_HPP_INCLUDED

#include <sanguis/load/model/optional_delay.hpp>
#include <sge/parse/json/object_fwd.hpp>


namespace sanguis
{
namespace load
{
namespace model
{

sanguis::load::model::optional_delay const
load_delay(
	sge::parse::json::object const &
);

}
}
}

#endif
