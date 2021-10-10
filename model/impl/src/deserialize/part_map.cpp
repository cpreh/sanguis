#include <sanguis/model/part_map.hpp>
#include <sanguis/model/impl/deserialize/map.hpp>
#include <sanguis/model/impl/deserialize/part.hpp>
#include <sanguis/model/impl/deserialize/part_map.hpp>
#include <sge/charconv/utf8_string.hpp>
#include <sge/parse/json/object_fwd.hpp>

sanguis::model::part_map
sanguis::model::impl::deserialize::part_map(sge::parse::json::object const &_object)
{
  return sanguis::model::impl::deserialize::map<sanguis::model::part_map>(
      _object, sge::charconv::utf8_string{"parts"}, &sanguis::model::impl::deserialize::part);
}
