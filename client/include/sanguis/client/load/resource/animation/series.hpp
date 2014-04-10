#ifndef SANGUIS_CLIENT_LOAD_RESOURCE_ANIMATION_SERIES_HPP_INCLUDED
#define SANGUIS_CLIENT_LOAD_RESOURCE_ANIMATION_SERIES_HPP_INCLUDED

#include <sanguis/client/load/resource/animation/series_fwd.hpp>
#include <sanguis/client/load/resource/animation/entity.hpp>
#include <sanguis/client/load/resource/animation/entity_vector.hpp>
#include <sge/renderer/dim2.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


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
public:
	typedef sanguis::client::load::resource::animation::entity_vector::const_iterator const_iterator;

	series();

	explicit
	series(
		sanguis::client::load::resource::animation::entity_vector const &
	);

	explicit
	series(
		sanguis::client::load::resource::animation::entity_vector &&
	);

	void
	push_back(
		sanguis::client::load::resource::animation::entity const &
	);

	sanguis::client::load::resource::animation::entity_vector &
	entities();

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
