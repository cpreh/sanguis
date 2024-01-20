#ifndef SANGUIS_SERVER_DAMAGE_BASIC_META_DECL_HPP_INCLUDED
#define SANGUIS_SERVER_DAMAGE_BASIC_META_DECL_HPP_INCLUDED

#include <sanguis/server/damage/basic_meta_fwd.hpp> // IWYU pragma: keep
#include <sanguis/server/damage/type.hpp>

namespace sanguis::server::damage
{

template <typename Unit>
class basic_meta
{
public:
  basic_meta(sanguis::server::damage::type, Unit);

  [[nodiscard]] sanguis::server::damage::type type() const;

  [[nodiscard]] Unit value() const;

private:
  sanguis::server::damage::type type_;

  Unit value_;
};

}

#endif
