#ifndef SANGUIS_WEAPON_DESCRIPTION_HPP_INCLUDED
#define SANGUIS_WEAPON_DESCRIPTION_HPP_INCLUDED

#include <sanguis/magazine_extra.hpp>
#include <sanguis/magazine_remaining.hpp>
#include <sanguis/magazine_size.hpp>
#include <sanguis/reload_time.hpp>
#include <sanguis/weapon_attribute_vector.hpp>
#include <sanguis/weapon_description_fwd.hpp>
#include <sanguis/weapon_type.hpp>
#include <sanguis/common/symbol.hpp>


namespace sanguis
{

class weapon_description
{
public:
	SANGUIS_COMMON_SYMBOL
	weapon_description(
		sanguis::weapon_type const &,
		sanguis::magazine_size,
		sanguis::magazine_extra,
		sanguis::magazine_remaining,
		sanguis::reload_time,
		sanguis::weapon_attribute_vector const &
	);

	SANGUIS_COMMON_SYMBOL
	sanguis::weapon_type const &
	weapon_type() const;

	SANGUIS_COMMON_SYMBOL
	sanguis::magazine_size const
	magazine_size() const;

	SANGUIS_COMMON_SYMBOL
	sanguis::magazine_extra const
	magazine_extra() const;

	SANGUIS_COMMON_SYMBOL
	sanguis::magazine_remaining const
	magazine_remaining() const;

	SANGUIS_COMMON_SYMBOL
	sanguis::reload_time const
	reload_time() const;

	SANGUIS_COMMON_SYMBOL
	sanguis::weapon_attribute_vector const &
	attributes() const;
private:
	sanguis::weapon_type weapon_type_;

	sanguis::magazine_size magazine_size_;

	sanguis::magazine_extra magazine_extra_;

	sanguis::magazine_remaining magazine_remaining_;

	sanguis::reload_time reload_time_;

	sanguis::weapon_attribute_vector attributes_;
};

}

#endif
