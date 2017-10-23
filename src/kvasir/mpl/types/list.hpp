//          Copyright Odin Holmes 2016.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE.md or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
#pragma once
#include "../functional/bind.hpp"
namespace kvasir {
	namespace mpl {
		/// \brief universal list tspe
		template <typename... Ts>
		struct list {};
		namespace detail {
			// recursive list, for internal use only
			template <typename Head, typename Tail>
			struct rlist {};

			using rlist_tail_of8 = rlist<
			        list<>,
			        rlist<list<>,
			              rlist<list<>,
			                    rlist<list<>,
			                          rlist<list<>,
			                                rlist<list<>, rlist<list<>, rlist<list<>, void>>>>>>>>;
		} // namespace detail

		/// \brief continuation which returns its input pack wrapped in a list
		using listify = cfe<list>;

		/// \exclude
		template <typename S>
		struct sequencify;
		/// \exclude 
		template <template <typename...> class S, typename... Ts>
		struct sequencify<S<Ts...>> {
			using type = cfe<S>;
		};

		template <typename... Ts>
		list<Ts...> make_list(Ts...) {
			return {};
		}
	} // namespace mpl
} // namespace kvasir
