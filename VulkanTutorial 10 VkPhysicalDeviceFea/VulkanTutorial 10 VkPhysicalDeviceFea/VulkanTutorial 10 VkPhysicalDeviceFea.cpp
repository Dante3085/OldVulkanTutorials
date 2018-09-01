// VulkanTutorial 10 VkPhysicalDeviceFea.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
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
1.VkPhysicalDeviceFeatures: https://www.khronos.org/registry/vulkan/specs/1.0/man/html/VkPhysicalDeviceFeatures.html
2.vkGetPhysicalDeviceFeatures: https://www.khronos.org/registry/vulkan/specs/1.0/man/html/vkGetPhysicalDeviceFeatures.html
-----------------

1. VkPhysicalDeviceFeatures: Features der Grafikkarte. Funktionen oder verschiedene Möglichkeiten, die die GPU bietet. Was für "Shader" kann ich erzeugen.
	1.1 Shader: Kleine Programme, die auf der Grafikkarte laufen können. Später mehr.
*/

namespace VulkanTutorial {

	/*INSTANCES*/
	VkInstance instance_ONE;

	/*FUNCTIONS*/
	void printDeviceStats(VkPhysicalDevice &device) {		

		char *underline = "--------------------------";

		VkPhysicalDeviceProperties properties;				
		vkGetPhysicalDeviceProperties(device, &properties);

		std::cout << "PHYSICAL DEVICE PROPERTIES" << "\n" << underline << std::endl;

		std::cout << "Name			   : " << properties.deviceName << "\n";
		uint32_t apiVer = properties.apiVersion;
		std::cout << "apiVersion	   : " << VK_VERSION_MAJOR(apiVer) << "." << VK_VERSION_MINOR(apiVer) << "." << VK_VERSION_PATCH(apiVer) << "\n";	
		std::cout << "deviceID		   : " << properties.deviceID << "\n";	
		std::cout << "deviceType	   : " << properties.deviceType << "\n";	
		std::cout << "driverVersion	   : " << properties.driverVersion << "\n";	
		std::cout << "pipelineCacheUUID: " << properties.pipelineCacheUUID << "\n"; 
		std::cout << "vendorID	       : " << properties.vendorID << "\n\n";	

		VkPhysicalDeviceFeatures features;				//Struct mit vielen bools, die zeigen, ob die GPU etwas kann oder nicht. Diese Features müssen noch separat aktiviert werden. 
		vkGetPhysicalDeviceFeatures(device, &features);

		std::cout << "PHYSICAL DEVICE FEATURES" << "\n" << underline << std::endl;

		std::cout << "Geometry Shader: " << features.geometryShader << std::endl;	//"0"
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


