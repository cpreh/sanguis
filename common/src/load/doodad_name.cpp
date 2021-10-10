#include <sanguis/doodad_type.hpp>
#include <sanguis/load/doodad_name.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/unreachable.hpp>

fcppt::string sanguis::load::doodad_name(sanguis::doodad_type const _type)
{
  switch (_type)
  {
  case sanguis::doodad_type::portal_blocker:
    return FCPPT_TEXT("portal_blocker");
  }

  FCPPT_ASSERT_UNREACHABLE;
}
