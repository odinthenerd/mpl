//          Copyright Odin Holmes 2016.
// Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE.md or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
#pragma once

#include "../algorithm/find_if.hpp"
#include "../functional/bind.hpp"
#include "../functional/call.hpp"
#include "../functional/identity.hpp"
#include "../types/bool.hpp"
#include <initializer_list>

namespace kvasir {
	namespace mpl {
		namespace c {
			namespace detail {
				struct nothing_found {
					template <typename... Ts>
					struct f {
						constexpr static bool value = (sizeof...(Ts) == 0);
					};
				};
				template <typename F>
				struct not_ {
					template <typename T>
					struct f {
						constexpr static bool value = (!(F::template f<T>::value));
					};
				};
				template <template <typename...> class F>
				struct not_<cfe<F,identity>> {
					template <typename T>
					struct f {
						constexpr static bool value = (!F<T>::value);
					};
				};
			}
#if defined(KVASIR_CONSTEXPR_14)
			namespace detail{
				constexpr int and_(std::initializer_list<bool> l) {
					bool out = true;
					for (auto i : l) {
						out = out && i;
					}
					return out;
				}
			}
			template<typename F>
			struct all {
				template<typename...Ts>
				using f = bool_<detail::and_({ static_cast<bool>(conditional<(sizeof...(Ts)<100000)>::template f<F, void>::template f<Ts>::value)... })>;
			};
			template <template <typename...> class F>
			struct all<cfe<F, identity>> {
				template<typename...Ts>
				using f = bool_<detail::and_({ static_cast<bool>(F<Ts>::value)... })>;
			};

#else
			template <typename F>
			using all = find_if<detail::not_<F>, detail::nothing_found>;
#endif
		}

		/// resolves to std::true_type if all elements in the input list
		/// fulfill the provided predicate
		template <typename List, template <typename...> class Cond = identity>
		using all = c::call<c::all<c::cfe<Cond>>, List>;
	}
}
