/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#include <sanguis/diff_clock_cref.hpp>
#include <sanguis/diff_timer.hpp>
#include <sanguis/client/draw2d/sprite/animation/loop_method.hpp>
#include <sanguis/client/draw2d/sprite/animation/texture.hpp>
#include <sanguis/client/load/resource/animation/series.hpp>
#include <sanguis/client/load/resource/animation/series_cref.hpp>
#include <sge/texture/const_part_ref.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iterator>
#include <fcppt/config/external_end.hpp>

sanguis::client::draw2d::sprite::animation::texture::texture(
    sanguis::client::load::resource::animation::series_cref const _series,
    sanguis::client::draw2d::sprite::animation::loop_method const _loop_method,
    sanguis::diff_clock_cref const _diff_clock)
    : series_(_series),
      loop_method_(_loop_method),
      pos_(_series->begin()),
      cur_timer_(sanguis::diff_timer::parameters(_diff_clock, pos_->delay()))
{
}

sanguis::client::draw2d::sprite::animation::texture::texture(texture &&) noexcept = default;

sanguis::client::draw2d::sprite::animation::texture &
sanguis::client::draw2d::sprite::animation::texture::operator=(texture &&) noexcept = default;

sanguis::client::draw2d::sprite::animation::texture::~texture() = default;

sge::texture::const_part_ref sanguis::client::draw2d::sprite::animation::texture::current_texture()
{
  auto const handle_end(
      [this]()
      {
        switch (loop_method_)
        {
        case sanguis::client::draw2d::sprite::animation::loop_method::repeat:
          pos_ = series_.get().begin();

          cur_timer_.interval(pos_->delay());

          return;
        case sanguis::client::draw2d::sprite::animation::loop_method::stop_at_end:
          return;
        }

        FCPPT_ASSERT_UNREACHABLE;
      });

  if (cur_timer_.expired())
  {
    if (std::next(pos_) == series_.get().end())
    {
      handle_end();
    }
    else
    {
      ++pos_;

      cur_timer_.interval(pos_->delay());
    }
  }

  return fcppt::make_cref(pos_->texture());
}

bool sanguis::client::draw2d::sprite::animation::texture::ended() const
{
  return loop_method_ == sanguis::client::draw2d::sprite::animation::loop_method::stop_at_end &&
         std::next(pos_) == series_.get().end();
}
