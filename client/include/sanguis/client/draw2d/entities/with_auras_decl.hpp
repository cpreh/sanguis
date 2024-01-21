#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_WITH_AURAS_DECL_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_WITH_AURAS_DECL_HPP_INCLUDED

#include <sanguis/aura_type.hpp>
#include <sanguis/diff_timer.hpp>
#include <sanguis/client/draw2d/entities/with_auras_fwd.hpp> // IWYU pragma: keep
#include <sanguis/client/draw2d/entities/with_auras_parameters_fwd.hpp>
#include <sanguis/client/draw2d/entities/ifaces/with_auras.hpp>
#include <sanguis/client/draw2d/sprite/normal/object.hpp>
#include <sanguis/client/draw2d/sprite/normal/system_ref.hpp>
#include <sanguis/client/load/auras/context_ref.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <map>
#include <fcppt/config/external_end.hpp>

namespace sanguis::client::draw2d::entities
{

template <typename Base>
class with_auras : public sanguis::client::draw2d::entities::ifaces::with_auras, public Base
{
  FCPPT_NONMOVABLE(with_auras);

public:
  using base_parameters = typename Base::parameters_type;

  using parameters_type = sanguis::client::draw2d::entities::with_auras_parameters<base_parameters>;

  explicit with_auras(parameters_type const &);

  ~with_auras() override;

protected:
  void update() override;

  void on_die() override;

private:
  void add_aura(sanguis::aura_type) override;

  sanguis::client::load::auras::context_ref const aura_load_context_;

  sanguis::client::draw2d::sprite::normal::system_ref const normal_system_;

  sanguis::diff_timer rotate_timer_;

  using sprite_map = std::map<sanguis::aura_type, sanguis::client::draw2d::sprite::normal::object>;

  sprite_map sprites_;
};

}

#endif
