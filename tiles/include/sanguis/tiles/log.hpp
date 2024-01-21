#ifndef SANGUIS_TILES_LOG_HPP_INCLUDED
#define SANGUIS_TILES_LOG_HPP_INCLUDED

#include <sanguis/tiles/log_fwd.hpp> // IWYU pragma: keep
#include <sanguis/tiles/symbol.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/log/context_reference_fwd.hpp>
#include <fcppt/log/object.hpp>

namespace sanguis::tiles
{

class log
{
  FCPPT_NONMOVABLE(log);

public:
  SANGUIS_TILES_SYMBOL
  explicit log(fcppt::log::context_reference);

  SANGUIS_TILES_SYMBOL
  ~log();

  [[nodiscard]] fcppt::log::object &main_log() const;

private:
  mutable fcppt::log::object main_log_;
};

}

#endif
