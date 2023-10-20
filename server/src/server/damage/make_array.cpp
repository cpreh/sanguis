#include <sanguis/server/damage/array.hpp>
#include <sanguis/server/damage/basic_make_array.hpp>
#include <sanguis/server/damage/make_array.hpp>
#include <sanguis/server/damage/meta.hpp> // NOLINT(misc-include-cleaner)
#include <sanguis/server/damage/meta_list.hpp>

sanguis::server::damage::array
sanguis::server::damage::make_array(sanguis::server::damage::meta_list const &_list)
{
  return sanguis::server::damage::basic_make_array(_list);
}
