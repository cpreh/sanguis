#ifndef SANGUIS_SERVER_ENTITIES_AURAS_FREEZE_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_AURAS_FREEZE_HPP_INCLUDED

#include "aura.hpp"

namespace sanguis
{
namespace server
{
namespace entities
{
namespace auras
{

class freeze : public aura {
public:
	freeze(
		environment const &,
		messages::pos_type const &pos,
		messages::space_unit radius,
		team::type team);
private:
	void do_effect(entity &target);
};

}
}
}
}

#endif
