#include <sanguis/friend_type.hpp>
#include <sanguis/load/friend_name.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/unreachable.hpp>

fcppt::string sanguis::load::friend_name(sanguis::friend_type const _type)
{
#define SANGUIS_LOAD_FRIEND_NAME_CASE(name) \
  case sanguis::friend_type::name: \
    return FCPPT_TEXT(#name)

  switch (_type)
  {
    SANGUIS_LOAD_FRIEND_NAME_CASE(spider);
    SANGUIS_LOAD_FRIEND_NAME_CASE(sentry);
  }

  FCPPT_ASSERT_UNREACHABLE;

#undef SANGUIS_LOAD_FRIEND_NAME_CASE
}
