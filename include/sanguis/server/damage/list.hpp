#ifndef SANGUIS_SERVER_DAMAGE_LIST_HPP_INCLUDED
#define SANGUIS_SERVER_DAMAGE_LIST_HPP_INCLUDED

#include <sanguis/server/damage/list_fwd.hpp>
#include <sanguis/server/damage/unit.hpp>
#include <sanguis/server/damage/array.hpp>
#include <sanguis/server/damage/meta_fwd.hpp>

namespace sanguis
{
namespace server
{
namespace damage
{

class list
{
public:
	explicit list(
		meta const &
	);

	explicit list(
		unit
	);

	list &
	operator()(
		meta const &
	);

	operator array() const;
private:
	array array_;
};

}
}
}

#endif
