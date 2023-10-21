#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_WITH_BUFFS_IMPL_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_WITH_BUFFS_IMPL_HPP_INCLUDED

#include <sanguis/buff_type.hpp>
#include <sanguis/exception.hpp>
#include <sanguis/client/draw2d/entities/with_buffs_decl.hpp> // IWYU pragma: export
#include <sanguis/client/draw2d/entities/with_buffs_parameters_decl.hpp>
#include <sanguis/client/draw2d/entities/buffs/base.hpp>
#include <sanguis/client/draw2d/entities/buffs/create.hpp>
#include <fcppt/not.hpp>
#include <fcppt/text.hpp>
#include <fcppt/container/find_opt_iterator.hpp>
#include <fcppt/optional/to_exception.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

template <typename Base>
sanguis::client::draw2d::entities::with_buffs<Base>::with_buffs(parameters_type const &_parameters)
    : Base(_parameters.base()),
      diff_clock_(_parameters.diff_clock()),
      normal_system_(_parameters.normal_system()),
      model_collection_(_parameters.model_collection()),
      buffs_()
{
  for (auto const &buff : _parameters.buffs())
  {
    this->add_buff(buff);
  }
}

namespace sanguis::client::draw2d::entities
{
template <typename Base>
with_buffs<Base>::~with_buffs() = default;
}

template <typename Base>
void sanguis::client::draw2d::entities::with_buffs<Base>::update()
{
  Base::update();

  for (auto const &buff : buffs_)
  {
    buff.second->update(*this);
  }
}

template <typename Base>
void sanguis::client::draw2d::entities::with_buffs<Base>::add_buff(sanguis::buff_type const _type)
{
  {
    // TODO(philipp): algorithm::find
    auto const it(buffs_.find(_type));

    if (it != buffs_.end())
    {
      it->second->increment();

      return;
    }
  }

  using insert_result = std::pair<buff_map::iterator, bool>;

  insert_result const result(buffs_.insert(std::make_pair(
      _type,
      sanguis::client::draw2d::entities::buffs::create(
          diff_clock_, normal_system_, model_collection_, *this, _type))));

  if (fcppt::not_(result.second))
  {
    throw sanguis::exception{FCPPT_TEXT("Double insert of buffs!")};
  }

  result.first->second->apply(*this);
}

template <typename Base>
void sanguis::client::draw2d::entities::with_buffs<Base>::remove_buff(
    sanguis::buff_type const _type)
{
  auto const it{fcppt::optional::to_exception(
      fcppt::container::find_opt_iterator(this->buffs_, _type),
      [] { return sanguis::exception{FCPPT_TEXT("Buff not found!")}; })};

  if (!it->second->decrement())
  {
    return;
  }

  it->second->remove(*this);

  this->buffs_.erase(it);
}

#endif
