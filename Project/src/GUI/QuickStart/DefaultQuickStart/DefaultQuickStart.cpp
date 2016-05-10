
ULONG GFW::GUI::Default::Init_Quickstart() {

	GFW::GUI::QuickStart &qs = GFW::GUI::QuickStart::getInstance();
	GFW::Gui &gui = GFW::Gui::getInstance();
	gui.Attach(&qs);

	GFW::GUI::Inspector &ins = GFW::GUI::Inspector::getInstance();
	qs.AttachApp("ins", ins);
	qs.AttachApp("inspector", ins);
	gui.Attach(&ins);

	GFW::GUI::Console &con = GFW::GUI::Console::getInstance();
	qs.AttachApp("cmd", con);
	qs.AttachApp("console", con);
	gui.Attach(&con);

	GFW::GUI::ShaderList &sl = GFW::GUI::ShaderList::getInstance();
	qs.AttachApp("sl", sl);
	qs.AttachApp("shaderlist", sl);
	gui.Attach(&sl);


	return 0;
}