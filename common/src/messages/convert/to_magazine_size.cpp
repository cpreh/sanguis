#include <sanguis/exception.hpp>
#include <sanguis/magazine_type.hpp>
#include <sanguis/messages/convert/to_magazine_size.hpp>
#include <sanguis/messages/types/magazine_size.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/truncation_check.hpp>
#include <fcppt/optional/to_exception.hpp>

sanguis::messages::types::magazine_size
sanguis::messages::convert::to_magazine_size(sanguis::magazine_type const _size)
{
  return fcppt::optional::to_exception(
      fcppt::cast::truncation_check<sanguis::messages::types::magazine_size>(_size),
      [] { return sanguis::exception{FCPPT_TEXT("magazine size too large")}; });
}
