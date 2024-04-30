#include <Windows.h>
#include <commctrl.h>
#include "headers/Table.h"

Table::Table(HWND& mnHwnd, HINSTANCE& hInstance)
{
	this->mnWnd = mnHwnd;
	this->hInstance = hInstance;

	this->initNativeObj();
	this->createNativeControls();
}
void Table::initNativeObj()
{
	WNDCLASSEXW tableClass{ sizeof(WNDCLASSEXW) };

	tableClass.cbClsExtra = 0;
	tableClass.cbWndExtra = 0;
	tableClass.hbrBackground = reinterpret_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	tableClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
	tableClass.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	tableClass.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);
	tableClass.hInstance = this->hInstance;
	tableClass.lpfnWndProc = this->windowProc;
	tableClass.lpszClassName = this->ClassName.c_str();
	tableClass.lpszMenuName = nullptr;
	tableClass.style = 0;

	RegisterClassExW(&tableClass);

	this->TableWnd = CreateWindowExW(0L, tableClass.lpszClassName, this->AppName.c_str(),
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		(GetSystemMetrics(SM_CXSCREEN) - this->widht) / 2u,
		(GetSystemMetrics(SM_CYSCREEN) - this->height) / 2u,
		this->widht, this->height,
		this->mnWnd, nullptr, this->hInstance, this);
}
void Table::createNativeControls()
{
	this->GoBackButton = CreateWindowExW(0l, WC_BUTTONW, L"Вернуться назад", WS_VISIBLE | WS_CHILD | ES_CENTER,
		10, 10, 150, 25, this->TableWnd,
		reinterpret_cast<HMENU>(Table::PageInteraction::GoBackClicked), nullptr, nullptr);

	static double a = -3.14159265358979323846, b = 3.14159265358979323846, n = 20;
	this->tableData = TbHelper::getVectorDatas(a, b, n);
	this->minMaxData = TbHelper::getMinMaxData(this->tableData);
	wstring header[5]{ L"X", L"F1", L"F2", L"Sum", L"Mean" };
	int const textMaxLen = 10;

	this->CreateListView();
	this->SetListViewColumns(5, textMaxLen, header);

	for(vector<double> data : this->tableData)
		this->AddListViewItems(5, textMaxLen, data);

	this->AddConcreteListViewItem(5, textMaxLen, minMaxData[0]);
	this->AddConcreteListViewItem(5, textMaxLen, minMaxData[1]);
}
LRESULT CALLBACK Table::windowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) 
	{
		case WM_COMMAND:
		{
			return this->handleCommand(hwnd, uMsg, wParam, lParam);
		}
		case WM_NOTIFY: 
		{
			LPNMHDR nmhdr = (LPNMHDR)lParam;
			if (nmhdr->code == NM_CUSTOMDRAW)
			{
				LPNMLVCUSTOMDRAW lvcd = (LPNMLVCUSTOMDRAW)lParam;
				if (lvcd->nmcd.dwDrawStage == CDDS_PREPAINT)
				{
					SetWindowLongPtr(hwnd, DWLP_MSGRESULT, CDRF_NOTIFYITEMDRAW);
					return CDRF_NOTIFYITEMDRAW;
				}
				else if (lvcd->nmcd.dwDrawStage == CDDS_ITEMPREPAINT)
				{
					int index = lvcd->nmcd.dwItemSpec;
					int subItemIndex = lvcd->iSubItem;

					if (index == ListView_GetItemCount(this->hListView) - 2)
						lvcd->clrTextBk = RGB(112, 66, 100);
					if (index == ListView_GetItemCount(this->hListView) - 1)
						lvcd->clrTextBk = RGB(187, 132, 147);
				}
			}
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
		}
		case WM_CLOSE:
		{
			SendMessage(this->mnWnd, WM_COMMAND, LOWORD(1555), reinterpret_cast<LPARAM>(this->TableWnd));
			return TRUE;
		}
		default:
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
			break;
	}
}
LRESULT CALLBACK Table::handleCommand(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) const
{
	switch (static_cast<Table::PageInteraction>(LOWORD(wParam)))
	{
		case Table::PageInteraction::GoBackClicked:
		{						// App::ButtonsInteraction::DestroyClicked
			SendMessage(this->mnWnd, WM_COMMAND, LOWORD(1555), reinterpret_cast<LPARAM>(this->TableWnd));

			return TRUE;
		}
		default:
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return TRUE;
}
BOOL WINAPI Table::AddListViewItems(int colNum, int textMaxLen, std::vector<double> item) const
{
	int iLastIndex = ListView_GetItemCount(this->hListView);

	std::wstring temp = std::to_wstring(item[0]);

	LVITEM lvi{};
	lvi.mask = LVIF_TEXT;
	lvi.cchTextMax = textMaxLen;
	lvi.iItem = iLastIndex;
	lvi.pszText = (wchar_t*)temp.c_str();
	lvi.iSubItem = 0;

	if (ListView_InsertItem(this->hListView, &lvi) == -1)
		return FALSE;
	for (int i = 1; i < colNum; i++)
	{
		temp = std::to_wstring(item[i]);
		ListView_SetItemText(this->hListView, iLastIndex, i, (wchar_t*)temp.c_str());
	}

	return TRUE;
}
BOOL WINAPI Table::AddConcreteListViewItem(int colNum, int textMaxLen, std::vector<wstring> item) const
{
	int iLastIndex = ListView_GetItemCount(this->hListView);


	LVITEM lvi{};
	lvi.mask = LVIF_TEXT;
	lvi.cchTextMax = textMaxLen;
	lvi.iItem = iLastIndex;
	lvi.pszText = (wchar_t*)item[0].c_str();
	lvi.iSubItem = 0;

	if (ListView_InsertItem(this->hListView, &lvi) == -1)
		return FALSE;
	for (int i = 1; i < colNum; i++)
	{
		ListView_SetItemText(this->hListView, iLastIndex, i, (wchar_t*)item[i].c_str());
	}

	return TRUE;
}
int Table::SetListViewColumns(int colNum, int textMaxLen, wstring header[5]) const
{
	RECT rcl;
	GetClientRect(this->hListView, &rcl);

	int index = -1;

	LVCOLUMN lvc{};
	lvc.mask = LVCF_TEXT | LVCF_WIDTH;
	lvc.cx = (rcl.right - rcl.left) / colNum;
	lvc.cchTextMax = textMaxLen;

	for (int i = 0; i < colNum; i++)
	{
		lvc.pszText = (wchar_t*)header[i].c_str();
		index = ListView_InsertColumn(this->hListView, i, &lvc);
		if (index == -1) break;
	}

	return index;
}
void Table::CreateListView()
{
	RECT rcl;
	GetClientRect(this->TableWnd, &rcl);

	this->hListView = CreateWindowExW(0L, WC_LISTVIEW, L"",
		WS_CHILD | LVS_REPORT | WS_VISIBLE | SWP_HIDEWINDOW,
		0, 40, rcl.right - rcl.left, rcl.bottom - rcl.top - 50,
		this->TableWnd, nullptr, nullptr, nullptr);
}
void Table::ShowHWND(int nCmdShow) const
{
	ShowWindow(this->TableWnd, nCmdShow);
	UpdateWindow(this->TableWnd);
}