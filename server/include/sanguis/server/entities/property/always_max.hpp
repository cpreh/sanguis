#ifndef SANGUIS_SERVER_ENTITIES_PROPERTY_ALWAYS_MAX_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROPERTY_ALWAYS_MAX_HPP_INCLUDED

#include <sanguis/server/entities/property/always_max_fwd.hpp> // IWYU pragma: keep
#include <sanguis/server/entities/property/base.hpp>
#include <sanguis/server/entities/property/change_callback.hpp>
#include <sanguis/server/entities/property/change_signal.hpp>
#include <sanguis/server/entities/property/value.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/signal/auto_connection_fwd.hpp>
#include <fcppt/signal/object_decl.hpp> // IWYU pragma: keep

namespace sanguis::server::entities::property
{

class always_max : public sanguis::server::entities::property::base
{
  FCPPT_NONCOPYABLE(always_max);

public:
  explicit always_max(sanguis::server::entities::property::value);

  always_max(always_max &&) noexcept;

  always_max &operator=(always_max &&) noexcept;

  ~always_max() override;

  [[nodiscard]] sanguis::server::entities::property::value current() const;

  [[nodiscard]] fcppt::signal::auto_connection
  register_change_callback(sanguis::server::entities::property::change_callback &&);

private:
  void on_recalc_max(sanguis::server::entities::property::value) override;

  sanguis::server::entities::property::value current_;

  sanguis::server::entities::property::change_signal change_signal_;
};

}

#endif
