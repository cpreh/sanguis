#include <sanguis/optional_weapon_attribute_value.hpp>
#include <sanguis/weapon_attribute.hpp>
#include <sanguis/weapon_attribute_value.hpp>
#include <sanguis/weapon_description.hpp>
#include <sanguis/weapon_type.hpp>
#include <sanguis/weapon_type_to_is_primary.hpp>
#include <sanguis/client/weapon_attribute_total.hpp>
#include <sanguis/client/weapon_pair.hpp>
#include <sanguis/client/draw2d/scene/hover/compare_weapons.hpp>
#include <sanguis/client/draw2d/scene/hover/weapon_attribute_diff.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/algorithm/find_if_opt.hpp>
#include <fcppt/optional/bind.hpp>
#include <fcppt/optional/copy_value.hpp>
#include <fcppt/optional/deref.hpp>
#include <fcppt/variant/comparison.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cmath>
#include <fcppt/config/external_end.hpp>

sanguis::client::draw2d::scene::hover::weapon_attribute_diff
sanguis::client::draw2d::scene::hover::compare_weapons(
    sanguis::weapon_type const _type,
    sanguis::weapon_attribute const &_attribute,
    sanguis::client::weapon_pair const &_player_weapons)
{
  return sanguis::client::draw2d::scene::hover::weapon_attribute_diff{fcppt::optional::bind(
      _player_weapons.get(sanguis::weapon_type_to_is_primary(_type)),
      [_attribute, _type](sanguis::weapon_description const &_desc)
      {
        return _desc.weapon_type() != _type
                   ? sanguis::optional_weapon_attribute_value()
                   : fcppt::optional::bind(
                         fcppt::optional::copy_value(
                             fcppt::optional::deref(fcppt::algorithm::find_if_opt(
                                 _desc.attributes(),
                                 [&_attribute](sanguis::weapon_attribute const &_comp)
                                 { return _comp.type() == _attribute.type(); }))),
                         [_attribute](sanguis::weapon_attribute const _same_attribute)
                         {
                           auto const whole_value(
                               [](sanguis::weapon_attribute const &_nattribute) {
                                 return sanguis::client::weapon_attribute_total(
                                     _nattribute.base(), _nattribute.extra());
                               });

                           sanguis::weapon_attribute_value const diff(
                               whole_value(_attribute) - whole_value(_same_attribute));

                           return std::abs(diff) <
                                          fcppt::literal<sanguis::weapon_attribute_value>(
                                              0.01 // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
                                              )
                                      ? sanguis::optional_weapon_attribute_value()
                                      : sanguis::optional_weapon_attribute_value(diff);
                         });
      })};
}
