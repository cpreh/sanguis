#include <sanguis/server/entities/auto_weak_link.hpp>
#include <sanguis/server/entities/with_links.hpp>

sanguis::server::entities::with_links::with_links() : links_() {}

sanguis::server::entities::with_links::~with_links() = default;

sanguis::server::entities::auto_weak_link sanguis::server::entities::with_links::link()
{
  return sanguis::server::entities::auto_weak_link(*this);
}

void sanguis::server::entities::with_links::reset_links() { links_.clear(); }

void sanguis::server::entities::with_links::insert_link(
    sanguis::server::entities::auto_weak_link &_link)
{
  links_.push_back(_link);
}
