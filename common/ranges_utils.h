#include <range/v3/all.hpp>

template<ranges::input_range Rng, typename F, typename P = ranges::identity>
	requires ranges::indirect_unary_predicate<F, ranges::projected<ranges::iterator_t<Rng>, P>>
auto find_val_if(Rng&& rng, F pred, P proj = P{})
{
	return *ranges::find_if(begin(rng), end(rng), std::move(pred), std::move(proj));
}

auto index_of(ranges::input_range auto&& rng, const auto& value)
{
	return ranges::distance(rng | ranges::views::take_while([&value](auto&& v) { return v != value; }));
}

template<ranges::input_range Rng, typename F>
	requires ranges::indirect_unary_predicate<F, ranges::iterator_t<Rng>>
auto index_of_if(Rng&& rng, F pred)
{
	return ranges::distance(rng | ranges::views::take_while(std::not_fn(std::move(pred))));
}
