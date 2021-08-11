#include "Utils.h"
#include "Config.h"
#include "System.h"

int main(int argc, char** argv)
{
	// setup console
	SetConsoleCP(GetACP());
	SetConsoleOutputCP(GetACP());

	LOG << "Start application" << std::endl;

	Config config(argc, argv);

	LOG << "Window pos: " << config.GetWindowPos() << std::endl;
	LOG << "Window size: " << config.GetWindowSize() << std::endl;

	System system(config);
	if (system.Initialize())
		system.Run();
	system.Shutdown();

	LOG << "Finish application" << std::endl;

	return 0;
}