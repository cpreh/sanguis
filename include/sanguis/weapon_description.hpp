#ifndef SANGUIS_WEAPON_DESCRIPTION_HPP_INCLUDED
#define SANGUIS_WEAPON_DESCRIPTION_HPP_INCLUDED

#include <sanguis/string_vector.hpp>
#include <sanguis/weapon_description_fwd.hpp>
#include <sanguis/weapon_type.hpp>


namespace sanguis
{

class weapon_description
{
public:
	weapon_description(
		sanguis::string_vector const &,
		sanguis::weapon_type const &
	);

	sanguis::string_vector const &
	text() const;

	sanguis::weapon_type const &
	weapon_type() const;
private:
	sanguis::string_vector text_;

	sanguis::weapon_type weapon_type_;
};

}

#endif
