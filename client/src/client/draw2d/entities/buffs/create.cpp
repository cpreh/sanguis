#include <sanguis/buff_type.hpp>
#include <sanguis/diff_clock_cref.hpp>
#include <sanguis/client/draw2d/entities/buffs/base.hpp>
#include <sanguis/client/draw2d/entities/buffs/burn.hpp>
#include <sanguis/client/draw2d/entities/buffs/create.hpp>
#include <sanguis/client/draw2d/entities/buffs/slow.hpp>
#include <sanguis/client/draw2d/entities/buffs/unique_ptr.hpp>
#include <sanguis/client/draw2d/entities/model/object_fwd.hpp>
#include <sanguis/client/draw2d/sprite/normal/system_ref.hpp>
#include <sanguis/client/load/model/collection_cref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/enum/make_invalid.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

sanguis::client::draw2d::entities::buffs::unique_ptr
sanguis::client::draw2d::entities::buffs::create(
    sanguis::diff_clock_cref const _diff_clock,
    sanguis::client::draw2d::sprite::normal::system_ref const _normal_system,
    sanguis::client::load::model::collection_cref const _model_collection,
    sanguis::client::draw2d::entities::model::object const &_model,
    sanguis::buff_type const _type)
{
  FCPPT_PP_PUSH_WARNING
  FCPPT_PP_DISABLE_GCC_WARNING(-Wswitch-default)
  switch (_type)
  {
  case sanguis::buff_type::slow:
    return fcppt::unique_ptr_to_base<sanguis::client::draw2d::entities::buffs::base>(
        fcppt::make_unique_ptr<sanguis::client::draw2d::entities::buffs::slow>());
  case sanguis::buff_type::burn:
    return fcppt::unique_ptr_to_base<sanguis::client::draw2d::entities::buffs::base>(
        fcppt::make_unique_ptr<sanguis::client::draw2d::entities::buffs::burn>(
            _diff_clock, _normal_system, _model_collection, _model));
  }
  FCPPT_PP_POP_WARNING

  throw fcppt::enum_::make_invalid(_type);
}
