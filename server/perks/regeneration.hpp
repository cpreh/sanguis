#ifndef SANGUIS_SERVER_PERKS_REGENERATION_HPP_INCLUDED
#define SANGUIS_SERVER_PERKS_REGENERATION_HPP_INCLUDED

#include "perk.hpp"

namespace sanguis
{
namespace server
{
namespace perks
{

class regeneration : public perk {
public:
	regeneration();
private:
	void
	do_apply(
		entities::entity &,
		time_type,
		environment::object_ptr,
		environment::load_context_ptr
	);

	bool can_raise_level() const;
};

}
}
}

#endif
