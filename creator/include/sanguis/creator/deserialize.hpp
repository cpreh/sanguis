#ifndef SANGUIS_CREATOR_DESERIALIZE_HPP_INCLUDED
#define SANGUIS_CREATOR_DESERIALIZE_HPP_INCLUDED

#include <sanguis/creator/result_fwd.hpp>
#include <sanguis/creator/symbol.hpp>
#include <fcppt/io/istream.hpp>


namespace sanguis
{
namespace creator
{

SANGUIS_CREATOR_SYMBOL
sanguis::creator::result const
deserialize(
	fcppt::io::istream &
);

}
}

#endif
