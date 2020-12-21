#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_IFACES_WITH_WEAPON_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_IFACES_WITH_WEAPON_HPP_INCLUDED

#include <sanguis/optional_primary_weapon_type_fwd.hpp>
#include <sanguis/weapon_status_fwd.hpp>
#include <fcppt/nonmovable.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace entities
{
namespace ifaces
{

class with_weapon
{
	FCPPT_NONMOVABLE(
		with_weapon
	);
protected:
	with_weapon();

	virtual
	~with_weapon();
public:
	virtual
	void
	weapon(
		sanguis::optional_primary_weapon_type
	) = 0;

	virtual
	void
	weapon_status(
		sanguis::weapon_status
	) = 0;
};

}
}
}
}
}

#endif
