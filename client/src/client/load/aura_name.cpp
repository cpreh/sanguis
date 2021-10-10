#include <sanguis/aura_type.hpp>
#include <sanguis/client/load/aura_name.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/unreachable.hpp>

fcppt::string sanguis::client::load::aura_name(sanguis::aura_type const _type)
{
#define SANGUIS_LOAD_AURA_NAME_CASE(name) \
  case sanguis::aura_type::name: \
    return FCPPT_TEXT(#name)
  switch (_type)
  {
    SANGUIS_LOAD_AURA_NAME_CASE(burn);
    SANGUIS_LOAD_AURA_NAME_CASE(slow);
  }

  FCPPT_ASSERT_UNREACHABLE;

#undef SANGUIS_LOAD_AURA_NAME_CASE
}
