#ifndef SANGUIS_SERVER_DAMAGE_WRAPPER_HPP_INCLUDED
#define SANGUIS_SERVER_DAMAGE_WRAPPER_HPP_INCLUDED

#include <sanguis/server/damage/armor_meta_fwd.hpp>
#include <sanguis/server/damage/armor_unit_fwd.hpp>
#include <sanguis/server/damage/meta_fwd.hpp>
#include <sanguis/server/damage/type.hpp>
#include <sanguis/server/damage/unit_fwd.hpp>
#include <sanguis/server/damage/wrapper_fwd.hpp>

namespace sanguis::server::damage
{

class wrapper
{
public:
  explicit wrapper(sanguis::server::damage::type);

  [[nodiscard]]
  // NOLINTNEXTLINE(cppcoreguidelines-c-copy-assignment-signature,misc-unconventional-assign-operator)
  sanguis::server::damage::meta
  operator=(sanguis::server::damage::unit) const;

  [[nodiscard]]
  // NOLINTNEXTLINE(cppcoreguidelines-c-copy-assignment-signature,misc-unconventional-assign-operator)
  sanguis::server::damage::armor_meta
  operator=(sanguis::server::damage::armor_unit) const;

private:
  sanguis::server::damage::type type_;
};

}

#endif
