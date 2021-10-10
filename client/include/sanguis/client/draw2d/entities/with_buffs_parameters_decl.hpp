#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_WITH_BUFFS_PARAMETERS_DECL_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_WITH_BUFFS_PARAMETERS_DECL_HPP_INCLUDED

#include <sanguis/buff_type_vector.hpp>
#include <sanguis/diff_clock_cref.hpp>
#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/client/draw2d/sprite/normal/system_fwd.hpp>
#include <sanguis/client/draw2d/sprite/normal/system_ref.hpp>
#include <sanguis/client/load/model/collection_cref.hpp>
#include <sanguis/client/load/model/collection_fwd.hpp>

namespace sanguis::client::draw2d::entities
{

template <typename Base>
class with_buffs_parameters
{
public:
  with_buffs_parameters(
      sanguis::diff_clock_cref,
      sanguis::client::draw2d::sprite::normal::system_ref,
      sanguis::client::load::model::collection_cref,
      sanguis::buff_type_vector &&,
      Base &&);

  [[nodiscard]] sanguis::diff_clock const &diff_clock() const;

  [[nodiscard]] sanguis::client::draw2d::sprite::normal::system &normal_system() const;

  [[nodiscard]] sanguis::client::load::model::collection const &model_collection() const;

  [[nodiscard]] sanguis::buff_type_vector const &buffs() const;

  [[nodiscard]] Base const &base() const;

private:
  sanguis::diff_clock_cref diff_clock_;

  sanguis::client::draw2d::sprite::normal::system_ref normal_system_;

  sanguis::client::load::model::collection_cref model_collection_;

  sanguis::buff_type_vector buffs_;

  Base base_;
};

}

#endif
