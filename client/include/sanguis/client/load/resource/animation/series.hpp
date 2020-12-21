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
	using
	const_iterator
	=
	sanguis::client::load::resource::animation::entity_vector::const_iterator;

	explicit
	series(
		sanguis::client::load::resource::animation::entity_vector &&
	);

	series(
		series &&
	)
	noexcept;

	series &
	operator=(
		series &&
	)
	noexcept;

	~series();

	[[nodiscard]]
	sanguis::client::load::resource::animation::entity_vector const &
	entities() const;

	[[nodiscard]]
	const_iterator
	begin() const;

	[[nodiscard]]
	const_iterator
	end() const;
private:
	sanguis::client::load::resource::animation::entity_vector entities_;
};

}
}
}
}
}

#endif
