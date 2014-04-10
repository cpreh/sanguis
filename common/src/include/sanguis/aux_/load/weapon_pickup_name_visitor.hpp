#ifndef SANGUIS_AUX__LOAD_WEAPON_PICKUP_NAME_VISITOR_HPP_INCLUDED
#define SANGUIS_AUX__LOAD_WEAPON_PICKUP_NAME_VISITOR_HPP_INCLUDED

#include <sanguis/primary_weapon_type_fwd.hpp>
#include <sanguis/secondary_weapon_type_fwd.hpp>
#include <fcppt/string.hpp>


namespace sanguis
{
namespace aux_
{
namespace load
{

struct weapon_pickup_name_visitor
{
	typedef
	fcppt::string
	result_type;

	result_type
	operator()(
		sanguis::primary_weapon_type
	) const;

	result_type
	operator()(
		sanguis::secondary_weapon_type
	) const;
};

}
}
}

#endif
