#include <sanguis/creator/enemy_type.hpp>
#include <sanguis/server/entities/enemies/attribute_container.hpp>
#include <sanguis/server/entities/enemies/make_name.hpp>
#include <sanguis/server/entities/enemies/pretty_name.hpp>
#include <sanguis/server/entities/enemies/skills/container.hpp>
#include <sanguis/server/entities/enemies/skills/skill.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>

fcppt::string sanguis::server::entities::enemies::make_name(
    sanguis::server::entities::enemies::attribute_container const &_attributes,
    sanguis::server::entities::enemies::skills::container const &_skills,
    sanguis::creator::enemy_type const _enemy_type)
{
  fcppt::string result{};

  // TODO(philipp): Refactor this!
  for (auto const &attribute : _attributes)
  {
    result += attribute.text() + FCPPT_TEXT(' ');
  }

  for (auto const &skill : _skills)
  {
    result += skill->attribute().text() + FCPPT_TEXT(' ');
  }

  return result + sanguis::server::entities::enemies::pretty_name(_enemy_type);
}
