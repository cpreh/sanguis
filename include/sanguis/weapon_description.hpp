#ifndef SANGUIS_WEAPON_DESCRIPTION_HPP_INCLUDED
#define SANGUIS_WEAPON_DESCRIPTION_HPP_INCLUDED

#include <sanguis/string_vector.hpp>
#include <sanguis/weapon_description_fwd.hpp>


namespace sanguis
{

class weapon_description
{
public:
	explicit
	weapon_description(
		sanguis::string_vector const &
	);

	sanguis::string_vector const &
	text() const;
private:
	sanguis::string_vector text_;
};

}

#endif
