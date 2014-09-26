#ifndef SANGUIS_CLIENT_LOAD_HUD_CONTEXT_HPP_INCLUDED
#define SANGUIS_CLIENT_LOAD_HUD_CONTEXT_HPP_INCLUDED

#include <sanguis/weapon_type.hpp>
#include <sanguis/client/load/resource/textures_fwd.hpp>
#include <sanguis/client/load/hud/context_fwd.hpp>
#include <sanguis/client/load/hud/weapon_icon_map.hpp>
#include <sge/texture/part_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace client
{
namespace load
{
namespace hud
{

class context
{
	FCPPT_NONCOPYABLE(
		context
	);
public:
	explicit
	context(
		sanguis::client::load::resource::textures const &
	);

	~context();

	sge::texture::part const &
	weapon_icon(
		sanguis::weapon_type
	);
private:
	sanguis::client::load::hud::weapon_icon_map const weapon_icons_;
};

}
}
}
}

#endif
