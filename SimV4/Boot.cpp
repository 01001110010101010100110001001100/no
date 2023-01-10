#include "AppW.h"

int main() {
	AppW app;
	if (app.init()) {
		while (app.isRun()) {
			app.broadcast();
		}
	}
	return 0;
}