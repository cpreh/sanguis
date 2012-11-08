#ifndef SANGUIS_CREATOR_GENERATOR_RAND_VALUE_HPP_INCLUDED
#define SANGUIS_CREATOR_GENERATOR_RAND_VALUE_HPP_INCLUDED

#include <fcppt/strong_typedef.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/cstdint.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace creator
{
namespace generator
{

FCPPT_MAKE_STRONG_TYPEDEF(
	boost::uint32_t,
	rand_value
);

}
}
}

#endif