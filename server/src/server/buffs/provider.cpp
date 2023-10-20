#include <sanguis/exception.hpp>
#include <sanguis/server/buffs/buff.hpp> // NOLINT(misc-include-cleaner)
#include <sanguis/server/buffs/provider.hpp>
#include <sanguis/server/buffs/unique_ptr.hpp>
#include <sanguis/server/entities/with_buffs.hpp>
#include <sanguis/server/entities/with_buffs_ref.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/reference_comparison.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/reference_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/container/find_opt_iterator.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

sanguis::server::buffs::provider::provider() : buffs_() {}

sanguis::server::buffs::provider::~provider() = default;

void sanguis::server::buffs::provider::add(
    sanguis::server::entities::with_buffs_ref const _entity,
    sanguis::server::buffs::unique_ptr &&_buff)
{
  using ret_type = std::pair<sanguis::server::buffs::provider::buff_map::iterator, bool>;

  ret_type const ret{this->buffs_.insert(std::make_pair(_entity, fcppt::make_ref(*_buff)))};

  if(!ret.second)
  {
    throw sanguis::exception{FCPPT_TEXT("Buff double insert!")};
  }

  _entity->add_buff(std::move(_buff));
}

void sanguis::server::buffs::provider::remove(sanguis::server::entities::with_buffs &_entity)
{
  fcppt::optional::maybe_void(
      fcppt::container::find_opt_iterator(this->buffs_, fcppt::make_ref(_entity)),
      [this, &_entity](sanguis::server::buffs::provider::buff_map::iterator const _it)
      {
        _entity.remove_buff(_it->second.get());

        this->buffs_.erase(_it);
      });
}
