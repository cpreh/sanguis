#include <sanguis/creator/name.hpp>
#include <sanguis/creator/impl/rooms_name.hpp>
#include <fcppt/text.hpp>

sanguis::creator::name sanguis::creator::impl::rooms_name()
{
  return sanguis::creator::name(FCPPT_TEXT("rooms"));
}
