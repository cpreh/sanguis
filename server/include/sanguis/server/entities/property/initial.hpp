#ifndef SANGUIS_SERVER_ENTITIES_PROPERTY_INITIAL_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROPERTY_INITIAL_HPP_INCLUDED

#include <sanguis/server/entities/property/initial_fwd.hpp>
#include <sanguis/server/entities/property/value.hpp>
#include <fcppt/declare_strong_typedef.hpp>
#include <fcppt/strong_typedef_impl.hpp> // IWYU pragma: keep

namespace sanguis::server::entities::property
{

class initial
{
public:
  FCPPT_DECLARE_STRONG_TYPEDEF(sanguis::server::entities::property::value, base);

  FCPPT_DECLARE_STRONG_TYPEDEF(sanguis::server::entities::property::value, current);

  initial(
      sanguis::server::entities::property::initial::base,
      sanguis::server::entities::property::initial::current);

  [[nodiscard]] sanguis::server::entities::property::value get_base() const;

  [[nodiscard]] sanguis::server::entities::property::value get_current() const;

private:
  sanguis::server::entities::property::value base_;
  sanguis::server::entities::property::value current_;
};

}

#endif
