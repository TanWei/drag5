#pragma once

#include "MainPage.g.h"

namespace winrt::drag5::implementation {
struct MainPage : MainPageT<MainPage> {
    MainPage();

    static fire_and_forget DelyRenderer(winrt::Windows::ApplicationModel::DataTransfer::DataProviderRequest request);

    void OnInputTargetPointerEntered(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::DragEventArgs const& args);
    void RecentFile_GridView_DragItemsStarting(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::DragItemsStartingEventArgs const& e);
    void GridViewItemPresenter_DragStarting(winrt::Microsoft::UI::Xaml::UIElement const& sender, winrt::Microsoft::UI::Xaml::DragStartingEventArgs const& args);
};
}

namespace winrt::drag5::factory_implementation {
struct MainPage : MainPageT<MainPage, implementation::MainPage> {
};
}
