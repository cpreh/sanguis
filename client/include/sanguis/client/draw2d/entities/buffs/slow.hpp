#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_BUFFS_SLOW_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_BUFFS_SLOW_HPP_INCLUDED

#include <sanguis/client/draw2d/entities/buffs/base.hpp>
#include <sanguis/client/draw2d/entities/model/object_fwd.hpp>
#include <sanguis/client/draw2d/sprite/normal/color.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/optional/object_decl.hpp>

namespace sanguis::client::draw2d::entities::buffs
{

class slow : public sanguis::client::draw2d::entities::buffs::base
{
  FCPPT_NONMOVABLE(slow);

public:
  slow();

  ~slow() override;

private:
  void apply(sanguis::client::draw2d::entities::model::object &) override; // NOLINT(google-runtime-references)

  void
  remove(sanguis::client::draw2d::entities::model::object &) override; // NOLINT(google-runtime-references)

  using optional_color = fcppt::optional::object<sanguis::client::draw2d::sprite::normal::color>;

  optional_color previous_color_;
};

}

#endif
