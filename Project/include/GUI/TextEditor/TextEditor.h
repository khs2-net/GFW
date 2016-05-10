#ifndef _HEADER_GFW_GUI_TEXTEDITOR_
#define _HEADER_GFW_GUI_TEXTEDITOR_
#pragma warning(push)

namespace GFW {
namespace GUI {

enum class FileOption {
	None = 0,
	NewDir = 1,

};
class Text : public boost::noncopyable {
public:
	Text();
	~Text();

	//ファイル操作系
	String getFilePass();
	ULONG setFilePass(String,ULONG);
	String getFileName();
	ULONG setFileName(String);

	ULONG deleteFile();

	//テキスト操作系
	ULONG New();
	String getAllString();
protected:
private:
	std::list<String> text;
	std::list<String>::iterator cursor;

	
	String filepass;
	String title;
};

class TextEditor  : public boost::noncopyable{
public:
	static TextEditor& getInstance() {
		static TextEditor ins;
		return ins;
	}
	~TextEditor();


	ULONG newText(String title);
	ULONG loadText(String pass);
	ULONG saveText(String saveas = TEXT(""));
	ULONG deleteText();//ファイルごと削除
	ULONG removeText();//ファイルは削除しない
	void InsertString(ULONG, ULONG, String);
	void InsertString(String);

	String getAllText();
	std::list<String> &getList();

	void Update();
protected:
private:
	TextEditor();
	ULONG isCurrent();
	void Update_Menu();
	void Update_Tab();


	std::map<String, Text>::iterator current;
	std::map<String, Text> textlist;

	bool view;
};


}
}
#pragma warning(pop)
#endif