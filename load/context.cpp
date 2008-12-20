#include "context.hpp"

sanguis::load::context::context(
	sge::image::loader_ptr const il,
	sge::renderer::device_ptr const rend,
	sge::audio::multi_loader &ml,
	sge::audio::player_ptr const ap,
	sge::audio::pool_ptr const pool)
:
	il(il),
	rend(rend),
	ml(ml),
	ap(ap),
	pool(pool)
{}

sanguis::load::context::~context()
{}
