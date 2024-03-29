#include <sanguis/client/draw2d/translation.hpp>
#include <sanguis/client/draw2d/unit.hpp>
#include <sanguis/client/draw2d/scene/background.hpp>
#include <sanguis/client/draw2d/scene/background_dim.hpp>
#include <sanguis/client/draw2d/scene/background_texture_coordinates.hpp>
#include <sanguis/client/draw2d/sprite/dim.hpp>
#include <sanguis/client/draw2d/sprite/point.hpp>
#include <sanguis/client/draw2d/sprite/client/category.hpp>
#include <sanguis/client/draw2d/sprite/client/object.hpp>
#include <sanguis/client/draw2d/sprite/client/system_decl.hpp> // NOLINT(misc-include-cleaner)
#include <sanguis/client/draw2d/sprite/client/system_ref.hpp>
#include <sanguis/client/load/context.hpp> // NOLINT(misc-include-cleaner)
#include <sanguis/client/load/context_cref.hpp>
#include <sanguis/client/load/resource/context.hpp>
#include <sanguis/client/load/resource/texture_identifier.hpp>
#include <sanguis/client/load/resource/textures.hpp>
#include <sge/renderer/context/core_fwd.hpp>
#include <sge/renderer/target/viewport.hpp>
#include <sge/sprite/intrusive/connection.hpp> // NOLINT(misc-include-cleaner)
#include <sge/sprite/roles/connection.hpp>
#include <sge/sprite/roles/pos.hpp>
#include <sge/sprite/roles/size.hpp>
#include <sge/sprite/roles/texture0.hpp>
#include <sge/sprite/roles/texture_coordinates0.hpp>
#include <sge/viewport/manage_callback.hpp>
#include <sge/viewport/manager.hpp> // NOLINT(misc-include-cleaner)
#include <sge/viewport/manager_ref.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/dim/to_signed.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/null.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

sanguis::client::draw2d::scene::background::background(
    sanguis::client::load::context_cref const _load_context,
    sanguis::client::draw2d::sprite::client::system_ref const _client_system,
    sge::viewport::manager_ref const _viewport_manager)
    : client_system_(_client_system),
      texture_(_load_context->resources().textures().load(
          sanguis::client::load::resource::texture_identifier(FCPPT_TEXT("background")))),
      sprite_(
          sge::sprite::roles::connection{} = client_system_->connection(
              sanguis::client::draw2d::sprite::client::category::background),
          sge::sprite::roles::pos{} =
              fcppt::math::vector::null<sanguis::client::draw2d::sprite::point>(),
          sge::sprite::roles::size{} = fcppt::math::dim::
              structure_cast<sanguis::client::draw2d::sprite::dim, fcppt::cast::size_fun>(
                  fcppt::math::dim::to_signed(
                      sanguis::client::draw2d::scene::background_dim(client_system_->renderer()))),
          sge::sprite::roles::texture0{} =
              sanguis::client::draw2d::sprite::client::object::texture_type{texture_},
          sge::sprite::roles::texture_coordinates0{} =
              sanguis::client::draw2d::scene::background_texture_coordinates(
                  sanguis::client::draw2d::translation(
                      fcppt::math::vector::null<
                          sanguis::client::draw2d::translation::value_type>()),
                  client_system_->renderer(),
                  texture_)),
      viewport_connection_(_viewport_manager->manage_callback(sge::viewport::manage_callback{
          [this](sge::renderer::target::viewport const &) { this->reset_viewport(); }}))
{
}

FCPPT_PP_POP_WARNING

sanguis::client::draw2d::scene::background::~background() = default;

void sanguis::client::draw2d::scene::background::render(
    sge::renderer::context::core &_render_context,
    sanguis::client::draw2d::translation const &_translation)
{
  sprite_.texture_coordinates(sanguis::client::draw2d::scene::background_texture_coordinates(
      sanguis::client::draw2d::translation{
          (_translation.get() / fcppt::literal<sanguis::client::draw2d::unit>(2)).get_unsafe()},
      client_system_->renderer(),
      texture_));

  client_system_->render(
      _render_context, sanguis::client::draw2d::sprite::client::category::background);
}

void sanguis::client::draw2d::scene::background::reset_viewport()
{
  sprite_.size(
      fcppt::math::dim::structure_cast<sanguis::client::draw2d::sprite::dim, fcppt::cast::size_fun>(
          fcppt::math::dim::to_signed(
              sanguis::client::draw2d::scene::background_dim(client_system_->renderer()))));
}
