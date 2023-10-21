#include <sanguis/exception.hpp>
#include <sanguis/perk_type.hpp>
#include <sanguis/server/perks/tree/choose.hpp>
#include <sanguis/server/perks/tree/container.hpp>
#include <sanguis/server/perks/tree/find_node.hpp>
#include <sanguis/server/perks/tree/status.hpp>
#include <fcppt/text.hpp>
#include <fcppt/optional/to_exception.hpp>

void sanguis::server::perks::tree::choose(
    sanguis::server::perks::tree::container &_tree, sanguis::perk_type const _perk_type)
{
  fcppt::optional::to_exception(
      sanguis::server::perks::tree::find_node(_tree, _perk_type),
      [] { return sanguis::exception{FCPPT_TEXT("Perk not found in the tree!")}; })
      .get()
      .value()
      .choose();
}
