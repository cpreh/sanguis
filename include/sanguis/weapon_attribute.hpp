#ifndef SANGUIS_WEAPON_ATTRIBUTE_HPP_INCLUDED
#define SANGUIS_WEAPON_ATTRIBUTE_HPP_INCLUDED

#include <sanguis/weapon_attribute_base.hpp>
#include <sanguis/weapon_attribute_extra.hpp>
#include <sanguis/weapon_attribute_fwd.hpp>
#include <sanguis/weapon_attribute_type.hpp>


namespace sanguis
{

class weapon_attribute
{
public:
	weapon_attribute(
		sanguis::weapon_attribute_type,
		sanguis::weapon_attribute_base,
		sanguis::weapon_attribute_extra
	);

	sanguis::weapon_attribute_type
	type() const;

	sanguis::weapon_attribute_base const
	base() const;

	sanguis::weapon_attribute_extra const
	extra() const;
private:
	sanguis::weapon_attribute_type type_;

	sanguis::weapon_attribute_base base_;

	sanguis::weapon_attribute_extra extra_;
};

}

#endif
