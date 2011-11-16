#ifndef SANGUIS_LOAD_MODEL_LOAD_DELAY_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_LOAD_DELAY_HPP_INCLUDED

#include <sanguis/load/model/optional_delay.hpp>
#include <sge/parse/json/member_map.hpp>

namespace sanguis
{
namespace load
{
namespace model
{

model::optional_delay const
load_delay(
	sge::parse::json::member_map const &
);

}
}
}

#endif
