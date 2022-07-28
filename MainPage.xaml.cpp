#include "pch.h"
#include "MainPage.xaml.h"
#if __has_include("MainPage.g.cpp")
#include "MainPage.g.cpp"
#endif

#include <winrt/Windows.ApplicationModel.DataTransfer.h>
#include <winrt/Windows.Storage.h>
#include <experimental/coroutine>
#include <coroutine>


#include <iostream>
#include <sstream>
#define DBOUT( s )            \
{                             \
   std::wostringstream os_;    \
   os_ << s;                   \
   OutputDebugString( os_.str().c_str() );  \
}

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Xaml::Controls;
using namespace Windows::ApplicationModel::DataTransfer;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Storage;



// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::drag5::implementation {
MainPage::MainPage() {
    InitializeComponent();

    auto itemCollection = single_threaded_observable_vector<IInspectable>();
    itemCollection.Append(box_value(L"123"));
    itemCollection.Append(box_value(L"456"));
    RecentFile_GridView().ItemsSource(itemCollection);

    RecentFile_GridView().Drop({ this, &MainPage::OnInputTargetPointerEntered });
}

void MainPage::OnInputTargetPointerEntered(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::DragEventArgs const& args) {
    int n = 0;
}

}

void winrt::drag5::implementation::MainPage::RecentFile_GridView_DragItemsStarting(winrt::Windows::Foundation::IInspectable const& sender,
        winrt::Microsoft::UI::Xaml::Controls::DragItemsStartingEventArgs const& e) {
    e.Data().RequestedOperation(DataPackageOperation::Copy);

    e.Data().SetDataProvider(StandardDataFormats::StorageItems(),
    [this](auto&& request) {
        DelyRenderer(request);
    });

    e.Data().OperationCompleted(
    [this](DataPackage data, OperationCompletedEventArgs const & args) {
    }
    );
}

IAsyncOperation<IVectorView<StorageFile>> PrepareFile() {
    hstring parent_dir = L"F:\\123";
    auto folder = co_await StorageFolder::GetFolderFromPathAsync(parent_dir.c_str());
    if (!folder.Path().empty()) {
        auto storage_items = co_await folder.GetFilesAsync();
        co_return storage_items;
    }
    co_return nullptr;
}

void winrt::drag5::implementation::MainPage::GridViewItemPresenter_DragStarting(winrt::Microsoft::UI::Xaml::UIElement const& sender,
        winrt::Microsoft::UI::Xaml::DragStartingEventArgs const& e) {
    e.Data().RequestedOperation(DataPackageOperation::Copy);
    e.Data().SetDataProvider(StandardDataFormats::StorageItems(),
    [this](auto&& request) {
        DelyRenderer(request);
    });
    e.Data().OperationCompleted(
    [this](DataPackage data, OperationCompletedEventArgs const & args) {
    }
    );
}

fire_and_forget winrt::drag5::implementation::MainPage::DelyRenderer(DataProviderRequest request) {
    auto deferral = request.GetDeferral();
    try {
        auto data = co_await PrepareFile(); // local file
        if (data.Size() == 0) {
            co_return;
        }

        // L"http://***.zip"
        // for example:https://codeload.github.com/microsoft/vscode/zip/refs/tags/1.69.2
        // how can i put the hypelink instead data
        request.SetData(data);
    } catch (...) {

    }
    deferral.Complete();
    co_return;
}
