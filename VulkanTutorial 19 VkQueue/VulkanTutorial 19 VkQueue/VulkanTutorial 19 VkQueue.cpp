// VulkanTutorial 19 VkQueue.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include "vulkan\vulkan.h"
#include <iostream>
#include <vector>

#define ASSERT_VULKAN(val) if(val != VK_SUCCESS) {__debugbreak();}		

/*"VkQueue":

Allgemeine Informationen
-------------------------
1. Das Sternchen mit einer Nummer ist ein Textverweis auf eine andere Kommentarstelle in dieser Datei. Erschaffen, weil zu wenig Platz in den 2-Bildschirmdimensionen :(.
2. Kommentare bei "0." sind meistens allgemeine Informationen über das Thema dieses Tutorials. Speziell zu dem Zeitpunkt, wo die weitere Struktur des Tutorials noch unbekannt ist.
3. Weitere Informationen, die unter genaue Punkte bzw. Themenbereiche zu fassen sind, werden wie folgt numeriert: "1. ... 1.1 ... 1.1.1 ... 2. ... 2.1 ... 2.1.1 ...".
4. "VERALTET UND WIRD IGNORIERT." dient als Mittel, um im Tutorial noch dargestellte Funktionalitäten, die jedoch jetzt bereits veraltet sind, zu kennzeichnen.
-------------------------

Internetverweise
-----------------
1. VkQueue: https://www.khronos.org/registry/vulkan/specs/1.0/man/html/VkQueue.html
2. vkGetDeviceQueue: https://www.khronos.org/registry/vulkan/specs/1.0/man/html/vkGetDeviceQueue.html
-----------------

0. Wir brauchen Möglichkeit, um auf Queues zuzugreifen.
Alle "NULL"s werden, wie es in C++ übrig ist, mit dem "nullptr" ersetzt. Ursprünglich wurde im Tutorial "NULL" verwendet, da dies der Konsens ist. Jedoch scheint es keinen Grund dafür zu geben. Deswegen der C++ übliche
nullptr. nullptr hat auch den Vorteil, dass er nur Variablen, die einen Pointer erwarten zugewiesen werden kann. Da "NULL" praktisch nur eine 0 ist, ist dies dort nicht der Fall.
*/

namespace VulkanTutorial {

	/*VARIABLES*/
	char *underline = "--------------------------";

	/*INSTANCES*/
	VkInstance instance_ONE;

	/*DEVICES*/
	VkDevice device_ONE;

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
		vkGetPhysicalDeviceQueueFamilyProperties(device, &amountOfQueueFamilies, nullptr);

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
	appInfo.pNext = nullptr;
	appInfo.pApplicationName = "Vulkan Tutorial";
	appInfo.applicationVersion = VK_MAKE_VERSION(0, 0, 0);
	appInfo.pEngineName = "Super Vulkan Engine Turbo Mega";
	appInfo.engineVersion = VK_MAKE_VERSION(0, 0, 0);
	appInfo.apiVersion = VK_API_VERSION_1_0;
	//--------------------

	/*VkInstanceCreateInfo
	--------------------*/

	uint32_t amountOfLayers = 0;
	vkEnumerateInstanceLayerProperties(&amountOfLayers, nullptr);
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

	uint32_t amountOfExtensions = 0;
	vkEnumerateInstanceExtensionProperties(nullptr, &amountOfExtensions, nullptr);
	VkExtensionProperties *extensions = new VkExtensionProperties[amountOfExtensions];
	vkEnumerateInstanceExtensionProperties(nullptr, &amountOfExtensions, extensions);

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
	instanceInfo.pNext = nullptr;
	instanceInfo.flags = 0;
	instanceInfo.pApplicationInfo = &appInfo;
	instanceInfo.enabledLayerCount = validationLayers.size();
	instanceInfo.ppEnabledLayerNames = validationLayers.data();
	instanceInfo.enabledExtensionCount = 0;
	instanceInfo.ppEnabledExtensionNames = nullptr;
	//--------------------

	/*vkCreateInstance
	--------------------*/
	VkResult result_ONE = vkCreateInstance(&instanceInfo, nullptr, &VulkanTutorial::instance_ONE);

	ASSERT_VULKAN(result_ONE);
	//--------------------

	/*vkEnumeratePhysicalDevices + VkPhysicalDevice
	--------------------*/
	uint32_t amountOfPhysicalDevices = 0;
	result_ONE = vkEnumeratePhysicalDevices(VulkanTutorial::instance_ONE, &amountOfPhysicalDevices, nullptr);

	ASSERT_VULKAN(result_ONE);

	VkPhysicalDevice *physicalDevices = new VkPhysicalDevice[amountOfPhysicalDevices];
	/*std::vector<VkPhysicalDevice> physicalDevices;		
	physicalDevices.resize(amountOfPhysicalDevices);*/

	result_ONE = vkEnumeratePhysicalDevices(VulkanTutorial::instance_ONE, &amountOfPhysicalDevices, physicalDevices/*physicalDevices.data()*/);

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
	deviceQueueCreateInfo.pNext = nullptr;
	deviceQueueCreateInfo.flags = 0;
	deviceQueueCreateInfo.queueFamilyIndex = 0;
	deviceQueueCreateInfo.queueCount = 1;	//Aus Gründen der Einfachheit von "4" auf "1" geändert.
	deviceQueueCreateInfo.pQueuePriorities = queuePrios;

	/*VkPhysicalDeviceFeatures
	--------------------*/
	VkPhysicalDeviceFeatures usedFeatures = {};
	//--------------------

	/*VkPhysicalDeviceFeatures
	--------------------*/
	VkDeviceCreateInfo deviceCreateInfo;
	deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	deviceCreateInfo.pNext = nullptr;
	deviceCreateInfo.flags = 0;
	deviceCreateInfo.queueCreateInfoCount = 1;
	deviceCreateInfo.pQueueCreateInfos = &deviceQueueCreateInfo;
	deviceCreateInfo.enabledLayerCount = 0;
	deviceCreateInfo.ppEnabledLayerNames = nullptr;
	deviceCreateInfo.enabledExtensionCount = 0;
	deviceCreateInfo.ppEnabledExtensionNames = nullptr;
	deviceCreateInfo.pEnabledFeatures = &usedFeatures;
	//--------------------

	//VkDevice device;	
	result_ONE = vkCreateDevice(physicalDevices[0], &deviceCreateInfo, nullptr, &VulkanTutorial::device_ONE);
	ASSERT_VULKAN(result_ONE);

	VkQueue queue;	//Dummywert, der in eine Funktion gegeben wird, um die tatsächliche Queue zu erstellen.

	vkGetDeviceQueue(VulkanTutorial::device_ONE, 0, 0, &queue);

	vkDeviceWaitIdle(VulkanTutorial::device_ONE);	
	vkDestroyDevice(VulkanTutorial::device_ONE, nullptr);		 
	vkDestroyInstance(VulkanTutorial::instance_ONE, nullptr);	 

	delete[] layers;				 
	delete[] extensions;			 
	delete[] physicalDevices;		 

	system("pause");
	return 0;

}

