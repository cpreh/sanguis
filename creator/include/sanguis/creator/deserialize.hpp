#ifndef SANGUIS_CREATOR_DESERIALIZE_HPP_INCLUDED
#define SANGUIS_CREATOR_DESERIALIZE_HPP_INCLUDED

#include <sanguis/creator/symbol.hpp>
#include <sanguis/creator/top_result_fwd.hpp>
#include <fcppt/io/istream.hpp>


namespace sanguis
{
namespace creator
{

SANGUIS_CREATOR_SYMBOL
sanguis::creator::top_result
deserialize(
	fcppt::io::istream &
);

}
}

#endif
