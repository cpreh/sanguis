#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_WITH_WEAPON_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_WITH_WEAPON_HPP_INCLUDED

#include "../../../weapon_type.hpp"
#include <fcppt/noncopyable.hpp>

namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace entities
{

class with_weapon
{
	FCPPT_NONCOPYABLE(
		with_weapon
	);
protected:
	with_weapon();

	virtual ~with_weapon();
public:
	virtual void
	weapon(
		weapon_type::type
	) = 0;

	virtual void
	attacking(
		bool
	) = 0;

	virtual void
	reloading(
		bool
	) = 0;
};

}
}
}
}

#endif
