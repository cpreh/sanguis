#ifndef SANGUIS_SERVER_WEAPONS_SPIDER_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_SPIDER_HPP_INCLUDED

#include <sanguis/weapon_attribute_vector.hpp>
#include <sanguis/server/entities/optional_base_ref_fwd.hpp>
#include <sanguis/server/weapons/attack_fwd.hpp>
#include <sanguis/server/weapons/common_parameters_fwd.hpp>
#include <sanguis/server/weapons/spawn.hpp>
#include <sanguis/server/weapons/spawn_parameters_fwd.hpp>
#include <sanguis/server/weapons/spawn_weapon.hpp>
#include <sanguis/server/weapons/spider_parameters_fwd.hpp>
#include <sanguis/server/weapons/unique_ptr.hpp>
#include <sanguis/server/weapons/attributes/health.hpp>
#include <fcppt/nonmovable.hpp>

namespace sanguis::server::weapons
{

class spider : public sanguis::server::weapons::spawn
{
  FCPPT_NONMOVABLE(spider);

public:
  spider(
      sanguis::server::weapons::common_parameters const &,
      sanguis::server::weapons::spawn_weapon &&,
      sanguis::server::weapons::spider_parameters const &);

  ~spider() override;

  spider(
      sanguis::server::weapons::spawn_parameters const &,
      sanguis::server::weapons::attributes::health);

private:
  [[nodiscard]] sanguis::server::weapons::unique_ptr clone() const override;

  [[nodiscard]] sanguis::server::entities::optional_base_ref do_spawn(
      sanguis::server::weapons::attack const &,
      sanguis::server::weapons::spawn_weapon const &) override;

  [[nodiscard]] sanguis::weapon_attribute_vector extra_attributes() const override;

  sanguis::server::weapons::attributes::health const health_;
};

}

#endif
