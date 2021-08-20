#include <iostream>
#include <fstream>
#include <map>
#include <unordered_set>
#include <codecvt>
#include <regex>
#include <cstdio>
#include <cstdlib>


class CppParcer {
private:
	std::map<std::wstring, std::wstring> const dictionary{ {L"пусто", L"void"}, {L"ціле", L"int"}, {L"символ", L"char"},
											   {L"символ", L"char"}, {L"головна", L"main"}, {L"повернути", L"return"}, {L"якщо", L"if"},
											   {L"присвоїти", L"="}, {L"дорівнює", L"=="}, {L"недорівнює", L"!="}, {L"додати", L"+"},
											   {L"відняти", L"-"}, {L"включити", L"#include"}, {L"якщоневизначено", L"#ifndef"},
											   {L"визначити", L"#define"}, {L"кінець", L"#endif"}, {L"надрукувати", L"std::cout<<"}, {L"ITEA_", L""} };

	std::vector<std::wstring> const ua = { L"а", L"б", L"в", L"г", L"д", L"е", L"є", L"ж", L"з", L"і", L"ї", L"й", L"к", L"л", L"м", L"н", L"о", L"п", L"р", L"с", L"т", L"у", L"ф", L"х", L"ц", L"ш", L"щ", L"ю", L"я" };
	
	std::vector<std::wstring> const en = { L"a", L"b", L"v", L"h", L"d", L"e", L"ye", L"zh", L"z", L"i", L"y", L"yi", L"k", L"l", L"m", L"n", L"o", L"p", L"r", L"s", L"t", L"u", L"f", L"kh", L"ts", L"sh", L"shsc", L"yu", L"ya" };
	
	std::string const makeFileName = "Збірка.txt";
	
	std::string makePath;
	
	std::string compilerCpp;

	std::string projectName;

	std::unordered_set<std::string> projectFiles;

	std::unordered_set<std::string> cppFiles;
public:
	CppParcer (std::string makePath, std::string compilerCpp):makePath(makePath), compilerCpp(compilerCpp) {}
	~CppParcer() = default;
	
	bool parce() {
		try {
			projFileParcer();
			codeFileParcer();
			makeFile();
			compile();
		}
		catch (std::string err) {
			std::cerr << err << std::endl;
			return false;
		}
		return true;
	}

private:
	std::string getUtf8(const std::wstring& wstr) {
		if (wstr.empty()) return std::string{};
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> convert;
		std::string res = convert.to_bytes(wstr);
		return res;
	}

	std::wstring getUtf16(const std::string& str) {
		if (str.empty()) return std::wstring{};
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> convert;
		std::wstring res = convert.from_bytes(str);
		return res;
	}

	void getText(std::string fileName, std::wstring& text) {
		std::ifstream in{ fileName };
		if (!in.is_open()) {
			throw "file not found " + fileName;
		}
		std::wbuffer_convert<std::codecvt_utf8<wchar_t>> conv(in.rdbuf());
		std::wistream wf(&conv);
		in.seekg(0, std::ios::beg);
		text.assign((std::istreambuf_iterator<wchar_t>(wf)), (std::istreambuf_iterator<wchar_t>()));
		in.close();
	}
	
	void projFileParcer() {
		std::string makeFile = makePath + makeFileName;
		std::ifstream in{ makeFile };
		if (!in.is_open()) {
			throw "File not found " + makeFile;
			return;
		}
		in >> projectName;
		projectName = projectName.substr(projectName.rfind(":") + 1);
		std::string tmpStr;
		while (in >> tmpStr) {
			projectFiles.insert(tmpStr);
		}
		in.close();
	}

	void codeParser(std::wstring& text) {
		for (auto p : dictionary) {
			if (text.rfind(p.first) > 0) {
				text = std::regex_replace(text, std::wregex(p.first), p.second);
			}
		}
		for (unsigned int i = 0; i < ua.size(); i++) {
			text = std::regex_replace(text, std::wregex(ua[i]), en[i]);
		}
	}
 
	void saveFile(std::string fileName, std::wstring& text) {
		std::string filePath{ makePath + "out/" + fileName };
		std::ofstream of{ filePath };
		of << getUtf8(text);
		of.close();
		cppFiles.insert(filePath);
	}

	void codeFileParcer() {
		for (auto fileName : projectFiles) {
			std::string p = makePath + fileName;
			std::wstring text;
			getText(p, text);
			codeParser(text);
			std::string cppFileName = fileName.substr(0, fileName.rfind(".") + 1) + fileName.substr(fileName.rfind("_") + 1);
			saveFile(cppFileName, text);
		}
	}

	void makeFile() {
		std::wstring text = getUtf16(compilerCpp) + L" -Wall -o ";
		text = text + L" " + getUtf16(projectName);
		for (auto filePath : cppFiles) {
			if (filePath.rfind(".cpp") > 0) {
				text = text + L" " + getUtf16(filePath);
			}
		}
		saveFile("makefile.bat", text);
	}

	void compile() {
		if (std::system((makePath + "out/makefile.bat").c_str()) > 0) {
			throw "Compile error";
		}

		for (auto filePath : cppFiles) {
			std::remove(filePath.c_str());
		}
	}
};

int main()
{
	CppParcer cppParcer{ "D:/GIT/ITEA/HW7/", "\"C:/Program Files/mingw-w64/x86_64-8.1.0-posix-seh-rt_v6-rev0/mingw64/bin/g++.exe\"" };
	if (cppParcer.parce()) {
		std::cout << "Compilation finished" << std::endl;
	}
}
