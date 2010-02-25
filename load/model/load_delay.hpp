#ifndef SANGUIS_LOAD_MODEL_LOAD_DELAY_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_LOAD_DELAY_HPP_INCLUDED

#include "optional_delay.hpp"
#include <sge/parse/json/member_vector.hpp>

namespace sanguis
{
namespace load
{
namespace model
{

optional_delay const
load_delay(
	sge::parse::json::member_vector const &
);

}
}
}

#endif
