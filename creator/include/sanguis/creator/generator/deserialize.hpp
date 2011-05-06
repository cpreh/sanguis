#ifndef SANGUIS_CREATOR_GENERATOR_DESERIALIZE_HPP_INCLUDED
#define SANGUIS_CREATOR_GENERATOR_DESERIALIZE_HPP_INCLUDED

#include <sanguis/creator/generator/result_fwd.hpp>
#include <sanguis/creator/symbol.hpp>
#include <fcppt/io/istream.hpp>

namespace sanguis
{
namespace creator
{
namespace generator
{

SANGUIS_CREATOR_SYMBOL
generator::result const
deserialize(
	fcppt::io::istream &
);

}
}
}

#endif
