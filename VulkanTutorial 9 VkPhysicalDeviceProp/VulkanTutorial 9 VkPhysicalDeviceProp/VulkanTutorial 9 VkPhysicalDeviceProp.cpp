// VulkanTutorial 9 VkPhysicalDeviceProp.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include "vulkan\vulkan.h"
#include <iostream>

#define ASSERT_VULKAN(val) if(val != VK_SUCCESS) {__debugbreak();}		

/*"VkPhysicalDeviceProperties":

Allgemeine Informationen
-------------------------
1. Das Sternchen mit einer Nummer ist ein Textverweis auf eine andere Kommentarstelle in dieser Datei. Erschaffen, weil zu wenig Platz in den 2-Bildschirmdimensionen :(.
2. Kommentare bei "0." sind meistens allgemeine Informationen über das Thema dieses Tutorials. Speziell zu dem Zeitpunkt, wo die weitere Struktur des Tutorials noch unbekannt ist.
3. Weitere Informationen, die unter genaue Punkte bzw. Themenbereiche zu fassen sind, werden wie folgt numeriert: "1. ... 1.1 ... 1.1.1 ... 2. ... 2.1 ... 2.1.1 ...".
-------------------------

Internetverweise
-----------------
1. VkPhysicalDeviceType: https://www.khronos.org/registry/vulkan/specs/1.0/man/html/VkPhysicalDeviceType.html
2. VkPhysicalDeviceLimits: https://www.khronos.org/registry/vulkan/specs/1.0/man/html/VkPhysicalDeviceLimits.html
3. VkPhysicalDeviceSparseProperties: https://www.khronos.org/registry/vulkan/specs/1.0/man/html/VkPhysicalDeviceSparseProperties.html
-----------------

0. Wir werden PhysicalDevices untersuchen.

*1
---
"VkPhysicalDeviceProperties::apiVersion" ist alleine nur eine Zahl, die erst in Major, Minor und Patch (Versionsnummer) übersetzt werden muss.
---

*2
----
"VkPhysicalDeviceLimits": Großes struct mit Fähigkeiten/Eigenschaften der GPU. Zum Beispiel maximale Dimension eines Image, dass die GPU darstellen kann.
"VkPhysicalDeviceSparseProperties": Beinhaltet Eigenschaften der "Sparse Texturen". Sparse Texturen sind sehr große Texturen, die alleine nicht in den Grafikkartenspeicher passen. Müssen deswegen in 
unterschiedliche kleine Texturen (Tiles) aufgesplittet werden.
----
*/

namespace VulkanTutorial {
	
	/*INSTANCES*/
	VkInstance instance_ONE;

	/*FUNCTIONS*/
	void printDeviceStats(VkPhysicalDevice &device) {		//Sollte mit Call by Value gehen. Damit man aber mit dem Device arbeiten kann, Call by Reference.

		VkPhysicalDeviceProperties properties;				//Kann physicalDeviceProperties speichern.
		vkGetPhysicalDeviceProperties(device, &properties); //Erwartet device und Pointer auf VkPhysicalDeviceProperties.

		std::cout << "Name: " << properties.deviceName << "\n";

		uint32_t apiVer = properties.apiVersion;
		std::cout << "apiVersion: " << VK_VERSION_MAJOR(apiVer) << "." << VK_VERSION_MINOR(apiVer) << "." << VK_VERSION_PATCH(apiVer) << "\n";	//Maximale Version von Vulkan, die die Grafikkarte unterstützt. *1

		std::cout << "deviceID: " << properties.deviceID << "\n";	//Kein Standard.

		std::cout << "deviceType: " << properties.deviceType << "\n";	//Siehe Internetverweise "1.".

		std::cout << "driverVersion: " << properties.driverVersion << "\n";	//Kein Standard.

		std::cout << "pipelineCacheUUID: " << properties.pipelineCacheUUID << "\n"; //Wichtig für Shader. Später mehr.

		std::cout << "vendorID: " << properties.vendorID << "\n\n";	//Vendor = Hersteller. Kein Standard.
		
		//*2
	}
}

int main() {

	VkApplicationInfo appInfo;
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pNext = NULL;
	appInfo.pApplicationName = "Vulkan Tutorial";
	appInfo.applicationVersion = VK_MAKE_VERSION(0, 0, 0);
	appInfo.pEngineName = "Super Vulkan Engine Turbo Mega";
	appInfo.engineVersion = VK_MAKE_VERSION(0, 0, 0);
	appInfo.apiVersion = VK_API_VERSION_1_0;

	VkInstanceCreateInfo instanceInfo;
	instanceInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	instanceInfo.pNext = NULL;
	instanceInfo.flags = 0;
	instanceInfo.pApplicationInfo = &appInfo;
	instanceInfo.enabledLayerCount = 0;
	instanceInfo.ppEnabledLayerNames = NULL;
	instanceInfo.enabledExtensionCount = 0;
	instanceInfo.ppEnabledExtensionNames = NULL;

	VkResult result = vkCreateInstance(&instanceInfo, NULL, &VulkanTutorial::instance_ONE);

	ASSERT_VULKAN(result);

	uint32_t amountOfPhysicalDevices = 0;
	result = vkEnumeratePhysicalDevices(VulkanTutorial::instance_ONE, &amountOfPhysicalDevices, NULL);

	ASSERT_VULKAN(result);

	VkPhysicalDevice *physicalDevices = new VkPhysicalDevice[amountOfPhysicalDevices];

	result = vkEnumeratePhysicalDevices(VulkanTutorial::instance_ONE, &amountOfPhysicalDevices, physicalDevices);

	ASSERT_VULKAN(result);

	for (int i = 0; i < amountOfPhysicalDevices; i++) {
		VulkanTutorial::printDeviceStats(physicalDevices[i]);
	}

	system("pause");
	return 0;

}
