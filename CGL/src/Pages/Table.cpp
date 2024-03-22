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
	tableClass.lpfnWndProc = this->TableProc;
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

	if (this->TableWnd == INVALID_HANDLE_VALUE)
		throw runtime_error("Unable to create main window"s);
}

void Table::createNativeControls()
{
	this->GoBackButton = CreateWindowExW(0l, WC_BUTTONW, L"Вернуться назад", WS_VISIBLE | WS_CHILD | ES_CENTER,
		10, 10, 150, 25, this->TableWnd,
		reinterpret_cast<HMENU>(Table::PageInteraction::GoBackClicked), nullptr, nullptr);

	static double a = -3.14159265358979323846, b = 3.14159265358979323846, n = 20;
	vector<vector<double>> tableData = TbHelper::getVectorDatas(a, b, n);
	wstring header[5]{ L"X", L"F1", L"F2", L"Sum", L"Mean" };
	int const textMaxLen = 10;

	this->CreateListView();
	this->SetListViewColumns(5, textMaxLen, header);

	for(vector<double> data : tableData)
		this->AddListViewItems(5, textMaxLen, data);
}

LRESULT CALLBACK Table::TableProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	Table* hTable;
	if (uMsg == WM_CREATE)
	{
		hTable = static_cast<Table*>(reinterpret_cast<CREATESTRUCT*>(lParam)->lpCreateParams);
		SetLastError(0);
		if (!SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(hTable)))
			if (GetLastError() != 0)
				return false;
	}
	else
	{
		hTable = reinterpret_cast<Table*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
	}

	if (hTable)
	{
		hTable->TableWnd = hwnd;
		return hTable->windowProc(hwnd, uMsg, wParam, lParam);
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

LRESULT CALLBACK Table::windowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) 
	{
		case WM_COMMAND:
		{
			return this->handleCommand(hwnd, uMsg, wParam, lParam);
		}
		case WM_SIZE:
		{
			RECT rcl{};

			GetWindowRect(hwnd, &rcl);
			SetWindowPos(this->hListView, HWND_TOP, 0, 0, rcl.right - rcl.left, rcl.bottom - rcl.top - 50, SWP_NOZORDER | SWP_NOMOVE);
			return UpdateWindow(hwnd);
		}
		case WM_NOTIFY: 
		{

			LPNMLISTVIEW pnm = (LPNMLISTVIEW)lParam;

			if (pnm->hdr.hwndFrom == this->hListView && pnm->hdr.code == NM_CUSTOMDRAW) {

				return ProcessCustomDraw(pnm->hdr.hwndFrom, uMsg, wParam, lParam);

			}
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
		}
		case WM_CLOSE:
		{						// App::ButtonsInteraction::DestroyClicked
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
}

LRESULT Table::ProcessCustomDraw(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LPNMLVCUSTOMDRAW lplvcd = (LPNMLVCUSTOMDRAW)lParam;

	switch (lplvcd->nmcd.dwDrawStage) 
	{
		case CDDS_PREPAINT: 
		{ //Before the paint cycle begins
			return CDRF_NOTIFYITEMDRAW;
		}
		case CDDS_ITEMPREPAINT: 
		{ //Before an item is drawn
			return CDRF_NOTIFYSUBITEMDRAW;
		}
		case CDDS_SUBITEM | CDDS_ITEMPREPAINT: 
		{ //Before a subitem is drawn
			if (lplvcd->iSubItem == 4)
			{
				lplvcd->clrTextBk = RGB(103, 63, 105);
			}
			else if (lplvcd->iSubItem == 3)
			{
				lplvcd->clrTextBk = RGB(87, 85, 254);
			}
			return CDRF_NEWFONT;
		}
		default:
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
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
		WS_CHILD | LVS_REPORT | WS_VISIBLE,
		0, 40, rcl.right - rcl.left, rcl.bottom - rcl.top - 50,
		this->TableWnd, nullptr, nullptr, nullptr);
}

void Table::ShowHWND(int nCmdShow) const
{
	ShowWindow(this->TableWnd, nCmdShow);
	UpdateWindow(this->TableWnd);
}