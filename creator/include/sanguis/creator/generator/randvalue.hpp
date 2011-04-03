#ifndef SANGUIS_CREATOR_GENERATOR_RANDVALUE_HPP_INCLUDED
#define SANGUIS_CREATOR_GENERATOR_RANDVALUE_HPP_INCLUDED

#include <fcppt/strong_typedef.hpp>
#include <boost/cstdint.hpp>

namespace sanguis
{
namespace creator
{
namespace generator
{

FCPPT_MAKE_STRONG_TYPEDEF(
	boost::uint32_t,
	randvalue
);

}
}
}

#endif