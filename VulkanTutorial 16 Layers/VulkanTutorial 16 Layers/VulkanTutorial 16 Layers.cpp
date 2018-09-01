// VulkanTutorial 16 Layers.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include "vulkan\vulkan.h"
#include <iostream>
#include <vector>

#define ASSERT_VULKAN(val) if(val != VK_SUCCESS) {__debugbreak();}		

/*"Layers":

Allgemeine Informationen
-------------------------
1. Das Sternchen mit einer Nummer ist ein Textverweis auf eine andere Kommentarstelle in dieser Datei. Erschaffen, weil zu wenig Platz in den 2-Bildschirmdimensionen :(.
2. Kommentare bei "0." sind meistens allgemeine Informationen über das Thema dieses Tutorials. Speziell zu dem Zeitpunkt, wo die weitere Struktur des Tutorials noch unbekannt ist.
3. Weitere Informationen, die unter genaue Punkte bzw. Themenbereiche zu fassen sind, werden wie folgt numeriert: "1. ... 1.1 ... 1.1.1 ... 2. ... 2.1 ... 2.1.1 ...".
4. "VERALTET UND WIRD IGNORIERT." dient als Mittel, um im Tutorial noch dargestellte Funktionalitäten, die jedoch jetzt bereits veraltet sind, zu kennzeichnen.
-------------------------

Internetverweise
-----------------
1. VkLayerProperties: https://www.khronos.org/registry/vulkan/specs/1.0/man/html/VkLayerProperties.html
2. vkEnumerateInstanceLayerProperties: https://www.khronos.org/registry/vulkan/specs/1.0/man/html/vkEnumerateInstanceLayerProperties.html
3. LunarG Vulkan SDK Layers: https://vulkan.lunarg.com/doc/view/1.0.39.1/windows/layers.html
-----------------

1. Layers: Features, die sich zwischen verschiedene Vulkan Funktionen reinklinken können, um dort irgendeine Funktionalität auszuführen (z.B.: Validierung: Überprüfung auf richtige Parameter in Funktionen).
Layer können dann im Release wieder ausgeschaltet werden, um die Performance zurückzugewinnen, die im Debugging für erhöhte Sicherheit geopfert wurde.
Layer können entweder auf "Instance" Ebene oder auf "Device" Ebene aktiviert werden.

2. VkLayerProperties: Structure specifying layer properties.
	2.1 layerName[VK_MAX_EXTENSION_NAME_SIZE]: Name wird zur Aktivierung gebraucht.

	2.2 specVersion: Vulkan Version für den der Layer geschrieben wurde.

	2.3 implementationVersion: Version dieses Layers.

	2.4 description[VK_MAX_DESCRIPTION_SIZE]: Beschreibung des Layers. Nur für den Programmierer.

3. VkLayer (LUNARG ist eine Subdivision von den Vulkan Machern.)
	3.1 VK_LAYER_LUNARG_api_dump: Gibt Funktionsaufrufe sowie deren Werte und Parameter aus.

	3.2 VK_LAYER_LUNARG_core_validation: Von Vulkan Core Funktionen werden Validierungen durchgeführt (Parameter werden überprüft).

	3.3 VK_LAYER_LUNARG_monitor: Gibt FPS des Zielprogramms in der Titelbar aus.

	3.4 VK_LAYER_LUNARG_object_tracker: Trackt alle Vulkan Objekte und flags, die invalide sind und Objekt memory leaks.

	3.5 VK_LAYER_LUNARG_parameter_validation: Überprüft Parameter, die in eine Funktion reingegeben wurden.

	3.6 VK_LAYER_LUNARG_screenshot: Gibt die vorgegebenen Frames an eine Bilddatei aus, wie sie dargestellt werden.

	3.7 VK_LAYER_LUNARG_swapchain: Überprüft die Benutzung der "WSI 'Swapchain'" Extension.

	3.8 VK_LAYER_GOOGLE_threading: Überprüft die Validität der Benutzung von Multi-Threading (z.B.: Ob ein Vulkan von 2 Threads gleichzeitig benutzt werden darf.).

	3.9 VK_LAYER_GOOGLE_unique_objects: Wickle alle Vulkan-Objekte zur Erschaffungszeit in einen uniquePointer, und entwickle sie zur Benutzungszeit.  

	3.10 VK_LAYER_LUNARG_vktrace: /

	3.11 VK_LAYER_NV_optimus: /

	3.12 VK_LAYER_VALVE_steam_overlay: SteamOverlay aktivieren.

	3.13 VK_LAYER_RENDERDOC_Capture: /

	3.14 VK_LAYER_LUNARG_standard_validation: Aktiviert alle Standard Validation Layer zusammen.
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

		//Char Pointer that underlines Text in the console.
		

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

	uint32_t amountOfLayers = 0;								//Instance Layer.
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

	const std::vector<const char*> validationLayers = {
		"VK_LAYER_LUNARG_standard_validation"
	};

	VkInstanceCreateInfo instanceInfo;
	instanceInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	instanceInfo.pNext = NULL;
	instanceInfo.flags = 0;
	instanceInfo.pApplicationInfo = &appInfo;
	instanceInfo.enabledLayerCount = validationLayers.size();	//"size()" holt sich die Größe des "validationLayers" Vektor.
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

	float queuePrios[] = {1.0f, 1.0f, 1.0f, 1.0f};

	VkDeviceQueueCreateInfo deviceQueueCreateInfo;
	deviceQueueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	deviceQueueCreateInfo.pNext = NULL;
	deviceQueueCreateInfo.flags = 0;
	deviceQueueCreateInfo.queueFamilyIndex = 0;
	deviceQueueCreateInfo.queueCount = 4;
	deviceQueueCreateInfo.pQueuePriorities = queuePrios;	//Hier muss ein Array rein mit der Länge an Queues, die benutzt werden.
	//--------------------

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

