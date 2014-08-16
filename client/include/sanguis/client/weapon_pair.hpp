#ifndef SANGUIS_CLIENT_WEAPON_PAIR_HPP_INCLUDED
#define SANGUIS_CLIENT_WEAPON_PAIR_HPP_INCLUDED

#include <sanguis/is_primary_weapon_fwd.hpp>
#include <sanguis/optional_weapon_description.hpp>
#include <sanguis/weapon_description_fwd.hpp>
#include <sanguis/client/weapon_pair_fwd.hpp>


namespace sanguis
{
namespace client
{

class weapon_pair
{
public:
	weapon_pair();

	void
	add(
		sanguis::weapon_description const &
	);

	void
	remove(
		sanguis::is_primary_weapon
	);

	sanguis::optional_weapon_description const &
	compare(
		sanguis::is_primary_weapon
	) const;
private:
	sanguis::optional_weapon_description primary_;

	sanguis::optional_weapon_description secondary_;
};

}
}

#endif
