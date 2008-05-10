#ifndef SANGUIS_SERVER_PERKS_IMS_HPP_INCLUDED
#define SANGUIS_SERVER_PERKS_IMS_HPP_INCLUDED

#include "perk.hpp"
#include "../../messages/types.hpp"

namespace sanguis
{
namespace server
{
namespace perks
{

class ims : public perk {
private:
	void do_apply(entities::entity &);
	bool can_raise_level() const;
	messages::space_unit factor() const;
};

}
}
}

#endif
