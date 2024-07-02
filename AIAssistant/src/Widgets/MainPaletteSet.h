#pragma once

class ChatPalette;

/// @brief 子面板容器类
class MainPaletteSet : public CAdUiPaletteSet
{
	DECLARE_DYNAMIC(MainPaletteSet)
public:
	MainPaletteSet();
	virtual ~MainPaletteSet();

public:
	bool Create(CWnd* pwndParent);
	void close();

protected:
	virtual void GetMinimumSize(CSize& size);
	virtual void GetMaximumSize(CSize& size);

	DECLARE_MESSAGE_MAP()

private:
	ChatPalette* m_pChatPalette = nullptr;
};

extern MainPaletteSet* G_pMainPane;
