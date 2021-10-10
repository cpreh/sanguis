#include <sanguis/model/part_map.hpp>
#include <sanguis/model/impl/serialize/map.hpp>
#include <sanguis/model/impl/serialize/part.hpp>
#include <sanguis/model/impl/serialize/part_map.hpp>
#include <sge/charconv/utf8_string.hpp>
#include <sge/parse/json/member.hpp>

sge::parse::json::member
sanguis::model::impl::serialize::part_map(sanguis::model::part_map const &_parts)
{
  return sanguis::model::impl::serialize::map(
      _parts, sge::charconv::utf8_string{"parts"}, &sanguis::model::impl::serialize::part);
}
