#pragma once

#include "MainWindow.g.h"

namespace winrt::drag5::implementation {
struct MainWindow : MainWindowT<MainWindow> {
    MainWindow();


};
}

namespace winrt::drag5::factory_implementation {
struct MainWindow : MainWindowT<MainWindow, implementation::MainWindow> {
};
}
