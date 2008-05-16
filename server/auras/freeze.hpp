#ifndef SANGUIS_SERVER_AURAS_FREEZE_HPP_INCLUDED
#define SANGUIS_SERVER_AURAS_FREEZE_HPP_INCLUDED

#include "aura.hpp"

namespace sanguis
{
namespace server
{
namespace auras
{

class freeze : public aura {
public:
	freeze(
		messages::circle_type const &,
		team::type team,
		influence::type);
private:
	void do_effect(
		entities::entity &target);
};

}
}
}

#endif
