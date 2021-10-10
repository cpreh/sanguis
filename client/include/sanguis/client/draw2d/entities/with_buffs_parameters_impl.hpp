#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_WITH_BUFFS_PARAMETERS_IMPL_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_WITH_BUFFS_PARAMETERS_IMPL_HPP_INCLUDED

#include <sanguis/buff_type_vector.hpp>
#include <sanguis/diff_clock_cref.hpp>
#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/client/draw2d/entities/with_buffs_parameters_decl.hpp>
#include <sanguis/client/draw2d/sprite/normal/system_fwd.hpp>
#include <sanguis/client/draw2d/sprite/normal/system_ref.hpp>
#include <sanguis/client/load/model/collection_cref.hpp>
#include <sanguis/client/load/model/collection_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

template <typename Base>
sanguis::client::draw2d::entities::with_buffs_parameters<Base>::with_buffs_parameters(
    sanguis::diff_clock_cref const _diff_clock,
    sanguis::client::draw2d::sprite::normal::system_ref const _normal_system,
    sanguis::client::load::model::collection_cref const _model_collection,
    sanguis::buff_type_vector &&_buffs,
    Base &&_base)
    : diff_clock_(_diff_clock),
      normal_system_(_normal_system),
      model_collection_(_model_collection),
      buffs_(std::move(_buffs)),
      base_(std::move(_base))
{
}

template <typename Base>
sanguis::diff_clock const &
sanguis::client::draw2d::entities::with_buffs_parameters<Base>::diff_clock() const
{
  return diff_clock_.get();
}

template <typename Base>
sanguis::client::draw2d::sprite::normal::system &
sanguis::client::draw2d::entities::with_buffs_parameters<Base>::normal_system() const
{
  return normal_system_.get();
}

template <typename Base>
sanguis::client::load::model::collection const &
sanguis::client::draw2d::entities::with_buffs_parameters<Base>::model_collection() const
{
  return model_collection_.get();
}

template <typename Base>
sanguis::buff_type_vector const &
sanguis::client::draw2d::entities::with_buffs_parameters<Base>::buffs() const
{
  return buffs_;
}

template <typename Base>
Base const &sanguis::client::draw2d::entities::with_buffs_parameters<Base>::base() const
{
  return base_;
}

#endif
