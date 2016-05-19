using namespace GFW;

Config::Config() {

}
Config::~Config() {
	this->Write();
}

ULONG Config::Read(std::string str) {
	const boost::filesystem::path path(str);
	boost::system::error_code error;
	const bool result = boost::filesystem::exists(path, error);
	if (!result || error) {
		this->Write();
	} else {
		boost::property_tree::read_ini(str, this->file);
	}



	return 0;
}
ULONG Config::Write(std::string str) {
	boost::property_tree::write_ini(str, this->file);
	return 0;
}