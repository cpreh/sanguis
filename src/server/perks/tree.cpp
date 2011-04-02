#include "tree.hpp"
#include "../log.hpp"
#include "../../exception.hpp"
#include <fcppt/container/tree/object_impl.hpp>
#include <fcppt/container/tree/pre_order.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/foreach_enumerator.hpp>
#include <fcppt/text.hpp>

namespace
{

struct perk_equal
{
	explicit perk_equal(
		sanguis::perk_type::type
	);
	
	bool
	operator()(
		sanguis::server::perks::tree::tree_type const &
	) const;
private:
	sanguis::perk_type::type type_;
};

}

sanguis::server::perks::tree::tree()
:
	impl_(
		perks::status()
	)
{
	// TODO: do this with assign::
	impl_.push_back(
		perks::status(
			perk_type::choleric,
			perks::required_player_level(
				2
			),
			perks::required_parent_level(
				0
			)
		)
	);
	impl_.push_back(
		perks::status(
			perk_type::ias,
			perks::required_player_level(
				0
			),
			perks::required_parent_level(
				0
			)
		)
	);
	impl_.push_back(
		perks::status(
			perk_type::ims,
			perks::required_player_level(
				0
			),
			perks::required_parent_level(
				0
			)
		)
	);
	impl_.push_back(
		perks::status(
			perk_type::irs,
			perks::required_player_level(
				0
			),
			perks::required_parent_level(
				0
			)
		)
	);
	impl_.push_back(
		perks::status(
			perk_type::health,
			perks::required_player_level(
				0
			),
			perks::required_parent_level(
				0
			)
		)
	);

	tree_type &health(
		impl_.back()
	);

	health.push_back(
		perks::status(
			perk_type::regeneration,
			perks::required_player_level(
				0
			),
			perks::required_parent_level(
				2
			)
		)
	);
}

sanguis::server::perks::tree::~tree()
{}

bool
sanguis::server::perks::tree::choosable(
	perk_type::type const _perk,
	server::level const _player_level
) const
{
	if(
		_perk == perk_type::size
	)
		return false;

	typedef 
	fcppt::container::tree::pre_order<
		tree_type const
	> traversal;
	
	traversal trav(
		impl_
	);
	
	traversal::iterator const it(
		std::find_if(
			trav.begin(),
			trav.end(),
			::perk_equal(
				_perk
			)
		)
	);
	
	if(
		it == trav.end()
	)
	{
		FCPPT_LOG_WARNING(
			server::log(),
			fcppt::log::_
				<< FCPPT_TEXT("Perk not found in tree")
		);

		return false;
	}

	if(
		it->value().required_player_level().get()
		>
		_player_level.get()
	)
		return false;

	for(
		tree_type const *pos(&*it);
		pos->has_parent();
		pos = &pos->parent()
	)
	{
		perks::status const &cur_status(
			pos->value()
		);

		if(
			cur_status.required_parent_level().get()
			> pos->parent().value().level().get()
		)
			return false;
	}

	return true;
}

void
sanguis::server::perks::tree::take(
	perk_type::type const _perk
)
{
	typedef 
	fcppt::container::tree::pre_order<
		tree_type
	> traversal;
	
	traversal trav(
		impl_
	);
	
	traversal::iterator const it(
		std::find_if(
			trav.begin(),
			trav.end(),
			::perk_equal(
				_perk
			)
		)
	);
	
	if(
		it == trav.end()
	)
		throw sanguis::exception(
			FCPPT_TEXT("Perk not found in the tree!")
		);
	
	(*it).value().choose();
}

sanguis::server::perks::list const
sanguis::server::perks::tree::choosables(
	server::level const _player_level
) const
{
	// TODO: very wasteful but easy
	list ret;

	FCPPT_FOREACH_ENUMERATOR(
		perk,
		perk_type
	)
	{
		if(
			this->choosable(
				perk,
				_player_level
			)
		)
			ret.push_back(
				perk
			);
	}

	return ret;
}

namespace
{

perk_equal::perk_equal(
	sanguis::perk_type::type const _type
)
:
	type_(_type)
{
}
	
bool
perk_equal::operator()(
	sanguis::server::perks::tree::tree_type const &_tree
) const
{
	return _tree.value().type() == type_;
}

}
