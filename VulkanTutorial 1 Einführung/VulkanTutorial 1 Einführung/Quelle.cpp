#include <iostream>
#include <fstream>
#include <string>

/*"Einf�hrung": F�r Details Programm starten, um Datei auszulesen.*/

int main() {

	std::ifstream file;
	std::string ZeilenSpeicher;
	file.open("Y:/2_IT_Informatik/2_Programmierung/3_MS VS 2017 CE/2_Projekte/VulkanTutorial 1 Einf�hrung/VulkanEinfuehrungDetails.txt");
	if (file.is_open()) {	
		while (std::getline(file, ZeilenSpeicher)) {	
			std::cout << ZeilenSpeicher << std::endl;
		}
		file.close();
	}
	else {
		std::cerr << "Fehler beim �ffnen der Datei!";
	}

	system("pause");
	return 0;
}