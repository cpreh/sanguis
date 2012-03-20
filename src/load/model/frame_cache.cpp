#include <sanguis/load/model/frame_cache.hpp>
#include <fcppt/math/box/object_impl.hpp>

void sanguis::load::model::frame_cache::push_back(
	frame_cache_value const &v)
{
	values_.push_back(
		v);
}

sanguis::load::model::frame_cache::const_iterator sanguis::load::model::frame_cache::begin() const
{
	return values_.begin();
}

sanguis::load::model::frame_cache::const_iterator sanguis::load::model::frame_cache::end() const
{
	return values_.end();
}

bool sanguis::load::model::frame_cache::empty() const
{
	return values_.empty();
}
