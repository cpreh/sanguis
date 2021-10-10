#ifndef SANGUIS_CLIENT_PERK_STATE_HPP_INCLUDED
#define SANGUIS_CLIENT_PERK_STATE_HPP_INCLUDED

#include <sanguis/perk_type.hpp>
#include <sanguis/client/level.hpp>
#include <sanguis/client/player_level.hpp>
#include <sanguis/client/perk/change_callback.hpp>
#include <sanguis/client/perk/change_function.hpp>
#include <sanguis/client/perk/choosable_state_fwd.hpp>
#include <sanguis/client/perk/info.hpp>
#include <sanguis/client/perk/level.hpp>
#include <sanguis/client/perk/level_callback.hpp>
#include <sanguis/client/perk/level_function.hpp>
#include <sanguis/client/perk/remaining_levels.hpp>
#include <sanguis/client/perk/send_callback.hpp>
#include <sanguis/client/perk/state_fwd.hpp>
#include <sanguis/client/perk/tree_fwd.hpp>
#include <sanguis/client/perk/tree_unique_ptr.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/optional/object_decl.hpp>
#include <fcppt/signal/auto_connection_fwd.hpp>
#include <fcppt/signal/object_decl.hpp>

namespace sanguis::client::perk
{

class state
{
  FCPPT_NONMOVABLE(state);

public:
  explicit state(sanguis::client::perk::send_callback &&);

  ~state();

  void perks(sanguis::client::perk::tree_unique_ptr &&, sanguis::client::perk::remaining_levels);

  void player_level(sanguis::client::player_level);

  [[nodiscard]] bool choose_perk(sanguis::perk_type);

  [[nodiscard]] sanguis::client::perk::tree const &perks() const;

  [[nodiscard]] sanguis::client::player_level player_level() const;

  [[nodiscard]] sanguis::client::perk::remaining_levels remaining_levels() const;

  [[nodiscard]] sanguis::client::perk::level perk_level(sanguis::perk_type) const;

  [[nodiscard]] sanguis::client::perk::choosable_state choosable(sanguis::perk_type) const;

  [[nodiscard]] fcppt::signal::auto_connection
  register_level_change(sanguis::client::perk::level_callback &&);

  [[nodiscard]] fcppt::signal::auto_connection
  register_perks_change(sanguis::client::perk::change_callback &&);

private:
  [[nodiscard]] sanguis::client::perk::tree &perks_impl();

  sanguis::client::perk::send_callback const send_callback_;

  using optional_tree_unique_ptr = fcppt::optional::object<sanguis::client::perk::tree_unique_ptr>;

  optional_tree_unique_ptr perks_;

  sanguis::client::player_level current_level_;

  sanguis::client::perk::remaining_levels remaining_levels_;

  fcppt::signal::object<sanguis::client::perk::level_function> level_signal_;

  fcppt::signal::object<sanguis::client::perk::change_function> change_signal_;
};

}

#endif
