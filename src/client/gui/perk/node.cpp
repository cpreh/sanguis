#include "node.hpp"
#include <fcppt/variant/apply_unary.hpp>
#include <fcppt/nonassignable.hpp>
#include <elements/CEGUITreeItem.h>
#include <elements/CEGUITree.h>

namespace
{

class add_visitor
{
	FCPPT_NONASSIGNABLE(
		add_visitor
	);
public:
	explicit add_visitor(
		CEGUI::TreeItem &	
	);

	typedef void result_type;

	template<
		typename T
	>
	result_type
	operator()(
		T
	) const;
private:
	CEGUI::TreeItem &item_;
};

struct remove_visitor
{
	FCPPT_NONASSIGNABLE(
		remove_visitor
	);
public:
	explicit remove_visitor(
		CEGUI::TreeItem &	
	);

	typedef void result_type;

	template<
		typename T
	>
	result_type
	operator()(
		T
	) const;
private:
	CEGUI::TreeItem &item_;
};

}

sanguis::client::gui::perk::node::node(
	gui::perk::node_variant const &_impl
)
:
	impl_(_impl)
{
}

void
sanguis::client::gui::perk::node::add_item(
	CEGUI::TreeItem &_item
) const
{
	fcppt::variant::apply_unary(
		add_visitor(
			_item
		),
		impl_
	);
}

void
sanguis::client::gui::perk::node::remove_item(
	CEGUI::TreeItem &_item
) const
{
	fcppt::variant::apply_unary(
		remove_visitor(
			_item
		),
		impl_
	);
}

namespace
{

add_visitor::add_visitor(
	CEGUI::TreeItem &_item
)
:
	item_(_item)
{
}

template<
	typename T
>
add_visitor::result_type
add_visitor::operator()(
	T const _ptr
) const
{
	_ptr->addItem(
		&item_
	);
}

remove_visitor::remove_visitor(
	CEGUI::TreeItem &_item
)
:
	item_(_item)
{
}

template<
	typename T
>
remove_visitor::result_type
remove_visitor::operator()(
	T const _ptr
) const
{
	_ptr->removeItem(
		&item_
	);
}

}
