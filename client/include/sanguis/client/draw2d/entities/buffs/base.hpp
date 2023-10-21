#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_BUFFS_BASE_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_BUFFS_BASE_HPP_INCLUDED

#include <sanguis/client/draw2d/entities/buffs/base_fwd.hpp>
#include <sanguis/client/draw2d/entities/model/object_fwd.hpp>
#include <fcppt/nonmovable.hpp>

namespace sanguis::client::draw2d::entities::buffs
{

class base
{
  FCPPT_NONMOVABLE(base);

protected:
  base();

public:
  virtual ~base() = 0;

  virtual void
  apply(sanguis::client::draw2d::entities::model::object &); // NOLINT(google-runtime-references)

  virtual void
  remove(sanguis::client::draw2d::entities::model::object &); // NOLINT(google-runtime-references)

  virtual void update(sanguis::client::draw2d::entities::model::object const &);

  void increment();

  [[nodiscard]] bool decrement();

private:
  using counter = unsigned;

  counter counter_; // NOLINT(cppcoreguidelines-use-default-member-init,modernize-use-default-member-init)
};

}

#endif
