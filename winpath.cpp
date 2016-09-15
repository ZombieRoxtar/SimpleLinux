/*
	winpath: resolves the WSL path virtualization for easy pasting into Windows
	This awesome program was written by Chris Roxby
//*/
#include <algorithm>
#include <iostream>
#include <unistd.h>

int main(int argc, char* argv[])
{
	bool bInRootfs = true;
	bool bMounted = false;

	std::string sPath = getcwd(NULL, 0);

	/* These 3 Directories live above \rootfs\ */
	if ((sPath.substr(0, 5) == "/mnt/") ||
		(sPath.substr(0, 6) == "/home/") ||
		(sPath.substr(0, 6) == "/root/"))
		bInRootfs = false;

	/*
		This works for drives that are mounted as their letter designation
		In other cases you'll get something like "file_share:\myPath"
	// */
	if (sPath.substr(0, 5) == "/mnt/")
	{
		bMounted = true;
		sPath.erase(0, 5); // Drop /mnt/
		sPath.insert(sPath.find("/"), ":"); // instert a : before the first /
	}

	replace(sPath.begin(), sPath.end(), '/', '\\'); // Flip these

	if (!bMounted)
	std::cout << "%localappdata%\\lxss";
	if (bInRootfs)
		std::cout << "\\rootfs";
	std::cout << sPath << std::endl;
	return EXIT_SUCCESS;
}
