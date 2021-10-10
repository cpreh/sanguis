#include <sanguis/server/entities/property/add.hpp>
#include <sanguis/server/entities/property/changeable.hpp>
#include <sanguis/server/entities/property/value.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <fcppt/config/external_end.hpp>

void sanguis::server::entities::property::add(
    sanguis::server::entities::property::changeable &_changeable,
    sanguis::server::entities::property::value const &_value)
{
  _changeable.current(std::min(_changeable.max(), _changeable.current() + _value));
}
