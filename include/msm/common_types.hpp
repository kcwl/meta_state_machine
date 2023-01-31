#pragma once


namespace msm
{
	enum class Handle
	{
		Handle_False = 0,
		Handle_True = 1,
		Handle_Guard_Reject = 2,
		Handle_Deferred = 4
	};

	using execute_t = Handle;
}