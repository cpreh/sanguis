#ifndef SANGUIS_CLIENT_LOAD_RESOURCE_ANIMATION_SERIES_HPP_INCLUDED
#define SANGUIS_CLIENT_LOAD_RESOURCE_ANIMATION_SERIES_HPP_INCLUDED

#include <sanguis/client/load/resource/animation/entity.hpp>
#include <sanguis/client/load/resource/animation/entity_vector.hpp>
#include <sanguis/client/load/resource/animation/series_fwd.hpp>
#include <sge/renderer/dim2.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace client
{
namespace load
{
namespace resource
{
namespace animation
{

class series
{
	FCPPT_NONCOPYABLE(
		series
	);
public:
	typedef sanguis::client::load::resource::animation::entity_vector::const_iterator const_iterator;

	explicit
	series(
		sanguis::client::load::resource::animation::entity_vector &&
	);

	series(
		series &&
	);

	series &
	operator=(
		series &&
	);

	~series();

	sanguis::client::load::resource::animation::entity_vector const &
	entities() const;

	const_iterator
	begin() const;

	const_iterator
	end() const;

	bool
	empty() const;
private:
	sanguis::client::load::resource::animation::entity_vector entities_;
};

}
}
}
}
}

#endif
