#ifndef SANGUIS_SERVER_ENTITIES_CENTER_SIMPLE_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_CENTER_SIMPLE_HPP_INCLUDED

#include <sanguis/server/center.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/optional_transfer_result_fwd.hpp>
#include <sanguis/server/entities/transfer_parameters_fwd.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/optional/object_decl.hpp>

namespace sanguis::server::entities
{

class center_simple : public virtual sanguis::server::entities::base
{
  FCPPT_NONMOVABLE(center_simple);

protected:
  center_simple();

public:
  [[nodiscard]] sanguis::server::center center() const final;

  ~center_simple() override = 0;

protected:
  [[nodiscard]] sanguis::server::entities::optional_transfer_result
  on_transfer(sanguis::server::entities::transfer_parameters const &) override;

private:
  using optional_center = fcppt::optional::object<sanguis::server::center>;

  optional_center center_;
};

}

#endif
