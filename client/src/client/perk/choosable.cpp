#include <sanguis/exception.hpp>
#include <sanguis/perk_type.hpp>
#include <sanguis/client/player_level.hpp>
#include <sanguis/client/perk/choosable.hpp>
#include <sanguis/client/perk/choosable_state.hpp>
#include <sanguis/client/perk/find_info_const.hpp>
#include <sanguis/client/perk/info.hpp>
#include <sanguis/client/perk/remaining_levels.hpp>
#include <sanguis/client/perk/tree.hpp>
#include <fcppt/const.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/text.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/optional/to_exception.hpp>
#include <fcppt/preprocessor/ignore_dangling_reference.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

sanguis::client::perk::choosable_state sanguis::client::perk::choosable(
    sanguis::perk_type const _type,
    sanguis::client::perk::tree const &_tree,
    sanguis::client::player_level const _player_level,
    sanguis::client::perk::remaining_levels const _remaining_levels)
{
  sanguis::client::perk::tree const &node(
      sanguis::client::perk::find_info_const(_type, fcppt::make_cref(_tree)));

  sanguis::client::perk::info const &info{fcppt::optional::to_exception(
      node.value(), [] { return sanguis::exception{FCPPT_TEXT("Perk node not set!")}; })};

  FCPPT_PP_PUSH_WARNING
  FCPPT_PP_IGNORE_DANGLING_REFERENCE
  sanguis::client::perk::tree const &parent_node{
      fcppt::optional::to_exception(
          node.parent(), [] { return sanguis::exception{FCPPT_TEXT("Perk has no parent node!")}; })
          .get()};
  FCPPT_PP_POP_WARNING

  if (info.max_level().get() == info.level())
  {
    return sanguis::client::perk::choosable_state::max_level;
  }

  if (fcppt::optional::maybe(
          parent_node.value(),
          fcppt::const_(false),
          [&info](sanguis::client::perk::info const &_parent_info)
          { return _parent_info.level() < info.required_parent_level().get(); }))
  {
    return sanguis::client::perk::choosable_state::parent_level;
  }

  if (info.required_player_level().get() > _player_level)
  {
    return sanguis::client::perk::choosable_state::player_level;
  }

  if (_remaining_levels.get().get() == 0U)
  {
    return sanguis::client::perk::choosable_state::level_up;
  }

  return sanguis::client::perk::choosable_state::ok;
}
