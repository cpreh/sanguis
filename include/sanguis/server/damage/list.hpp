#ifndef SANGUIS_SERVER_DAMAGE_LIST_HPP_INCLUDED
#define SANGUIS_SERVER_DAMAGE_LIST_HPP_INCLUDED

#include <sanguis/server/damage/array.hpp>
#include <sanguis/server/damage/list_fwd.hpp>
#include <sanguis/server/damage/meta_fwd.hpp>
#include <sanguis/server/damage/unit.hpp>


namespace sanguis
{
namespace server
{
namespace damage
{

class list
{
public:
	explicit
	list(
		sanguis::server::damage::meta const &
	);

	explicit
	list(
		sanguis::server::damage::unit
	);

	sanguis::server::damage::list &
	operator()(
		sanguis::server::damage::meta const &
	);

	operator sanguis::server::damage::array() const;
private:
	sanguis::server::damage::array array_;
};

}
}
}

#endif
