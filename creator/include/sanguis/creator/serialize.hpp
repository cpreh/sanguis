#ifndef SANGUIS_CREATOR_SERIALIZE_HPP_INCLUDED
#define SANGUIS_CREATOR_SERIALIZE_HPP_INCLUDED

#include <sanguis/creator/result_fwd.hpp>
#include <sanguis/creator/symbol.hpp>
#include <fcppt/io/ostream.hpp>


namespace sanguis
{
namespace creator
{

SANGUIS_CREATOR_SYMBOL
void
serialize(
	fcppt::io::ostream &,
	sanguis::creator::result const &
);

}
}

#endif
