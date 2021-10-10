#include <sanguis/creator/name.hpp>
#include <sanguis/creator/impl/graveyard_name.hpp>
#include <fcppt/text.hpp>

sanguis::creator::name sanguis::creator::impl::graveyard_name()
{
  return sanguis::creator::name(FCPPT_TEXT("graveyard"));
}
