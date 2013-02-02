#ifndef SANGUIS_LOAD_MODEL_OBJECT_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_OBJECT_HPP_INCLUDED

#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/load/model/object_fwd.hpp>
#include <sanguis/load/model/part_fwd.hpp>
#include <sanguis/load/resource/context_fwd.hpp>
#include <sge/renderer/dim2.hpp>
#include <fcppt/random/variate_fwd.hpp>
#include <fcppt/random/distribution/uniform_int_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/scoped_ptr_impl.hpp>
#include <fcppt/string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/ptr_container/ptr_map.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace load
{
namespace model
{

class object
{
	typedef boost::ptr_map<
		fcppt::string,
		sanguis::load::model::part
	> part_map;

	FCPPT_NONCOPYABLE(
		object
	);
public:
	typedef part_map::value_type value_type;

	typedef part_map::const_reference const_reference;

	typedef part_map::const_iterator const_iterator;

	typedef part_map::size_type size_type;

	~object();

	sanguis::load::model::part const &
	operator[](
		fcppt::string const &
	) const;

	sanguis::load::model::part const &
	random_part() const;

	size_type
	size() const;

	const_iterator
	begin() const;

	const_iterator
	end() const;

	sge::renderer::dim2 const
	dim() const;

	object(
		boost::filesystem::path const &,
		sanguis::load::resource::context const &,
		sanguis::random_generator &
	);
private:
	void
	construct(
		sanguis::load::resource::context const &
	);

	friend class collection;

	boost::filesystem::path const path_;

	sanguis::random_generator &random_generator_;

	sge::renderer::dim2 cell_size_;

	part_map parts_;

	typedef fcppt::random::distribution::uniform_int<
		part_map::size_type
	> part_map_distribution;

	typedef fcppt::random::variate<
		sanguis::random_generator,
		part_map_distribution
	> part_rand;

	mutable fcppt::scoped_ptr<
		part_rand
	> random_part_;
};

}
}
}

#endif
