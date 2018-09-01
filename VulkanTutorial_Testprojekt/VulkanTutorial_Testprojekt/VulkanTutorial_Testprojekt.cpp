// VulkanTutorial 20 VkSurfaceKHRWindows.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#define VK_USE_PLATFORM_WIN32_KHR //"KHR" zeigt, dass dies eine Extension ist. Muss vor "vulkan\vulkan.h" und nach "stdafx.h" defined werden.
#include "vulkan\vulkan.h"
#include <iostream>
#include <vector>
#include <chrono>

#define ASSERT_VULKAN(val) if(val != VK_SUCCESS) {__debugbreak();}		

/*"VkSurfaceKHR für Windows":

Allgemeine Informationen
-------------------------
1. Das Sternchen mit einer Nummer ist ein Textverweis auf eine andere Kommentarstelle in dieser Datei. Erschaffen, weil zu wenig Platz in den 2-Bildschirmdimensionen :(.
2. Kommentare bei "0." sind meistens allgemeine Informationen über das Thema dieses Tutorials. Speziell zu dem Zeitpunkt, wo die weitere Struktur des Tutorials noch unbekannt ist.
3. Weitere Informationen, die unter genaue Punkte bzw. Themenbereiche zu fassen sind, werden wie folgt numeriert: "1. ... 1.1 ... 1.1.1 ... 2. ... 2.1 ... 2.1.1 ...".
4. "VERALTET UND WIRD IGNORIERT." dient als Mittel, um im Tutorial noch dargestellte Funktionalitäten, die jedoch jetzt bereits veraltet sind, zu kennzeichnen.
-------------------------

Internetverweise
-----------------

-----------------

0. Nächstes Etappenziel: Herstellung eines Surface, auf dem gezeichnet werden kann. Surface liegt immer in einem Fenster (Window). Vulkan an sich kennt keine Fenster. Wir könnten die "windows.h" benutzen. Allerdings
wäre unser Programm dann an Windows gebunden. Es gibt eine Zusatzlibrary, die platformunabhängige Fenster ermöglicht. Später mehr. Jetzt Surfacecreation ohne Fenster.

1. VkWin32SurfaceCreateInfoKHR:
1.1 sType: Typ dieser Struktur. "VK_STRUCTURE_TYPE_DISPLAY_SURFACE_CREATE_INFO_KHR".

1.2 pNext: Extensions. Für uns "nullptr".

1.3 flags: future Use.

1.4 hinstance: Kommt aus "windows.h". Ist mit der Fenstererstellung verbunden. Fenster würde hier reingegeben werden.

1.5 hwnd: Kommt aus "windows.h". Ist mit der Fenstererstellung verbunden.
*/

/*FUNCTIONS
--------------*/
void measureTime(std::string time) {

	static std::chrono::high_resolution_clock::time_point t1;
	static std::chrono::high_resolution_clock::time_point t2;
	static bool t1Measured = false;

	if (time == "t1") {
		t1Measured = true;
		t1 = std::chrono::high_resolution_clock::now();
	}

	if (time == "t2") {
		if (t1Measured == false) {
			std::cerr << "The start point of the measurement must be specified first!" << std::endl;
		}
		else {
			t2 = std::chrono::high_resolution_clock::now();
			auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
			std::cout << "duration in microseconds: " << duration << std::endl;
		}
	}

	else {
		std::cerr << "Wrong input! Only 't1' and 't2' " << std::endl;
	}
}
//-----------------

/*NAMESPACES
--------------*/
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
//----------------------------

int main() {

	measureTime("t1");

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

	const std::vector<const char*> usedExtension = {
		"VK_KHR_surface",								//Wir wollen etwas auf einem Fenster zeichnen.
		VK_KHR_WIN32_SURFACE_EXTENSION_NAME				//Auf welchem Betriebsystem. "VK_KHR_win32_surface" kann auch verwendet werden. Bei "VK_KHR_WIN32_SURFACE_EXTENSION_NAME" kontrolliert Compiler jedoch richtige Schreibweise.
	};

	VkInstanceCreateInfo instanceInfo;
	instanceInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	instanceInfo.pNext = nullptr;
	instanceInfo.flags = 0;
	instanceInfo.pApplicationInfo = &appInfo;
	instanceInfo.enabledLayerCount = validationLayers.size();
	instanceInfo.ppEnabledLayerNames = validationLayers.data();
	instanceInfo.enabledExtensionCount = usedExtension.size();
	instanceInfo.ppEnabledExtensionNames = usedExtension.data();
	//--------------------

	/*vkCreateInstance
	--------------------*/
	VkResult result_ONE = vkCreateInstance(&instanceInfo, nullptr, &VulkanTutorial::instance_ONE);
	ASSERT_VULKAN(result_ONE);

	VkWin32SurfaceCreateInfoKHR surfaceCreateInfo;
	surfaceCreateInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR/*VK_STRUCTURE_TYPE_DISPLAY_SURFACE_CREATE_INFO_KHR*/;
	surfaceCreateInfo.pNext = nullptr;
	surfaceCreateInfo.flags = 0;
	surfaceCreateInfo.hinstance = nullptr;	//Eigentlich müssten hier die jeweiligen Pointer für die Fenstererstellung rein.
	surfaceCreateInfo.hwnd = nullptr;		//Eigentlich müssten hier die jeweiligen Pointer für die Fenstererstellung rein.

	VkSurfaceKHR surface;		//Platformunabhängig.
	result_ONE = vkCreateWin32SurfaceKHR(VulkanTutorial::instance_ONE, &surfaceCreateInfo, nullptr, &surface); //Diese Funktion ist nicht platformunabhängig. Kein Fenster, sondern Surface. Surface kann in Fenster gelegt werden.
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
	deviceQueueCreateInfo.queueCount = 1;
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

	VkQueue queue;

	vkGetDeviceQueue(VulkanTutorial::device_ONE, 0, 0, &queue);
	vkDeviceWaitIdle(VulkanTutorial::device_ONE);

	vkDestroyDevice(VulkanTutorial::device_ONE, nullptr);
	vkDestroySurfaceKHR(VulkanTutorial::instance_ONE, surface, nullptr);
	vkDestroyInstance(VulkanTutorial::instance_ONE, nullptr);

	delete[] layers;
	delete[] extensions;
	delete[] physicalDevices;

	measureTime("t2");

	system("pause");
	return 0;

}

