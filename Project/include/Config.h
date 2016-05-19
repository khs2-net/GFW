#ifndef _HEADER_GFW_CONFIG_
#define _HEADER_GFW_CONFIG_
#pragma warning(push)
namespace GFW {
class Config {
public:
	~Config();
	static Config &getInstance() {
		static Config ins;
		return ins;
	}
	ULONG Read(std::string str = "GFW.ini");
	ULONG Write(std::string str = "GFW.ini");

	static boost::property_tree::ptree &get() { return GFW::Config::getInstance().file; }
protected:
private:
	Config();
	boost::property_tree::ptree file;
};
}

#pragma warning(pop)
#endif