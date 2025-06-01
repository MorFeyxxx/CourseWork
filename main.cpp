#include <iostream>
#include "AppManager/AppManager.h"
#include "windows.h"

int main() {
    SetConsoleOutputCP(CP_UTF8);

    AppManager app;
    app.run();

    return 0;
}
