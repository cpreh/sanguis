#ifndef SANGUIS_SERVER_AURA_OPTIONAL_GROUPS_HPP_INCLUDED
#define SANGUIS_SERVER_AURA_OPTIONAL_GROUPS_HPP_INCLUDED

#include "../collision/group_vector.hpp"
#include <sge/optional_fwd.hpp>

namespace sanguis
{
namespace server
{
namespace auras
{

typedef sge::optional<
	collision::group_vector
> optional_groups;

}
}
}

#endif
