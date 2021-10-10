#ifndef SANGUIS_SERVER_WEAPONS_LOG_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_LOG_HPP_INCLUDED

#include <sanguis/server/weapons/log_fwd.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/log/context_reference_fwd.hpp>
#include <fcppt/log/object.hpp>

namespace sanguis::server::weapons
{

class log
{
  FCPPT_NONMOVABLE(log);

public:
  explicit log(fcppt::log::context_reference);

  ~log();

  [[nodiscard]] fcppt::log::object &main_log() const;

private:
  mutable fcppt::log::object main_log_;
};

}

#endif
