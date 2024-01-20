#ifndef SANGUIS_WEAPON_ATTRIBUTE_HPP_INCLUDED
#define SANGUIS_WEAPON_ATTRIBUTE_HPP_INCLUDED

#include <sanguis/weapon_attribute_base.hpp>
#include <sanguis/weapon_attribute_extra.hpp>
#include <sanguis/weapon_attribute_fwd.hpp> // IWYU pragma: keep
#include <sanguis/weapon_attribute_type.hpp>
#include <sanguis/common/symbol.hpp>

namespace sanguis
{

class weapon_attribute
{
public:
  SANGUIS_COMMON_SYMBOL
  weapon_attribute(
      sanguis::weapon_attribute_type,
      sanguis::weapon_attribute_base,
      sanguis::weapon_attribute_extra);

  [[nodiscard]] SANGUIS_COMMON_SYMBOL sanguis::weapon_attribute_type type() const;

  [[nodiscard]] SANGUIS_COMMON_SYMBOL sanguis::weapon_attribute_base base() const;

  [[nodiscard]] SANGUIS_COMMON_SYMBOL sanguis::weapon_attribute_extra extra() const;

private:
  sanguis::weapon_attribute_type type_;

  sanguis::weapon_attribute_base base_;

  sanguis::weapon_attribute_extra extra_;
};

}

#endif
