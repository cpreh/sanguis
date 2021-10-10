#include <sanguis/model/cell_size.hpp>
#include <sanguis/model/impl/deserialize/cell_size.hpp>
#include <sge/charconv/utf8_string.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/find_member_exn.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/convert/to_static_container.hpp>
#include <fcppt/make_cref.hpp>

sanguis::model::cell_size
sanguis::model::impl::deserialize::cell_size(sge::parse::json::object const &_object)
{
  return sanguis::model::cell_size(
      sge::parse::json::convert::to_static_container<sanguis::model::cell_size::value_type>(
          sge::parse::json::find_member_exn<sge::parse::json::array>(
              fcppt::make_cref(_object.members), sge::charconv::utf8_string{"cell_dimensions"})
              .get()));
}
