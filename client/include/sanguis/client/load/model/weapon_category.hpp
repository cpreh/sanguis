#ifndef SANGUIS_CLIENT_LOAD_MODEL_WEAPON_CATEGORY_HPP_INCLUDED
#define SANGUIS_CLIENT_LOAD_MODEL_WEAPON_CATEGORY_HPP_INCLUDED

#include <sanguis/client/load/animation_type_fwd.hpp>
#include <sanguis/client/load/model/animation_fwd.hpp>
#include <sanguis/client/load/model/animation_map.hpp>
#include <sanguis/client/load/model/global_parameters_fwd.hpp>
#include <sanguis/client/load/model/weapon_category_fwd.hpp> // IWYU pragma: keep
#include <sanguis/model/weapon_category_fwd.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/log/object_fwd.hpp>

namespace sanguis::client::load::model
{

class weapon_category
{
  FCPPT_NONMOVABLE(weapon_category);

public:
  weapon_category(
      fcppt::log::object &, // NOLINT(google-runtime-references)
      sanguis::model::weapon_category const &,
      sanguis::client::load::model::global_parameters const &);

  ~weapon_category();

  // TODO(philipp): optionals
  [[nodiscard]] sanguis::client::load::model::animation const &
  operator[](sanguis::client::load::animation_type) const;

  [[nodiscard]] bool has_animation(sanguis::client::load::animation_type) const;

private:
  sanguis::client::load::model::animation_map const animations_;
};

}

#endif
