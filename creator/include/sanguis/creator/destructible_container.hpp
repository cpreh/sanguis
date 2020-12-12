#ifndef SANGUIS_CREATOR_DESTRUCTIBLE_CONTAINER_HPP_INCLUDED
#define SANGUIS_CREATOR_DESTRUCTIBLE_CONTAINER_HPP_INCLUDED

#include <sanguis/creator/destructible.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace creator
{

using
destructible_container
=
std::vector<
	sanguis::creator::destructible
>;

}
}

#endif
