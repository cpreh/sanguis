#include <sanguis/collision/center.hpp>
#include <sanguis/collision/exception.hpp>
#include <sanguis/collision/radius.hpp>
#include <sanguis/collision/impl/collides.hpp>
#include <sanguis/collision/impl/world/make_circle.hpp>
#include <sanguis/collision/impl/world/simple/body.hpp>
#include <sanguis/collision/impl/world/simple/ghost.hpp>
#include <sanguis/collision/impl/world/simple/ghost_remove_callback.hpp>
#include <sanguis/collision/world/body_enter.hpp>
#include <sanguis/collision/world/body_exit.hpp>
#include <sanguis/collision/world/body_exit_container.hpp>
#include <sanguis/collision/world/created.hpp>
#include <sanguis/collision/world/ghost.hpp>
#include <sanguis/collision/world/ghost_group.hpp>
#include <sanguis/collision/world/ghost_parameters.hpp>
#include <sanguis/collision/world/optional_body_enter.hpp>
#include <sanguis/collision/world/optional_body_exit.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/not.hpp>
#include <fcppt/reference_comparison.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/reference_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/map_iteration.hpp>
#include <fcppt/algorithm/update_action.hpp>
#include <fcppt/container/find_opt_iterator.hpp>
#include <fcppt/container/find_opt_mapped.hpp>
#include <fcppt/optional/map.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

sanguis::collision::impl::world::simple::ghost::ghost(
    sanguis::collision::world::ghost_parameters const &_parameters,
    sanguis::collision::impl::world::simple::ghost_remove_callback &&_ghost_remove_callback)
    : sanguis::collision::world::ghost{},
      ghost_remove_callback_(std::move(_ghost_remove_callback)),
      radius_(_parameters.radius()),
      collision_group_(_parameters.collision_group()),
      center_(_parameters.center()),
      ghost_base_(_parameters.ghost_base()),
      bodies_()
{
}

sanguis::collision::impl::world::simple::ghost::~ghost() { ghost_remove_callback_(*this); }

void sanguis::collision::impl::world::simple::ghost::center(
    sanguis::collision::center const _center)
{
  center_ = _center;
}

sanguis::collision::center sanguis::collision::impl::world::simple::ghost::center() const
{
  return center_;
}

sanguis::collision::radius sanguis::collision::impl::world::simple::ghost::radius() const
{
  return radius_;
}

sanguis::collision::world::ghost_group
sanguis::collision::impl::world::simple::ghost::collision_group() const
{
  return collision_group_;
}

void sanguis::collision::impl::world::simple::ghost::pre_update_bodies()
{
  for (auto &body : bodies_)
  {
    body.second = body_status::marked_for_deletion;
  }
}

sanguis::collision::world::body_exit_container
sanguis::collision::impl::world::simple::ghost::post_update_bodies()
{
  sanguis::collision::world::body_exit_container result;

  fcppt::algorithm::map_iteration(
      bodies_,
      [this, &result](body_map::value_type const &_element)
      {
        if (_element.second == body_status::marked_for_deletion)
        {
          // NOLINTNEXTLINE(hicpp-use-emplace,modernize-use-emplace)
          result.push_back(sanguis::collision::world::body_exit(
              fcppt::make_ref(_element.first.get().body_base()), fcppt::make_ref(ghost_base_)));

          return fcppt::algorithm::update_action::remove;
        }

        return fcppt::algorithm::update_action::keep;
      });

  return result;
}

sanguis::collision::world::optional_body_enter
sanguis::collision::impl::world::simple::ghost::update_near_body(
    sanguis::collision::impl::world::simple::body const &_body)
{
  return sanguis::collision::impl::collides(
             sanguis::collision::impl::world::make_circle(_body),
             sanguis::collision::impl::world::make_circle(*this))
             ? fcppt::optional::maybe(
                   fcppt::container::find_opt_mapped(bodies_, fcppt::make_cref(_body)),
                   [this, &_body]
                   {
                     bodies_.insert(std::make_pair(fcppt::make_cref(_body), body_status::normal));

                     return sanguis::collision::world::optional_body_enter(
                         sanguis::collision::world::body_enter(
                             fcppt::make_ref(_body.body_base()),
                             fcppt::make_ref(ghost_base_),
                             sanguis::collision::world::created{false}));
                   },
                   [](fcppt::reference<body_status> const _status)
                   {
                     _status.get() = body_status::normal;

                     return sanguis::collision::world::optional_body_enter();
                   })
             : sanguis::collision::world::optional_body_enter();
}

sanguis::collision::world::optional_body_enter
sanguis::collision::impl::world::simple::ghost::new_body(
    sanguis::collision::impl::world::simple::body const &_body,
    sanguis::collision::world::created const _created)
{
  if (!sanguis::collision::impl::collides(
          sanguis::collision::impl::world::make_circle(_body),
          sanguis::collision::impl::world::make_circle(*this)))
  {
    return sanguis::collision::world::optional_body_enter();
  }

  if (fcppt::not_(this->bodies_.insert(std::make_pair(fcppt::make_cref(_body), body_status::normal))
                      .second))
  {
    throw sanguis::collision::exception{FCPPT_TEXT("Body double insert!")};
  }

  return sanguis::collision::world::optional_body_enter(sanguis::collision::world::body_enter{
      fcppt::make_ref(_body.body_base()), fcppt::make_ref(ghost_base_), _created});
}

sanguis::collision::world::optional_body_exit
sanguis::collision::impl::world::simple::ghost::remove_body(
    sanguis::collision::impl::world::simple::body const &_body)
{
  return fcppt::optional::map(
      fcppt::container::find_opt_iterator(bodies_, fcppt::make_cref(_body)),
      [this, &_body](sanguis::collision::impl::world::simple::ghost::body_map::iterator const _it)
      {
        bodies_.erase(_it);

        return sanguis::collision::world::body_exit(
            fcppt::make_ref(_body.body_base()), fcppt::make_ref(ghost_base_));
      });
}

void sanguis::collision::impl::world::simple::ghost::body_destroyed(
    sanguis::collision::impl::world::simple::body const &_body)
{
  bodies_.erase(fcppt::make_cref(_body));
}
