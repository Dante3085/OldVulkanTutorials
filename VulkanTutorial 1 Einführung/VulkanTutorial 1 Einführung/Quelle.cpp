#include <iostream>
#include <fstream>
#include <string>

/*"Einführung": Für Details Programm starten, um Datei auszulesen.*/

int main() {

	std::ifstream file;
	std::string ZeilenSpeicher;
	file.open("Y:/2_IT_Informatik/2_Programmierung/3_MS VS 2017 CE/2_Projekte/VulkanTutorial 1 Einführung/VulkanEinfuehrungDetails.txt");
	if (file.is_open()) {	
		while (std::getline(file, ZeilenSpeicher)) {	
			std::cout << ZeilenSpeicher << std::endl;
		}
		file.close();
	}
	else {
		std::cerr << "Fehler beim Öffnen der Datei!";
	}

	system("pause");
	return 0;
}