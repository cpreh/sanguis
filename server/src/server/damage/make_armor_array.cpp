#include <sanguis/server/damage/armor_array.hpp>
#include <sanguis/server/damage/armor_meta.hpp> // NOLINT(misc-include-cleaner)
#include <sanguis/server/damage/armor_meta_list.hpp>
#include <sanguis/server/damage/basic_make_array.hpp>
#include <sanguis/server/damage/make_armor_array.hpp>

sanguis::server::damage::armor_array
sanguis::server::damage::make_armor_array(sanguis::server::damage::armor_meta_list const &_list)
{
  return sanguis::server::damage::basic_make_array(_list);
}
