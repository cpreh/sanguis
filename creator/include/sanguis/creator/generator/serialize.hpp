#ifndef SANGUIS_CREATOR_GENERATOR_SERIALIZE_HPP_INCLUDED
#define SANGUIS_CREATOR_GENERATOR_SERIALIZE_HPP_INCLUDED

#include <sanguis/creator/symbol.hpp>
#include <sanguis/creator/generator/result_fwd.hpp>
#include <fcppt/io/ostream.hpp>


namespace sanguis
{
namespace creator
{
namespace generator
{

SANGUIS_CREATOR_SYMBOL
void
serialize(
	fcppt::io::ostream &,
	sanguis::creator::generator::result const &
);

}
}
}

#endif
