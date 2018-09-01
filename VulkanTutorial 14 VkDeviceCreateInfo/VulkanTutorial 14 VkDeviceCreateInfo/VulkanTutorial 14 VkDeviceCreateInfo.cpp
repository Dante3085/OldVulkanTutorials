// VulkanTutorial 14 VkDeviceCreateInfo.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include "vulkan\vulkan.h"
#include <iostream>

#define ASSERT_VULKAN(val) if(val != VK_SUCCESS) {__debugbreak();}		

/*"VkDeviceCreateInfo":

Allgemeine Informationen
-------------------------
1. Das Sternchen mit einer Nummer ist ein Textverweis auf eine andere Kommentarstelle in dieser Datei. Erschaffen, weil zu wenig Platz in den 2-Bildschirmdimensionen :(.
2. Kommentare bei "0." sind meistens allgemeine Informationen über das Thema dieses Tutorials. Speziell zu dem Zeitpunkt, wo die weitere Struktur des Tutorials noch unbekannt ist.
3. Weitere Informationen, die unter genaue Punkte bzw. Themenbereiche zu fassen sind, werden wie folgt numeriert: "1. ... 1.1 ... 1.1.1 ... 2. ... 2.1 ... 2.1.1 ...".
4. "VERALTET UND WIRD IGNORIERT." dient als Mittel, um im Tutorial noch dargestellte Funktionalitäten, die jedoch jetzt bereits veraltet sind, zu kennzeichnen.
-------------------------

Internetverweise
-----------------
1. VkDeviceCreateInfo: https://www.khronos.org/registry/vulkan/specs/1.0/man/html/VkDeviceCreateInfo.html
-----------------

1. VkDeviceCreateInfo: Die Info, die dafür zuständig ist ein logisches Device zu bauen.
	1.1 sType: Typ dieser Struktur. "VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO".

	1.2 pNext: "NULL", da keine Extensions gebraucht werden.

	1.3 flags: "0", da für "future use" (noch keine Funktion).

	1.4 queueCreateInfoCount: Größe des "pQueueCreateInfos" Arrays.

	1.5 pQueueCreateInfos: Wurde gerade erstellt. Es können aber noch mehr "QueueCreateInfos" erstellt werden, da eventuell von unterschiedlichen Families unterschiedliche Queues created werden sollen. Dazu werden
	unterschiedliche "QueueCreateInfos" gebraucht, die dann in dieses Array gesteckt werden.

	1.6 enabledLayerCount: VERALTET UND WIRD IGNORIERT.

	1.7 ppEnabledLayerNames: VERALTET UND WIRD IGNORIERT.

	1.8 enabledExtensionCount: Wie viele Extensions "ppEnabledExtensionNames" enthält.

	1.9 ppEnabledExtensionNames: Array an Strings mit Extensions.

	1.10 pEnabledFeatures: Pointer auf "VkPhysicalDeviceFeatures" oder "NULL". Hier kommen alle Features rein, die gebraucht werden und von der GPU unterstützt werden bzw. "true" sind.
*/

namespace VulkanTutorial {

	/*INSTANCES*/
	VkInstance instance_ONE;

	/*FUNCTIONS*/
	void printDeviceStats(VkPhysicalDevice &device) {

		//Char Pointer that underlines Text in the console.
		char *underline = "--------------------------";

		/*VkPhysicalDeviceProperties
		-----------------------------*/

		std::cout << "PHYSICAL DEVICE PROPERTIES" << "\n" << underline << std::endl;

		VkPhysicalDeviceProperties properties;
		vkGetPhysicalDeviceProperties(device, &properties);

		std::cout << "Name: " << properties.deviceName << "\n";
		uint32_t apiVer = properties.apiVersion;
		std::cout << "apiVersion: " << VK_VERSION_MAJOR(apiVer) << "." << VK_VERSION_MINOR(apiVer) << "." << VK_VERSION_PATCH(apiVer) << "\n";
		std::cout << "deviceID: " << properties.deviceID << "\n";
		std::cout << "deviceType: " << properties.deviceType << "\n";
		std::cout << "driverVersion	: " << properties.driverVersion << "\n";
		std::cout << "pipelineCacheUUID: " << properties.pipelineCacheUUID << "\n";
		std::cout << "vendorID: " << properties.vendorID << "\n";
		std::cout << "discreteQueuePriorities " << properties.limits.discreteQueuePriorities << "\n\n";
		//----------------------------

		/*VkPhysicalDeviceFeatures
		---------------------------*/

		std::cout << "PHYSICAL DEVICE FEATURES" << "\n" << underline << std::endl;

		VkPhysicalDeviceFeatures features;
		vkGetPhysicalDeviceFeatures(device, &features);

		std::cout << "Geometry Shader: " << features.geometryShader << "\n" << std::endl;
		//---------------------------

		/*VkPhysicalDeviceMemoryProperties
		---------------------------------*/

		std::cout << "PHYSICAL DEVICE MEMORY PROPERTIES" << "\n" << underline << std::endl;

		VkPhysicalDeviceMemoryProperties memoryProperties;
		vkGetPhysicalDeviceMemoryProperties(device, &memoryProperties);

		std::cout << "" << memoryProperties.memoryHeaps << "\n" << memoryProperties.memoryTypes << "\n\n";
		//---------------------------------

		/*VkQueueFamiliyProperties
		---------------------------*/

		std::cout << "QUEUE FAMILY PROPERTIES" << "\n" << underline << std::endl;

		uint32_t amountOfQueueFamilies = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(device, &amountOfQueueFamilies, NULL);

		VkQueueFamilyProperties *familyProperties = new VkQueueFamilyProperties[amountOfQueueFamilies];		//*1

		vkGetPhysicalDeviceQueueFamilyProperties(device, &amountOfQueueFamilies, familyProperties);

		std::cout << "Amount of Queue Families: " << amountOfQueueFamilies << std::endl;

		for (int i = 0; i < amountOfQueueFamilies; i++) {
			std::cout << std::endl;
			std::cout << "Queue Familiy" << i << std::endl;
			std::cout << "VK_QUEUE_GRAPHICS_BIT " << ((familyProperties[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) != 0) << std::endl;
			std::cout << "VK_QUEUE_COMPUTE_BIT " << ((familyProperties[i].queueFlags & VK_QUEUE_COMPUTE_BIT) != 0) << std::endl;
			std::cout << "VK_QUEUE_TRANSFER_BIT " << ((familyProperties[i].queueFlags & VK_QUEUE_TRANSFER_BIT) != 0) << std::endl;
			std::cout << "VK_QUEUE_SPARSE_BINDING_BIT " << ((familyProperties[i].queueFlags & VK_QUEUE_SPARSE_BINDING_BIT) != 0) << std::endl;
			std::cout << "Queue Count: " << familyProperties[i].queueCount << std::endl;
			std::cout << "Timestamp Valid Bits: " << familyProperties[i].timestampValidBits << std::endl;
			uint32_t width = familyProperties[i].minImageTransferGranularity.width;
			uint32_t height = familyProperties[i].minImageTransferGranularity.height;
			uint32_t depth = familyProperties[i].minImageTransferGranularity.depth;
			std::cout << "Min Image Transfer Granularity" << width << "," << height << "," << depth << std::endl;
		}

		std::cout << std::endl;
		delete[] familyProperties;
		//---------------------------
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

	VkResult result_ONE = vkCreateInstance(&instanceInfo, NULL, &VulkanTutorial::instance_ONE);

	ASSERT_VULKAN(result_ONE);

	uint32_t amountOfPhysicalDevices = 0;
	result_ONE = vkEnumeratePhysicalDevices(VulkanTutorial::instance_ONE, &amountOfPhysicalDevices, NULL);

	ASSERT_VULKAN(result_ONE);

	VkPhysicalDevice *physicalDevices = new VkPhysicalDevice[amountOfPhysicalDevices];

	result_ONE = vkEnumeratePhysicalDevices(VulkanTutorial::instance_ONE, &amountOfPhysicalDevices, physicalDevices);

	ASSERT_VULKAN(result_ONE);

	for (int i = 0; i < amountOfPhysicalDevices; i++) {
		VulkanTutorial::printDeviceStats(physicalDevices[i]);
	}

	VkDeviceQueueCreateInfo deviceQueueCreateInfo;							 
	deviceQueueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	deviceQueueCreateInfo.pNext = NULL;										 
	deviceQueueCreateInfo.flags = 0;									     
	deviceQueueCreateInfo.queueFamilyIndex = 0;								 
	deviceQueueCreateInfo.queueCount = 4;									 
	deviceQueueCreateInfo.pQueuePriorities = NULL;							 

	VkPhysicalDeviceFeatures usedFeatures = {}; //Initialisiert die Featureliste mit 0, da wir momentan keine Features brauchen.

	VkDeviceCreateInfo deviceCreateInfo;
	deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	deviceCreateInfo.pNext = NULL;
	deviceCreateInfo.flags = 0;
	deviceCreateInfo.queueCreateInfoCount = 1;
	deviceCreateInfo.pQueueCreateInfos = &deviceQueueCreateInfo;
	deviceCreateInfo.enabledLayerCount = 0;							//VERALTET UND WIRD IGNORIERT.
	deviceCreateInfo.ppEnabledLayerNames = NULL;					//VERALTET UND WIRD IGNORIERT.
	deviceCreateInfo.enabledExtensionCount = 0;
	deviceCreateInfo.ppEnabledExtensionNames = NULL;
	deviceCreateInfo.pEnabledFeatures = &usedFeatures;

	system("pause");
	return 0;

}

