#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_TEXT_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_TEXT_HPP_INCLUDED

#include <sanguis/diff_clock_cref.hpp>
#include <sanguis/diff_timer.hpp>
#include <sanguis/client/draw2d/z_ordering_fwd.hpp>
#include <sanguis/client/draw2d/entities/own.hpp>
#include <sanguis/client/draw2d/sprite/center.hpp>
#include <sanguis/client/draw2d/sprite/normal/color_fwd.hpp>
#include <sanguis/client/draw2d/sprite/normal/object_decl.hpp>
#include <sanguis/client/draw2d/sprite/normal/system_ref.hpp>
#include <sge/font/object_fwd.hpp>
#include <sge/font/string.hpp>
#include <sge/font/text_unique_ptr.hpp>
#include <sge/texture/const_part_unique_ptr.hpp>
#include <fcppt/nonmovable.hpp>


namespace sanguis::client::draw2d::entities
{

class text
:
	public sanguis::client::draw2d::entities::own
{
	FCPPT_NONMOVABLE(
		text
	);
public:
	text(
		sanguis::diff_clock_cref,
		sanguis::client::draw2d::sprite::normal::system_ref,
		sge::font::object &, // NOLINT(google-runtime-references)
		sge::font::string const &,
		sanguis::client::draw2d::z_ordering,
		sanguis::client::draw2d::sprite::center const &,
		sanguis::client::draw2d::sprite::normal::color
	);

	~text()
	override;
private:
	text(
		sanguis::diff_clock_cref,
		sanguis::client::draw2d::sprite::normal::system_ref,
		sge::font::text_unique_ptr &&,
		sanguis::client::draw2d::z_ordering,
		sanguis::client::draw2d::sprite::center const &,
		sanguis::client::draw2d::sprite::normal::color
	);

	void
	update()
	override;

	[[nodiscard]]
	bool
	may_be_removed() const
	override;

	sanguis::diff_timer life_time_;

	sge::texture::const_part_unique_ptr const texture_;

	sanguis::client::draw2d::sprite::normal::object sprite_;

	sanguis::client::draw2d::sprite::center const origin_;
};

}

#endif
