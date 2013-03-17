#ifndef SANGUIS_PERK_TYPE_HPP_INCLUDED
#define SANGUIS_PERK_TYPE_HPP_INCLUDED

#include <sanguis/perk_type_fwd.hpp>


namespace sanguis
{

enum class perk_type
{
	choleric,
	health,
	ias,
	ims,
	irs,
	regeneration,
	fcppt_maximum = regeneration
};

}

#endif
