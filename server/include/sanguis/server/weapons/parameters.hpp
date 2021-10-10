#ifndef SANGUIS_SERVER_WEAPONS_PARAMETERS_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_PARAMETERS_HPP_INCLUDED

#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/weapon_type.hpp>
#include <sanguis/server/weapons/backswing_time.hpp>
#include <sanguis/server/weapons/cast_point.hpp>
#include <sanguis/server/weapons/common_parameters.hpp>
#include <sanguis/server/weapons/log_fwd.hpp>
#include <sanguis/server/weapons/optional_reload_time.hpp>
#include <sanguis/server/weapons/parameters_fwd.hpp>
#include <sanguis/server/weapons/range.hpp>
#include <sanguis/server/weapons/attributes/optional_accuracy.hpp>
#include <sanguis/server/weapons/attributes/optional_magazine_size.hpp>

namespace sanguis::server::weapons
{

class parameters
{
public:
  parameters(
      sanguis::server::weapons::common_parameters const &,
      sanguis::weapon_type,
      sanguis::server::weapons::attributes::optional_accuracy,
      sanguis::server::weapons::range,
      sanguis::server::weapons::attributes::optional_magazine_size,
      sanguis::server::weapons::backswing_time,
      sanguis::server::weapons::cast_point,
      sanguis::server::weapons::optional_reload_time);

  [[nodiscard]] sanguis::server::weapons::common_parameters const &common_parameters() const;

  [[nodiscard]] sanguis::server::weapons::log const &log() const;

  [[nodiscard]] sanguis::random_generator &random_generator() const;

  [[nodiscard]] sanguis::weapon_type weapon_type() const;

  [[nodiscard]] sanguis::server::weapons::attributes::optional_accuracy accuracy() const;

  [[nodiscard]] sanguis::server::weapons::range range() const;

  [[nodiscard]] sanguis::server::weapons::attributes::optional_magazine_size magazine_size() const;

  [[nodiscard]] sanguis::server::weapons::backswing_time backswing_time() const;

  [[nodiscard]] sanguis::server::weapons::cast_point cast_point() const;

  [[nodiscard]] sanguis::server::weapons::optional_reload_time reload_time() const;

private:
  sanguis::server::weapons::common_parameters common_parameters_;

  sanguis::weapon_type weapon_type_;

  sanguis::server::weapons::attributes::optional_accuracy accuracy_;

  sanguis::server::weapons::range range_;

  sanguis::server::weapons::attributes::optional_magazine_size magazine_size_;

  sanguis::server::weapons::backswing_time backswing_time_;

  sanguis::server::weapons::cast_point cast_point_;

  sanguis::server::weapons::optional_reload_time reload_time_;
};

}

#endif
