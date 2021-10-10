#include <sanguis/projectile_type.hpp>
#include <sanguis/load/projectile_name.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/unreachable.hpp>

fcppt::string sanguis::load::projectile_name(sanguis::projectile_type const _type)
{
#define SANGUIS_LOAD_PROJECTILE_NAME_CASE(name) \
  case sanguis::projectile_type::name: \
    return FCPPT_TEXT(#name)

  switch (_type)
  {
    SANGUIS_LOAD_PROJECTILE_NAME_CASE(bullet);
  }

  FCPPT_ASSERT_UNREACHABLE;
}
