#include <sanguis/entity_id.hpp>
#include <sanguis/exception.hpp>
#include <sanguis/server/world/sight_range.hpp>
#include <fcppt/not.hpp>
#include <fcppt/text.hpp>

sanguis::server::world::sight_range::sight_range() : entries_() {}

void sanguis::server::world::sight_range::add(sanguis::entity_id const _id)
{
  if(fcppt::not_(this->entries_.insert(_id).second))
  {
    throw sanguis::exception{FCPPT_TEXT("Double sight insert!")};
  }
}

void sanguis::server::world::sight_range::remove(sanguis::entity_id const _id)
{
  if(this->entries_.erase(_id) != 1U)
  {
    throw sanguis::exception{FCPPT_TEXT("Failed to remove sight!")};
  }
}

bool sanguis::server::world::sight_range::contains(sanguis::entity_id const _id) const
{
  return entries_.find(_id) != entries_.end();
}

bool sanguis::server::world::sight_range::empty() const { return entries_.empty(); }
