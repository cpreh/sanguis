#include <sanguis/pickup_type.hpp>
#include <sanguis/load/pickup_name.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/unreachable.hpp>

fcppt::string sanguis::load::pickup_name(sanguis::pickup_type const _type)
{
  switch (_type)
  {
  case sanguis::pickup_type::health:
    return FCPPT_TEXT("hp");
  case sanguis::pickup_type::monster:
    return FCPPT_TEXT("monster");
  }

  FCPPT_ASSERT_UNREACHABLE;
}
