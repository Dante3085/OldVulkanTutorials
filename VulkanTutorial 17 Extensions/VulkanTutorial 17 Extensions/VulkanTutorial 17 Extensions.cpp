// VulkanTutorial 17 Extensions.cpp : Definiert den Einstiegspunkt f�r die Konsolenanwendung.
//

#include "stdafx.h"
#include "vulkan\vulkan.h"
#include <iostream>
#include <vector>

#define ASSERT_VULKAN(val) if(val != VK_SUCCESS) {__debugbreak();}		

/*"Extensions":

Allgemeine Informationen
-------------------------
1. Das Sternchen mit einer Nummer ist ein Textverweis auf eine andere Kommentarstelle in dieser Datei. Erschaffen, weil zu wenig Platz in den 2-Bildschirmdimensionen :(.
2. Kommentare bei "0." sind meistens allgemeine Informationen �ber das Thema dieses Tutorials. Speziell zu dem Zeitpunkt, wo die weitere Struktur des Tutorials noch unbekannt ist.
3. Weitere Informationen, die unter genaue Punkte bzw. Themenbereiche zu fassen sind, werden wie folgt numeriert: "1. ... 1.1 ... 1.1.1 ... 2. ... 2.1 ... 2.1.1 ...".
4. "VERALTET UND WIRD IGNORIERT." dient als Mittel, um im Tutorial noch dargestellte Funktionalit�ten, die jedoch jetzt bereits veraltet sind, zu kennzeichnen.
-------------------------

Internetverweise
-----------------
1. vkEnumerateInstanceExtensionProperties: https://www.khronos.org/registry/vulkan/specs/1.0/man/html/vkEnumerateInstanceExtensionProperties.html
2. VkExtensionProperties: https://www.khronos.org/registry/vulkan/specs/1.0/man/html/VkExtensionProperties.html
3. Vulkan� Documentation and Extensions: Procedures and Conventions: https://www.khronos.org/registry/vulkan/specs/1.0/styleguide.html#extensions
-----------------

1.Extensions: Werden auch entweder auf Instanceebene oder Deviceebene gestartet. Sie geben neue Funktionalit�ten in unseren Code. Vulkan kennt von sich aus keine Betriebssysteme. Somit kann es alleine kein Fenster �ffnen
und zeichnen. Daf�r werden Extensions gebraucht. Eine Extension kann auch aus einem speziellen Layer folgen. Das hei�t, ein bestimmter Layer erm�glicht noch bestimmte Extensions.

2.VkExtensionProperties:
	2.1 extensionName: Name der Extension

	2.2 specVersion: Version dieser Extension.

3.vkEnumerateInstanceExtensionProperties:
	3.1 pLayerName: pLayerName is either NULL or a pointer to a null-terminated UTF-8 string naming the layer to retrieve extensions from.

	3.2 pPropertyCount: pPropertyCount is a pointer to an integer related to the number of extension properties available or queried, as described below.

	3.3 pProperties: pProperties is either NULL or a pointer to an array of VkExtensionProperties structures.
*/

namespace VulkanTutorial {

	/*VARIABLES*/
	char *underline = "--------------------------";

	/*INSTANCES*/
	VkInstance instance_ONE;

	/*DEVICES*/
	VkDevice device;

	/*FUNCTIONS*/
	void printDeviceStats(VkPhysicalDevice &device) {

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

		std::cout << "PHYSICAL DEVICE MEMORY PROPERTIES" << std::endl << underline << std::endl;

		VkPhysicalDeviceMemoryProperties memoryProperties;
		vkGetPhysicalDeviceMemoryProperties(device, &memoryProperties);

		std::cout << "" << memoryProperties.memoryHeaps << "\n" << memoryProperties.memoryTypes << "\n\n";
		//---------------------------------

		/*VkQueueFamiliyProperties
		---------------------------*/

		std::cout << "QUEUE FAMILY PROPERTIES" << "\n" << underline << std::endl;

		uint32_t amountOfQueueFamilies = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(device, &amountOfQueueFamilies, NULL);

		VkQueueFamilyProperties *familyProperties = new VkQueueFamilyProperties[amountOfQueueFamilies];		

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

	/*VkApplicationInfo
	--------------------*/
	VkApplicationInfo appInfo;
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pNext = NULL;
	appInfo.pApplicationName = "Vulkan Tutorial";
	appInfo.applicationVersion = VK_MAKE_VERSION(0, 0, 0);
	appInfo.pEngineName = "Super Vulkan Engine Turbo Mega";
	appInfo.engineVersion = VK_MAKE_VERSION(0, 0, 0);
	appInfo.apiVersion = VK_API_VERSION_1_0;
	//--------------------

	/*VkInstanceCreateInfo
	--------------------*/

	uint32_t amountOfLayers = 0;								
	vkEnumerateInstanceLayerProperties(&amountOfLayers, NULL);
	VkLayerProperties *layers = new VkLayerProperties[amountOfLayers];
	vkEnumerateInstanceLayerProperties(&amountOfLayers, layers);

	std::cout << "Instance Layers" << std::endl << VulkanTutorial::underline << std::endl;

	std::cout << "Amount of Instance Layers: " << amountOfLayers << std::endl << std::endl;

	for (int i = 0; i < amountOfLayers; i++) {
		std::cout << "Description:            " << layers[i].description << std::endl;
		std::cout << "Implementation Version: " << layers[i].implementationVersion << std::endl;
		std::cout << "Layer Name:             " << layers[i].layerName << std::endl;
		std::cout << "Spec Version:           " << layers[i].specVersion << std::endl << std::endl;
	}

	uint32_t amountOfExtensions = 0;																		//Extensions
	vkEnumerateInstanceExtensionProperties(NULL, &amountOfExtensions, NULL);								
	VkExtensionProperties *extensions = new VkExtensionProperties[amountOfExtensions];
	vkEnumerateInstanceExtensionProperties(NULL, &amountOfExtensions, extensions);

	std::cout << std::endl;
	std::cout << "Amount of Extensions: " << amountOfExtensions << std::endl;
	for (int i = 0; i < amountOfExtensions; i++) {
		std::cout << std::endl;
		std::cout << "Name: " << extensions[i].extensionName << std::endl;
		std::cout << "Spec Version: " << extensions[i].specVersion << std::endl;
	}

	std::cout << std::endl;

	const std::vector<const char*> validationLayers = {
		"VK_LAYER_LUNARG_standard_validation"
	};

	VkInstanceCreateInfo instanceInfo;
	instanceInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	instanceInfo.pNext = NULL;
	instanceInfo.flags = 0;
	instanceInfo.pApplicationInfo = &appInfo;
	instanceInfo.enabledLayerCount = validationLayers.size();	
	instanceInfo.ppEnabledLayerNames = validationLayers.data();
	instanceInfo.enabledExtensionCount = 0;
	instanceInfo.ppEnabledExtensionNames = NULL;
	//--------------------

	/*vkCreateInstance
	--------------------*/
	VkResult result_ONE = vkCreateInstance(&instanceInfo, NULL, &VulkanTutorial::instance_ONE);

	ASSERT_VULKAN(result_ONE);
	//--------------------

	/*vkEnumeratePhysicalDevices + VkPhysicalDevice
	--------------------*/
	uint32_t amountOfPhysicalDevices = 0;
	result_ONE = vkEnumeratePhysicalDevices(VulkanTutorial::instance_ONE, &amountOfPhysicalDevices, NULL);

	ASSERT_VULKAN(result_ONE);

	VkPhysicalDevice *physicalDevices = new VkPhysicalDevice[amountOfPhysicalDevices];

	result_ONE = vkEnumeratePhysicalDevices(VulkanTutorial::instance_ONE, &amountOfPhysicalDevices, physicalDevices);

	ASSERT_VULKAN(result_ONE);
	//--------------------

	/*Eigenschaften der Physical Devices
	-------------------------------------*/
	for (int i = 0; i < amountOfPhysicalDevices; i++) {
		VulkanTutorial::printDeviceStats(physicalDevices[i]);
	}
	//-------------------------------------

	/*VkDeviceQueueCreateInfo
	--------------------*/

	float queuePrios[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	VkDeviceQueueCreateInfo deviceQueueCreateInfo;
	deviceQueueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	deviceQueueCreateInfo.pNext = NULL;
	deviceQueueCreateInfo.flags = 0;
	deviceQueueCreateInfo.queueFamilyIndex = 0;
	deviceQueueCreateInfo.queueCount = 4;
	deviceQueueCreateInfo.pQueuePriorities = queuePrios;	

	/*VkPhysicalDeviceFeatures
	--------------------*/
	VkPhysicalDeviceFeatures usedFeatures = {};
	//--------------------

	/*VkPhysicalDeviceFeatures
	--------------------*/
	VkDeviceCreateInfo deviceCreateInfo;
	deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	deviceCreateInfo.pNext = NULL;
	deviceCreateInfo.flags = 0;
	deviceCreateInfo.queueCreateInfoCount = 1;
	deviceCreateInfo.pQueueCreateInfos = &deviceQueueCreateInfo;
	deviceCreateInfo.enabledLayerCount = 0;
	deviceCreateInfo.ppEnabledLayerNames = NULL;
	deviceCreateInfo.enabledExtensionCount = 0;
	deviceCreateInfo.ppEnabledExtensionNames = NULL;
	deviceCreateInfo.pEnabledFeatures = &usedFeatures;
	//--------------------

	//VkDevice device;	
	result_ONE = vkCreateDevice(physicalDevices[0], &deviceCreateInfo, NULL, &VulkanTutorial::device);
	ASSERT_VULKAN(result_ONE);

	system("pause");
	return 0;

}

