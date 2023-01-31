#pragma once
#include <tuple>

namespace msm
{
	namespace back
	{
		template<typename... _Args>
		struct dispatch_table
		{
			using type = std::tuple<_Args...>;
		};

		template<typename _Event, typename _Tuple>
		struct find_by;

		template<typename _Event>
		struct find_by<_Event, std::tuple<>>
		{
			using type = std::tuple<>;

			//static_assert(false, "out of index!");
		};

		template<typename _Event, typename _This, typename... _Args>
		requires(std::same_as<_Event, typename _This::event_type>)
		struct find_by<_Event, std::tuple<_This, _Args...>>
		{
			using type = _This;
		};

		template<typename _Event, typename _This, typename... _Args>
		struct find_by<_Event, std::tuple<_This, _Args...>> : find_by<_Event, std::tuple<_Args...>> {};
	}
}