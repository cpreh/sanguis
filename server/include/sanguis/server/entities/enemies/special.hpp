#ifndef SANGUIS_SERVER_ENTITIES_ENEMIES_SPECIAL_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_ENEMIES_SPECIAL_HPP_INCLUDED

#include <sanguis/enemy_kind_fwd.hpp>
#include <sanguis/random_generator_ref.hpp>
#include <sanguis/messages/types/string.hpp>
#include <sanguis/server/entities/enemies/attribute_container.hpp>
#include <sanguis/server/entities/enemies/enemy.hpp>
#include <sanguis/server/entities/enemies/is_unique.hpp>
#include <sanguis/server/entities/enemies/parameters_fwd.hpp>
#include <sanguis/server/entities/enemies/skills/container.hpp>
#include <sanguis/server/entities/enemies/skills/factory/container.hpp>
#include <fcppt/nonmovable.hpp>

namespace sanguis::server::entities::enemies
{

class special : public sanguis::server::entities::enemies::enemy
{
  FCPPT_NONMOVABLE(special);

public:
  special(
      sanguis::random_generator_ref,
      sanguis::server::entities::enemies::parameters &&,
      sanguis::server::entities::enemies::attribute_container const &,
      sanguis::server::entities::enemies::skills::factory::container const &,
      sanguis::server::entities::enemies::is_unique);

  ~special() override;

private:
  void update() override;

  void remove_from_game() override;

  [[nodiscard]] sanguis::messages::types::string const &name() const override;

  [[nodiscard]] sanguis::enemy_kind enemy_kind() const override;

  sanguis::server::entities::enemies::skills::container const skills_;

  sanguis::messages::types::string const name_;

  sanguis::server::entities::enemies::is_unique const is_unique_;
};

}

#endif
