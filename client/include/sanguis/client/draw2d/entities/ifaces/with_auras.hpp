#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_IFACES_WITH_AURAS_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_IFACES_WITH_AURAS_HPP_INCLUDED

#include <sanguis/aura_type_fwd.hpp>
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

class with_auras
{
	FCPPT_NONMOVABLE(
		with_auras
	);
protected:
	with_auras();

	virtual
	~with_auras();
public:
	virtual
	void
	add_aura(
		sanguis::aura_type
	) = 0;
};

}
}
}
}
}

#endif
