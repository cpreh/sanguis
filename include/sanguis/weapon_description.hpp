#ifndef SANGUIS_WEAPON_DESCRIPTION_HPP_INCLUDED
#define SANGUIS_WEAPON_DESCRIPTION_HPP_INCLUDED

#include <sanguis/magazine_extra.hpp>
#include <sanguis/magazine_remaining.hpp>
#include <sanguis/magazine_size.hpp>
#include <sanguis/weapon_attribute_vector.hpp>
#include <sanguis/weapon_description_fwd.hpp>
#include <sanguis/weapon_type.hpp>


namespace sanguis
{

class weapon_description
{
public:
	weapon_description(
		sanguis::weapon_type const &,
		sanguis::magazine_size,
		sanguis::magazine_extra,
		sanguis::magazine_remaining,
		sanguis::weapon_attribute_vector const &
	);

	sanguis::weapon_type const &
	weapon_type() const;

	sanguis::magazine_size const
	magazine_size() const;

	sanguis::magazine_extra const
	magazine_extra() const;

	sanguis::magazine_remaining const
	magazine_remaining() const;

	sanguis::weapon_attribute_vector const &
	attributes() const;
private:
	sanguis::weapon_type weapon_type_;

	sanguis::magazine_size magazine_size_;

	sanguis::magazine_extra magazine_extra_;

	sanguis::magazine_remaining magazine_remaining_;

	sanguis::weapon_attribute_vector attributes_;
};

}

#endif
