#include "base.hpp"

sanguis::server::collision::base::base(
	sge::collision::objects::circle_ptr const circle_)
:
	circle_(circle_)
{}

sanguis::server::collision::base::~base()
{}
