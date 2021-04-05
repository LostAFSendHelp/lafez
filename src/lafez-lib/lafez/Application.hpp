#pragma once
#include <lafezlib_export.h>

namespace Lafez {
	class LAFEZLIB Application {
	public:
		virtual ~Application();

		virtual void startUp() = 0;
		virtual void run() = 0;
		virtual void shutDown() = 0;

	protected:
		Application();
	};

	Application* createApplication();
};