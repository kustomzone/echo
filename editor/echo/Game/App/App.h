#pragma once

#include <Engine/core/main/Root.h>
#include "Log.h"

namespace Game
{
	class App
	{
	public:
		App();
		~App();

		// init
		void init(HWND hwnd, const Echo::String& echoProject);

		// tick
		void tick(Echo::ui32 elapsedTime);

		// onSize
		void onSize(Echo::ui32 width, Echo::ui32 height);

	private:
		Echo::Root*		m_root;
		GameLog*		m_log;
	};
}