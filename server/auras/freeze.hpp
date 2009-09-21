#ifndef SANGUIS_SERVER_AURAS_FREEZE_HPP_INCLUDED
#define SANGUIS_SERVER_AURAS_FREEZE_HPP_INCLUDED

#include "aura.hpp"
#include <sge/collision/world_fwd.hpp>

namespace sanguis
{
namespace server
{
namespace auras
{

class freeze : public aura {
public:
	freeze(
		space_unit radius,
		team::type team
	);
private:
	void
	enter(
		entities::entity &target
	);

	void
	leave(
		entities::entity &target
	);
		
};

}
}
}

#endif
